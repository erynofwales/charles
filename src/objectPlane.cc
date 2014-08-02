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

#include "basics.h"
#include "object.h"
#include "objectPlane.hh"

namespace charles {

/*
 * charles::Plane::Plane --
 */
Plane::Plane()
    : mNormal(Vector3::Y),
      mDistance(0.0)
{ }


const Vector3&
Plane::GetNormal()
    const
{
    return mNormal;
}


void
Plane::SetNormal(const Vector3& normal)
{
    mNormal = normal.normalized();
}


Double
Plane::GetDistance()
    const
{
    return mDistance;
}


void
Plane::SetDistance(Double distance)
{
    mDistance = distance;
}


/*
 * charles::Plane::DoesIntersect --
 */
bool
Plane::DoesIntersect(const Ray &ray,
                     TVector& t)
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

    /* The denominator for the t equation above. */
    Double vd = mNormal.dot(ray.direction);
    if (vd == 0.0) {
        /* The ray is parallel to the plane. */
        return false;
    }

    /* The numerator of the equation for t above. */
    Double vo = -(mNormal.dot(ray.origin) + mDistance);

    Double t0 = vo / vd;
    if (t0 < 0.0) {
        /* The plane is behind the ray's origin. */
        return false;
    }

    t.push_back(t0);
    return true;
}


/*
 * charles::Plane::point_is_on_surface --
 */
bool
Plane::point_is_on_surface(const Vector3 &p)
    const
{
    /*
     * Plug point p into the equation for a plane:
     *
     *     A * x + B * y + C * z + D = 0
     *
     * where (A, B, C) are the coordinates of the normal vector, and D is the
     * distance along that vector from the origin.
     */
    Double x = mNormal.x * p.x;
    Double y = mNormal.y * p.y;
    Double z = mNormal.z * p.z;
    return (x + y + z + mDistance) == 0.0;
}


/*
 * charles::Plane::compute_normal --
 */
Vector3
Plane::compute_normal(const Vector3 &p)
    const
{
    if (!point_is_on_surface(p)) {
        return Vector3::Zero;
    }
    if (mNormal.dot(p) < 0.0) {
        return mNormal;
    } else {
        return -mNormal;
    }
}

} /* namespace charles */
