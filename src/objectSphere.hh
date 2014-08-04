/* object_sphere.h
 *
 * Spheres are Shapes defined by a center point and a radius.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __OBJECTSPHERE_HH__
#define __OBJECTSPHERE_HH__

#include "basics.h"
#include "object.h"

namespace charles {

class Sphere
    : public Object
{
public:
    Sphere();
    Sphere(Double r);
    Sphere(Vector3 o, Double r);

    Double GetRadius() const;
    void SetRadius(Double r);

    bool DoesIntersect(const Ray& ray, TVector& t, Stats& stats) const;
    bool point_is_on_surface(const Vector3 &p) const;
    Vector3 compute_normal(const Vector3 &p) const;

    /** @see charles::Object::Write */
    void Write(std::ostream& ost) const;

private:
    Double mRadius;
};

} /* namespace charles */

#endif /* __OBJECTSPHERE_HH__ */
