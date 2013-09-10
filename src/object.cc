/* object.c
 *
 * Definition of scene Objects.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#include <cassert>
#include <cmath>
#include <cstdlib>

#include "basics.h"
#include "object.h"


static int sphere_does_intersect(Object *obj, Ray ray, float **t);
static int sphere_point_lies_on_surface(Object *obj, Vector3 p);
static Vector3 sphere_compute_normal(Object *obj, Vector3 p);


/*
 * Object::Object --
 *
 * Default constructor. Create a new Object with an origin at (0, 0, 0).
 */
Object::Object()
    : origin()
{ }


/*
 * Object::get_origin --
 * Object::set_origin --
 *
 * Get and set the Object's origin.
 */
Vector3
Object::get_origin()
{
    return origin;
}

void
Object::set_origin(Vector3 v)
{
    origin = v;
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
        *t = malloc(sizeof(float) * nints);
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
 * sphere_point_lies_on_surface --
 *
 * Determine if a point lies on the given sphere.
 */
int
sphere_point_lies_on_surface(Object *obj, Vector3 p)
{
    assert(obj != NULL && obj->type == ObjectTypeSphere);

    Vector3 loc = object_get_location(obj);
    float x = p.x - loc.x;
    float y = p.y - loc.y;
    float z = p.z - loc.z;
    float r = object_sphere_get_radius(obj);

    return (x * x) + (y * y) + (z * z) == (r * r);
}


/*
 * sphere_compute_normal --
 *
 * Compute the normal for the given Object (which must be a Sphere) at the given point. This point must lie on the
 * surface of the object.
 */
/* static */ Vector3
sphere_compute_normal(Object *obj, Vector3 p)
{
    assert(obj != NULL && obj->type == ObjectTypeSphere);

    // Make sure the given point is actually on the surface of the sphere.
    if (!sphere_point_lies_on_surface(obj, p)) {
        return Vector3Zero;
    }

    // The fun thing about sphere is the normal to any point on the sphere is the point itself. Woo!
    return p;
}
