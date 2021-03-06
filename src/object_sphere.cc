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
    : Shape(o),
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
 * Sphere::does_intersect --
 *
 * Compute the intersection of a ray with this Sphere. All intersection t values are returned in the **t argument. The
 * number of values returned therein is indicated by the return value. Memory is allocated at *t. It is the caller's
 * responsibility to free it when it is no longer needed. If 0 is returned, no memory needs to be freed.
 */
int
Sphere::does_intersect(const Ray &ray, float **t)
    const
{
    // Origin of the vector in object space.
    Vector3 ray_origin_obj = ray.origin - get_origin();

    // Coefficients for quadratic equation.
    float a = ray.direction.dot(ray.direction);
    float b = ray.direction.dot(ray_origin_obj) * 2.0;
    float c = ray_origin_obj.dot(ray_origin_obj) - (radius * radius);

    // Discriminant for the quadratic equation.
    float discrim = (b * b) - (4.0 * a * c);

    // If the discriminant is less than zero, there are no real (as in not imaginary) solutions to this intersection.
    if (discrim < 0) {
        return 0;
    }

    // Compute the intersections, the roots of the quadratic equation. Spheres have at most two intersections.
    float sqrt_discrim = sqrtf(discrim);
    float t0 = (-b - sqrt_discrim) / (2.0 * a);
    float t1 = (-b + sqrt_discrim) / (2.0 * a);

    // If t[1] is less than t[0], swap them (t[0] will always be the first intersection).
    if (t1 < t0) {
        float tmp = t0;
        t0 = t1;
        t1 = tmp;
    }

    /*
     * If the farther intersection of the two is in the negative direction, the sphere is in the ray's negative
     * direction.
     */
    if (t1 < 0) {
        return 0;
    }

    /*
     * Allocate the memory and store the values. It's possible the two values are equal. Only allocate enough memory to
     * store the required number of values.
     */
    int nints = (t0 != t1) ? 2 : 1;
    if (t != NULL) {
        *t = new float[nints];
        if (*t == NULL) {
            return 0;
        }
        (*t)[0] = t0;
        if (nints > 1) {
            (*t)[1] = t1;
        }
    }

    return nints;
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
    Vector3 o = get_origin();
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
    Vector3 normal = p - get_origin();
    normal.normalize();
    return normal;
}
