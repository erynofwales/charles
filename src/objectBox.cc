/* objectBox.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <limits>

#include "objectBox.hh"


namespace charles {

Box::Box()
      /* A unit box centered on the origin. */
    : Box(Vector3(-0.5, -0.5, -0.5), Vector3(0.5, 0.5, 0.5))
{ }


Box::Box(const Vector3& near, const Vector3& far)
    : Object(),
      mNear(near),
      mFar(far)
{ }


Vector3&
Box::GetNear()
{
    return mNear;
}


void
Box::SetNear(const Vector3& near)
{
    mNear = near;
}


Vector3&
Box::GetFar()
{
    return mFar;
}


void
Box::SetFar(const Vector3& far)
{
    mFar = far;
}


bool
Box::DoesIntersect(const Ray& ray,
                   TVector& t,
                   Stats& stats)
    const
{
    stats.boxIntersectionTests++;

    /*
     * XXX: For now, I'm assuming that all boxes are parallel to the coordinate
     * axes. This is the Kay-Kajiya box intersection algorithm.
     */

    Double t0, t1;
    Double tNear = -std::numeric_limits<Double>::infinity();
    Double tFar = std::numeric_limits<Double>::infinity();

    /*
     * From the Ray Tracing book:
     *
     *   For a more efficient algorithm, unwrap the loop, expand the swap of t0
     *   and t1 into two branches, and change the calculations to multiply by
     *   the inverse of the ray's direction to avoid divisions. Unwrapping the
     *   loop allows elimination of comparing t0 adn t1 to tNear and tFar [for
     *   the X planes], as tNear will always be set to the smaller and tFar the
     *   larger of t0 and t1.
     *
     * Initially there was a for loop iterating over each parallel pair of
     * planes (X, Y, and Z planes).
     */

    /*
     * Unrolling the loop means lots of duplicated code. So we start with the X
     * planes...
     */

    if (ray.direction.x == 0.0) {
        /* The ray is parallel to the X axis. */
        if (ray.origin.x < mNear.x || ray.origin.x > mFar.x) {
            /* The ray's origin is not between the slabs, so no intersection. */
            return false;
        }
    } else {
        Double invX = 1.0 / ray.direction.x;
        t0 = (mNear.x - ray.origin.x) * invX;
        t1 = (mFar.x - ray.origin.x) * invX;
        if (t0 > t1) {
            tNear = t1;
            tFar = t0;
        } else {
            tNear = t0;
            tFar = t1;
        }

        if (tNear > tFar) {
            /* Box is missed. */
            return false;
        }
        if (tFar < 0.0) {
            /* Box is behind the ray. */
            return false;
        }
    }

    /* Now the Y planes. */

    if (ray.direction.y == 0.0) {
        /* The ray is parallel to the Y axis. */
        if (ray.origin.y < mNear.y || ray.origin.y > mFar.y) {
            /* The ray's origin is not between the slabs, so no intersection. */
            return false;
        }
    } else {
        /* The ray isn't parallel, so calculate the intersection points. */
        Double invY = 1.0 / ray.direction.y;
        t0 = (mNear.y - ray.origin.y) * invY;
        t1 = (mFar.y - ray.origin.y) * invY;
        if (t0 > t1) {
            tNear = t1;
            tFar = t0;
        } else {
            tNear = t0;
            tFar = t1;
        }

        if (tNear > tFar) {
            /* Box is missed. */
            return false;
        }
        if (tFar < 0.0) {
            /* Box is behind the ray. */
            return false;
        }
    }

    /* Finally, the Z planes. */

    if (ray.direction.z == 0.0) {
        /* The ray is parallel to the Z axis. */
        if (ray.origin.z < mNear.z || ray.origin.z > mFar.z) {
            /* The ray's origin is not between the slabs, so no intersection. */
            return false;
        }
    } else {
        Double invZ = 1.0 / ray.direction.z;
        t0 = (mNear.z - ray.origin.z) * invZ;
        t1 = (mFar.z - ray.origin.z) * invZ;
        if (t0 > t1) {
            tNear = t1;
            tFar = t0;
        } else {
            tNear = t0;
            tFar = t1;
        }

        if (tNear > tFar) {
            /* Box is missed. */
            return false;
        }
        if (tFar < 0.0) {
            /* Box is behind the ray. */
            return false;
        }
    }

    /* We have an intersection! */
    stats.boxIntersections++;
    t.push_back(tNear);
    t.push_back(tFar);

    return true;
}


bool
Box::point_is_on_surface(const Vector3& p)
    const
{
    if (p.x == mNear.x || p.x == mFar.x) {
        return    (p.y > mNear.y && p.y < mFar.y)
               && (p.z > mNear.z && p.z < mFar.z);
    } else if (p.y == mNear.y || p.y == mFar.y) {
        return    (p.x > mNear.x && p.x < mFar.x)
               && (p.z > mNear.z && p.z < mFar.z);
    } else if (p.z == mNear.z || p.z == mFar.z) {
        return    (p.x > mNear.x && p.x < mFar.x)
               && (p.y > mNear.y && p.y < mFar.y);
    }
    return false;
}


Vector3
Box::compute_normal(const Vector3& p)
    const
{
    const Double EPS = 0.01;

    if (abs(p.x - mNear.x) < EPS) {
        return Vector3(-1, 0, 0);
    } else if (abs(p.x - mFar.x) < EPS) {
        return Vector3(1, 0, 0);
    } else if (abs(p.y - mNear.y) < EPS) {
        return Vector3(0, -1, 0);
    } else if (abs(p.y - mFar.y) < EPS) {
        return Vector3(0, 1, 0);
    } else if (abs(p.z - mNear.z) < EPS) {
        return Vector3(0, 0, -1);
    } else if (abs(p.z - mFar.y) < EPS) {
        return Vector3(0, 0, 1);
    }

    return Vector3();
}

} /* namespace charles */

