/* object_plane.h
 *
 * Planes are Shapes defined by a point and two direction vectors.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __OBJECT_PLANE_H__
#define __OBJECT_PLANE_H__

#include "basics.h"
#include "object.h"


class Plane
    : public Shape
{
public:
    Plane();
    Plane(Vector3 normal);
    Plane(Vector3 o, Vector3 normal);

    int does_intersect(const Ray &ray, float **t) const;
    bool point_is_on_surface(const Vector3 &p) const;
    Vector3 compute_normal(const Vector3 &p) const;

private:
    Vector3 normal;
};

#endif
