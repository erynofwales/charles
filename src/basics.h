/* basics.h
 *
 * Declaration of basic types: Vector.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#ifndef __BASICS_H
#define __BASICS_H

#include <stdint.h>


typedef struct {
    float x, y, z;
} Vector3;


extern const Vector3 ZeroVector3;


Vector3 vector_init(float x, float y, float z);
Vector3 vector_mult_scalar(Vector3 v, float f);
Vector3 vector_mult_vector(Vector3 v, Vector3 f);
Vector3 vector_sub_vector(Vector3 m, Vector3 s);
float vector_length2(Vector3 v);
float vector_length(Vector3 v);
float vector_dot(Vector3 v, Vector3 f);

Vector3 vector_normalize(Vector3 v);


typedef struct {
    float x, y;
    float w, h;
} Rect;

Rect rect_init(float x, float y, float h, float w);


typedef struct {
    Vector3 location;
    Vector3 direction;
} Ray;

Ray ray_init(Vector3 location, Vector3 direction);


typedef struct {
    uint8_t red, green, blue, alpha;
} Color;


#endif
