/* basics.h
 *
 * Declaration of basic types: Vector.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#ifndef __BASICS_H
#define __BASICS_H


typedef struct {
    float x, y, z;
} Vector3;


extern const Vector3 ZeroVector3;


Vector3 vector_init(float x, float y, float z);
Vector3 vector_mult_scalar(Vector3 v, float f);
Vector3 vector_mult_vector(Vector3 v, Vector3 f);


#endif
