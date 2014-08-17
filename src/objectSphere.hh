/* object_sphere.h
 *
 * Spheres are Shapes defined by a center point and a radius.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __OBJECTSPHERE_HH__
#define __OBJECTSPHERE_HH__

#include "object.hh"
#include "basics/basics.hh"


namespace charles {

class Sphere
    : public Object
{
public:
    Sphere(const basics::Vector4& origin = basics::Vector4(), Double radius = 1.0);

    Double GetRadius() const;
    void SetRadius(const Double& r);

    /** @see charles::Object::Write */
    void Write(std::ostream& ost) const;

protected:
    bool DoIntersect(const basics::Ray& ray, TVector& t, Stats& stats) const override;
    basics::Vector4 DoNormal(const basics::Vector4& p) const override;

private:
    Double mRadius;
};

} /* namespace charles */

#endif /* __OBJECTSPHERE_HH__ */
