/* object.c
 *
 * Definition of generic scene objects.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cassert>
#include <cmath>
#include <cstdlib>

#include "basics.h"
#include "object.h"

#pragma mark - Objects

/*
 * Object::Object --
 *
 * Default constructor. Create a new Object with an origin at (0, 0, 0).
 */
Object::Object()
    : Object(Vector3::Zero)
{ }


/*
 * Object::Object --
 *
 * Constructor. Create a new Object with an origin at o.
 */
Object::Object(Vector3 o)
    : origin(o)
{ }


/*
 * Object::get_origin --
 * Object::set_origin --
 *
 * Get and set the Object's origin.
 */
Vector3
Object::get_origin()
    const
{
    return origin;
}

void
Object::set_origin(Vector3 v)
{
    origin = v;
}

#pragma mark - Shapes

/*
 * Shape::Shape --
 *
 * Default constructor. Create a new Shape with an origin at (0, 0, 0).
 */
Shape::Shape()
    : Object()
{ }


/*
 * Shape::Shape --
 *
 * Constructor. Create a new Shape with an origin at o.
 */
Shape::Shape(Vector3 o)
    : Object(o)
{ }

/*
 * sphere_point_lies_on_surface --
 *
 * Determine if a point lies on the given sphere.
 */
#if 0
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
#endif


/*
 * sphere_compute_normal --
 *
 * Compute the normal for the given Object (which must be a Sphere) at the given point. This point must lie on the
 * surface of the object.
 */
#if 0
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
#endif
