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
#include "object_sphere.h"

namespace charles {

/*
 * Sphere::Sphere --
 *
 * Default constructor. Create a Sphere with radius 1.0.
 */
Sphere::Sphere()
    : Sphere(1.0)
{ }


/*
 * Sphere::Sphere --
 *
 * Constructor. Create a Sphere with the given radius.
 */
Sphere::Sphere(float r)
    : Sphere(Vector3::Zero, r)
{ }


Sphere::Sphere(Vector3 o, float r)
    : Object(o),
      radius(r)
{ }


/*
 * Sphere::get_radius --
 * Sphere::set_radius --
 *
 * Get and set the radius of this Sphere.
 */
float
Sphere::get_radius()
{
    return radius;
}

void
Sphere::set_radius(float r)
{
    radius = (radius >= 0.0) ? r : -r;
}


/*
 * Sphere::DoesIntersect --
 */
bool
Sphere::DoesIntersect(const Ray& ray,
                      TVector& t)
    const
{
    /* Origin of the vector in object space. */
    Vector3 rayOriginObj = ray.origin - GetOrigin();

    /* Coefficients for quadratic equation. */
    Double a = ray.direction.dot(ray.direction);
    Double b = ray.direction.dot(rayOriginObj) * 2.0;
    Double c = rayOriginObj.dot(rayOriginObj) - (radius * radius);

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
    float x = p.x - o.x;
    float y = p.y - o.y;
    float z = p.z - o.z;

    return x*x + y*y + z*z == radius*radius;
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

} /* namespace charles */
