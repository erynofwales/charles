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

namespace charles {

class Sphere
    : public Object
{
public:
    typedef std::shared_ptr<Sphere> Ptr;

    Sphere();
    Sphere(float r);
    Sphere(Vector3 o, float r);

    float get_radius();
    void set_radius(float r);

    bool DoesIntersect(const Ray& ray, TVector& t, Stats& stats) const;
    bool point_is_on_surface(const Vector3 &p) const;
    Vector3 compute_normal(const Vector3 &p) const;
private:
    float radius;
};

} /* namespace charles */

#endif
