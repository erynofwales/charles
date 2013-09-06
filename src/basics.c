/* basics.c
 *
 * Definition of basic types: Vector.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include "basics.h"


/*
 * vector_init --
 *
 * Create a new vector given x, y, and z coordinates.
 */
Vector3
vector_init(float x, float y, float z)
{
    Vector3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}


/*
 * vector_mult_scalar --
 *
 * Multiply a vector by a scalar. Return a new vector.
 */
Vector3
vector_mult_scalar(Vector3 v, float f)
{
    return vector_init(f * v.x, f * v.y, f * v.z);
}


/*
 * vector_mult_vector --
 *
 * Multiply a vector by another vector. Return a new vector.
 */
Vector3
vector_mult_vector(Vector3 v, Vector3 f)
{
    return vector_init(v.x * f.x, v.y * f.y, v.z * f.z);
}
