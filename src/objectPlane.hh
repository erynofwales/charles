/* object_plane.h
 *
 * Planes are Shapes defined by a point and two direction vectors.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __OBJECT_PLANE_H__
#define __OBJECT_PLANE_H__

#include "object.hh"
#include "basics/basics.hh"


namespace charles {

class Plane
    : public Object
{
public:
    /** Default constructor. Creates a plane with a normal along the Y axis. */
    Plane();

    const basics::Vector4& GetNormal() const;
    void SetNormal(const basics::Vector4& normal);

    Double GetDistance() const;
    void SetDistance(Double distance);

    /** @see charles::Object::Write */
    void Write(std::ostream& ost) const;

protected:
    bool DoIntersect(const basics::Ray& ray, TVector& t, Stats& stats) const;
    basics::Vector4 DoNormal(const basics::Vector4& p) const;

private:
    /** A normal vector, which specified the orientation of the plane. */
    basics::Vector4 mNormal;

    /**
     * The distance from the origin along the normal vector that this plane is
     * set.
     */
    Double mDistance;
};

} /* namespace charles */

#endif
