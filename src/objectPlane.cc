/* object_plane.h
 *
 * Planes are Shapes defined by a point and two direction vectors.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>

#include "objectPlane.hh"


using charles::basics::Ray;
using charles::basics::Vector4;


namespace charles {

/*
 * charles::Plane::Plane --
 */
Plane::Plane()
    : mNormal(0, 1, 0),
      mDistance(0.0)
{ }


/*
 * charles::Plane::GetNormal --
 */
const Vector4&
Plane::GetNormal()
    const
{
    return mNormal;
}


/*
 * charles::Plane::SetNormal --
 */
void
Plane::SetNormal(const Vector4& normal)
{
    mNormal = basics::Normalized(normal);
}


/*
 * charles::Plane::GetDistance --
 */
Double
Plane::GetDistance()
    const
{
    return mDistance;
}


/*
 * charles::Plane::SetDistance --
 */
void
Plane::SetDistance(Double distance)
{
    mDistance = distance;
}


/*
 * charles::Plane::DoesIntersect --
 */
bool
Plane::DoIntersect(const Ray& ray,
                   TVector& t,
                   Stats& stats)
    const
{
    /*
     * Planes are defined in terms of [A B C D], where [A B C] make up the unit
     * normal vector, and D is the distance from the origin. We can write the
     * equation for a plane like this:
     *
     *     A * x + B * y + C * z + D = 0, where
     *     A^2 + B^2 + C^2 = 1.
     *
     * The sign of D determines which side of the origin the plane is on.
     *
     * We can figure out the distance from the ray's origin to the intersection
     * point (there will be only one for planes) by substituting the ray's
     * parameters into the above equation. In the equations below, RO is the
     * ray's origin, RD is the ray's direction, and components thereof are
     * indicated with lowercase letters (ROx is the x component of RO).
     *
     *     A(ROx + RDx * t) + B(ROy + RDy * t) + C(ROz + RDz * t) + D = 0
     *
     * We then solve for t.
     *
     *     t = -(A * ROx + B * ROy + C * ROz + D) / (A * RDx + B * RDy + C * RDz)
     *
     * In vector notation, this works out more cleanly.
     *
     *     t = -(n . RO + D) / (n . RD)
     */

    stats.planeIntersectionTests++;

    /* The denominator for the t equation above. */
    Double vd = mNormal.Dot(ray.direction);
    if (NearZero(vd)) {
        /* The ray is parallel to the plane. */
        return false;
    }

    /* The numerator of the equation for t above. */
    Double vo = -(mNormal.Dot(ray.origin) + mDistance);

    Double t0 = vo / vd;
    if (t0 < 0.0) {
        /* The plane is behind the ray's origin. */
        return false;
    }

    if (TooFar(t0)) {
        return false;
    }

    stats.planeIntersections++;
    t.push_back(t0);
    return true;
}


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

/*
 * charles::Plane::DoNormal --
 */
Vector4
Plane::DoNormal(const Vector4& p)
    const
{
    return mNormal;
}

#pragma clang diagnostic pop


/*
 * charles::Plane::Write --
 */
void
Plane::Write(std::ostream& ost)
    const
{
    ost << "[Plane normal=" << mNormal << " distance=" << mDistance << "]";
}

} /* namespace charles */
