/* objectSphere.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>

#include "objectSphere.hh"


using charles::basics::Ray;
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


/*
 * charles::Sphere::GetRadius --
 */
Double
Sphere::GetRadius()
    const
{
    return mRadius;
}


/*
 * charles::Sphere::SetRadius --
 */
void
Sphere::SetRadius(const Double& r)
{
    mRadius = std::fabs(r);
}


/*
 * charles::Sphere::DoesIntersect --
 */
bool
Sphere::DoIntersect(const Ray& ray,
                    TVector& t,
                    Stats& stats)
    const
{
    stats.sphereIntersectionTests++;

    /* Coefficients for quadratic equation. */
    Double a = ray.direction.Dot(ray.direction);
    Double b = ray.direction.Dot(ray.origin) * 2.0;
    Double c = ray.origin.Dot(ray.origin) - (mRadius * mRadius);

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
    Double sqrtDiscrim = std::sqrt(discrim);
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
 * charles::Sphere::DoNormal --
 */
Vector4
Sphere::DoNormal(const Vector4& p)
    const
{
    /*
     * The fun thing about sphere is the normal to any point on the sphere is
     * the point itself. Woo!
     */
    return Normalized(p);
}


/*
 * charles::Sphere::Write --
 */
void
Sphere::Write(std::ostream& ost)
    const
{
    ost << "[Sphere r=" << mRadius << "]";
}

} /* namespace charles */
