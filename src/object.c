/* object.c
 *
 * Definition of scene Objects.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "basics.h"
#include "object.h"


struct _Object {
    ObjectType type;
    Vector3 location;
    Texture *texture;
    void *shape;

    int (*does_intersect)(Object *obj, Ray ray, float **t);
};


typedef struct _Sphere {
    float radius;
} Sphere;

static int sphere_does_intersect(Object *obj, Ray ray, float **t);
static int sphere_point_lies_on_surface(Object *obj, Vector3 p);
static Vector3 sphere_compute_normal(Object *obj, Vector3 p);


/*
 * object_init ---
 *
 * Create a new object of the given type.
 */
Object *
object_init(ObjectType type)
{
    Object *obj = malloc(sizeof(Object));
    if (obj == NULL) {
        return NULL;
    }

    obj->type = type;
    obj->location = Vector3Zero;
    obj->texture = NULL;

    switch (type) {
        case ObjectTypeSphere: {
            Sphere *s = malloc(sizeof(Sphere));
            if (s == NULL) {
                // TODO: DANGER! WILL ROBINSON!
            }
            obj->shape = s;
            s->radius = 0.0;
            obj->does_intersect = sphere_does_intersect;
            break;
        }
        default:
            assert(0);
    }

    return obj;
}


/*
 * object_destroy --
 *
 * Destroy the given object.
 */
void
object_destroy(Object *obj)
{
    assert(obj != NULL);
    assert(obj->shape != NULL);

    free(obj->shape);
    free(obj);
}


/*
 * object_get_location --
 * object_set_location --
 *
 * Get and set the location of the object.
 */
Vector3
object_get_location(Object *obj)
{
    assert(obj != NULL);
    return obj->location;
}

void
object_set_location(Object *obj, Vector3 location)
{
    assert(obj != NULL);
    obj->location = location;
}


/*
 * object_get_texture --
 * object_set_texture --
 *
 * Get and set the object's texture.
 */
Texture *
object_get_texture(Object *obj)
{
    assert(obj != NULL);
    return obj->texture;
}

void
object_set_texture(Object *obj, Texture *tex)
{
    assert(obj != NULL);
    obj->texture = tex;
}


/*
 * object_does_intersect --
 *
 * Determine if a ray intersects with the object.
 */
int
object_does_intersect(Object *obj, Ray ray, float **t)
{
    assert(obj != NULL && obj->does_intersect != NULL);
    return obj->does_intersect(obj, ray, t);
}

/*
 * Sphere functions
 */

/*
 * object_sphere_get_radius --
 * object_sphere_set_radius --
 *
 * Get and set the radius of a Sphere object.
 */
float
object_sphere_get_radius(Object *obj)
{
    assert(obj != NULL && obj->type == ObjectTypeSphere);
    return ((Sphere *)obj->shape)->radius;
}

void
object_sphere_set_radius(Object *obj, float r)
{
    assert(obj != NULL && obj->type == ObjectTypeSphere);
    ((Sphere *)obj->shape)->radius = r;
}


/*
 * sphere_does_intersect --
 *
 * Compute the intersection of a ray with the given object. The object must be a Sphere. All intersection t values are
 * returned in the **t argument. The number of values returned therein is indicated by the return value. Memory is
 * allocated at *t. It is the caller's responsibility to free it when it is no longer needed. If 0 is returned, no
 * memory needs to be freed.
 */
int
sphere_does_intersect(Object *obj, Ray ray, float **t)
{
    // Location of the vector in object space.
    Vector3 ray_loc_obj = vector_sub_vector(ray.location, object_get_location(obj));
    float r = object_sphere_get_radius(obj);

    // Coefficients for quadratic equation.
    float a = vector_dot(ray.direction, ray.direction);
    float b = vector_dot(ray.direction, ray_loc_obj) * 2.0;
    float c = vector_dot(ray_loc_obj, ray_loc_obj) - (r * r);

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
    *t = malloc(sizeof(float) * nints);
    if (*t == NULL) {
        return 0;
    }
    (*t)[0] = t0;
    if (nints > 1) {
        (*t)[1] = t1;
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
