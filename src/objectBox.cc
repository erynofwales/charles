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


bool
Box::DoesIntersect(const Ray& ray,
                   TVector& t)
    const
{
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

    /* Unrolling the loop, so we start with the X planes... */

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
    t.push_back(t0);
    t.push_back(t1);
    return true;
}

} /* namespace charles */

