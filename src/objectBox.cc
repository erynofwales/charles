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
    if (NearlyEqual(p.x, mNear.x)) {
        return Vector3(-1, 0, 0);
    } else if (NearlyEqual(p.x, mFar.x)) {
        return Vector3(1, 0, 0);
    } else if (NearlyEqual(p.y, mNear.y)) {
        return Vector3(0, -1, 0);
    } else if (NearlyEqual(p.y, mFar.y)) {
        return Vector3(0, 1, 0);
    } else if (NearlyEqual(p.z, mNear.z)) {
        return Vector3(0, 0, -1);
    } else if (NearlyEqual(p.z, mFar.z)) {
        return Vector3(0, 0, 1);
    }

    /* TODO: Eventually, I might want to raise an error here. */
    return Vector3();
}


/*
 * charles::Box::DoIntersect --
 */
bool
Box::DoIntersect(const basics::Ray& ray,
                 TVector& t,
                 Stats& stats)
    const
{
    stats.boxIntersectionTests++;

    /* This is the Kay-Kajiya box intersection algorithm. */

    Double tNear = -std::numeric_limits<Double>::infinity();
    Double tFar = std::numeric_limits<Double>::infinity();

    if (!IntersectSlab(mNear.x, mFar.x,
                       ray.origin.X(), ray.direction.X(),
                       tNear, tFar)) {
        return false;
    }
    if (!IntersectSlab(mNear.y, mFar.y,
                       ray.origin.Y(), ray.direction.Y(),
                       tNear, tFar)) {
        return false;
    }
    if (!IntersectSlab(mNear.z, mFar.z,
                       ray.origin.Z(), ray.direction.Z(),
                       tNear, tFar)) {
        return false;
    }

    /* We have an intersection! */
    stats.boxIntersections++;
    t.push_back(tNear);
    t.push_back(tFar);

    return true;
}


/*
 * charles::Box::IntersectSlab --
 */
inline bool
Box::IntersectSlab(const Double& slabLow,
                   const Double& slabHigh,
                   const Double& rayOriginComponent,
                   const Double& rayDirectionComponent,
                   Double& tNear,
                   Double& tFar)
    const
{
    Double t0, t1;

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

    if (NearZero(rayDirectionComponent)) {
        /* The ray is parallel to the X axis. */
        if (rayOriginComponent < slabLow || rayOriginComponent > slabHigh) {
            /* The ray's origin is not between the slabs, so no intersection. */
            return false;
        }
    } else {
        t0 = (slabLow - rayOriginComponent) / rayDirectionComponent;
        t1 = (slabHigh - rayOriginComponent) / rayDirectionComponent;
#if 0
        if (t0 <= t1) {
            tNear = t0;
            tFar = t1;
        } else {
            tNear = t1;
            tFar = t0;
        }
#else
        if (t0 > t1) {
            Double tmp = t0;
            t0 = t1;
            t1 = tmp;
        }
#endif
        if (t0 > tNear) {
            tNear = t0;
        }
        if (t1 < tFar) {
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
    return true;
}


/*
 * charles::Box::Write --
 */
void
Box::Write(std::ostream& ost)
    const
{
    ost << "[Box near=" << mNear << " far=" << mFar << "]";
}

} /* namespace charles */

