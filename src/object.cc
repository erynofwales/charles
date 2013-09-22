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
#include "material.h"
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


std::ostream &
operator<<(std::ostream &os, const Object &o)
{
    // Stream objects like this: [Object origin]
    os << "[Object " << o.origin << "]";
    return os;
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
 * Shape::~Shape() --
 *
 * Destructor.
 */
Shape::~Shape()
{ }


/*
 * Shape::get_material --
 * Shape::set_material --
 *
 * Get and set the Material applied to this shape.
 */
Material &
Shape::get_material()
    const
{
    return *material;
}

void
Shape::set_material(Material *mat)
{
    material = mat;
}
