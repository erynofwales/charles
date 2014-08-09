/* objectBox.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <limits>

#include "objectBox.hh"


using charles::basics::Ray;
using charles::basics::Vector4;


namespace charles {

/*
 * charles::Box::Box --
 */
Box::Box()
      /* A unit box centered on the origin. */
    : Box(Vector4(-0.5, -0.5, -0.5), Vector4(0.5, 0.5, 0.5))
{ }


/*
 * charles::Box::Box --
 */
Box::Box(const Vector4& near,
         const Vector4& far)
    : Object(),
      mNear(near),
      mFar(far)
{ }


/*
 * charles::Box::GetNear --
 */
Vector4&
Box::GetNear()
{
    return mNear;
}


/*
 * charles::Box::SetNear --
 */
void
Box::SetNear(const Vector4& near)
{
    mNear = near;
}


/*
 * charles::Box::GetFar --
 */
Vector4&
Box::GetFar()
{
    return mFar;
}


/*
 * charles::Box::SetFar --
 */
void
Box::SetFar(const Vector4& far)
{
    mFar = far;
}


/*
 * charles::Box::DoNormal --
 */
Vector4
Box::DoNormal(const Vector4& p)
    const
{
    if (NearlyEqual(p.X(), mNear.X())) {
        return Vector4(-1, 0, 0);
    } else if (NearlyEqual(p.X(), mFar.X())) {
        return Vector4(1, 0, 0);
    } else if (NearlyEqual(p.Y(), mNear.Y())) {
        return Vector4(0, -1, 0);
    } else if (NearlyEqual(p.Y(), mFar.Y())) {
        return Vector4(0, 1, 0);
    } else if (NearlyEqual(p.Z(), mNear.Z())) {
        return Vector4(0, 0, -1);
    } else if (NearlyEqual(p.Z(), mFar.Z())) {
        return Vector4(0, 0, 1);
    }

    /* TODO: Eventually, I might want to raise an error here. */
    return Vector4();
}


/*
 * charles::Box::DoIntersect --
 */
bool
Box::DoIntersect(const Ray& ray,
                 TVector& t,
                 Stats& stats)
    const
{
    stats.boxIntersectionTests++;

    /* This is the Kay-Kajiya box intersection algorithm. */

    Double tNear = -std::numeric_limits<Double>::infinity();
    Double tFar = std::numeric_limits<Double>::infinity();

    if (!IntersectSlab(mNear.X(), mFar.X(),
                       ray.origin.X(), ray.direction.X(),
                       tNear, tFar)) {
        return false;
    }
    if (!IntersectSlab(mNear.Y(), mFar.Y(),
                       ray.origin.Y(), ray.direction.Y(),
                       tNear, tFar)) {
        return false;
    }
    if (!IntersectSlab(mNear.Z(), mFar.Z(),
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

