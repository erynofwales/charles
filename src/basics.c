/* basics.c
 *
 * Definition of basic types: Vector.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <math.h>
#include "basics.h"


const Vector3 ZeroVector3 = {0.0, 0.0, 0.0};


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


/*
 * vector_length2 --
 *
 * Return the length-squared of the given vector.
 */
float
vector_length2(Vector3 v)
{
    return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}


/*
 * vector_length --
 *
 * Return the length of the given vector.
 */
float
vector_length(Vector3 v)
{
    return sqrt(vector_length2(v));
}


/*
 * vector_normalize --
 *
 * Normalize the given vector. Return a new vector.
 */
Vector3
vector_normalize(Vector3 v)
{
    float length2 = vector_length2(v);
    if (length2 <= 0) {
        return v;
    }

    float inverse_length = 1 / sqrt(length2);
    return vector_init(v.x * inverse_length, v.y * inverse_length, v.z * inverse_length);
}
