/* object_sphere.h
 *
 * Spheres are Scene objects defined by a center point and a radius.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>

#include "basics.h"
#include "object.h"
#include "objectSphere.hh"


using charles::basics::Vector4;


namespace charles {

/*
 * charles::Sphere::Sphere --
 */
Sphere::Sphere(const Vector4& origin,
               Double radius)
    : Object(origin),
      mRadius(radius)
{ }


Double
Sphere::GetRadius()
    const
{
    return mRadius;
}


void
Sphere::SetRadius(Double r)
{
    mRadius = std::fabs(r);
}


/*
 * Sphere::DoesIntersect --
 */
bool
Sphere::DoesIntersect(const Ray& ray,
                      TVector& t,
                      Stats& stats)
    const
{
    stats.sphereIntersectionTests++;

    /* Coefficients for quadratic equation. */
    Double a = ray.direction.dot(ray.direction);
    Double b = ray.direction.dot(ray.origin) * 2.0;
    Double c = ray.origin.dot(ray.origin) - (mRadius * mRadius);

    /* Discriminant for the quadratic equation. */
    Double discrim = (b * b) - (4.0 * a * c);

    /*
     * If the discriminant is less than zero, there are no real (as in not
     * imaginary) solutions to this intersection.
     */
    if (discrim < 0) {
        return false;
    }

    /*
     * Compute the intersections, the roots of the quadratic equation. Spheres
     * have at most two intersections.
     */
    Double sqrtDiscrim = sqrt(discrim);
    Double t0 = (-b - sqrtDiscrim) / (2.0 * a);
    Double t1 = (-b + sqrtDiscrim) / (2.0 * a);

    /*
     * If the farther intersection of the two is in the negative direction, the
     * sphere is in the ray's negative direction.
     */
    if (t1 < 0) {
        return false;
    }

    if (t0 == t1) {
        t.push_back(t0);
    }
    else {
        /* Push these on in ascending order, nearest intersection to farthest. */
        if (t0 < t1) {
            t.push_back(t0);
            t.push_back(t1);
        }
        else {
            t.push_back(t1);
            t.push_back(t0);
        }
    }

    stats.sphereIntersections++;
    return true;
}


/*
 * Sphere::point_is_on_surface --
 *
 * Determine if a point lies on the surface of this Sphere.
 */
bool
Sphere::point_is_on_surface(const Vector3 &p)
    const
{
    Vector3 o = GetOrigin();
    Double x = p.x - o.x;
    Double y = p.y - o.y;
    Double z = p.z - o.z;

    return x*x + y*y + z*z == mRadius*mRadius;
}


/*
 * Sphere::compute_normal --
 *
 * Compute the normal for this Sphere at the given point. If the point does not lie on the surface of the sphere, a zero
 * vector is returned.
 */
Vector3
Sphere::compute_normal(const Vector3 &p)
    const
{
    // The fun thing about sphere is the normal to any point on the sphere is the point itself. Woo!
    Vector3 normal = p - GetOrigin();
    normal.normalize();
    return normal;
}


void
Sphere::Write(std::ostream& ost)
    const
{
    ost << "[Sphere origin=" << GetOrigin() << " r=" << mRadius << "]";
}

} /* namespace charles */
