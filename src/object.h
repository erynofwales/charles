/* object.h
 *
 * Declaration of abstract, top-level scene objects. The Object class is the top of this hierarchy. All other scene
 * objects are based on it. The Shape class defines a visible shape in the scene.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "basics.h"
#include "texture.h"


class Object
{
public:
    Object();
    Object(Vector3 o);

    Vector3 get_origin() const;
    void set_origin(Vector3 v);

private:
    Vector3 origin;
};


class Shape
    : public Object
{
public:
    Shape();
    Shape(Vector3 o);

    virtual int does_intersect(const Ray &ray, float **t) const = 0;
    virtual bool point_is_on_surface(const Vector3 &p) const = 0;
    virtual Vector3 compute_normal(const Vector3 &p) const = 0;
};

#endif
