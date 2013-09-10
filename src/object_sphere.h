/* object_sphere.h
 *
 * Spheres are Shapes defined by a center point and a radius.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __OBJECT_SPHERE_H__
#define __OBJECT_SPHERE_H__

#include "basics.h"
#include "object.h"


class Sphere
    : public Shape
{
    Sphere();
    Sphere(float r);
    Sphere(Vector3 o, float r);

    float get_radius();
    void set_radius(float r);

    int does_intersect(const Ray &ray, float **t);
private:
    float radius;
};

#endif
