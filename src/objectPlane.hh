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
#include "types.hh"

namespace charles {

class Plane
    : public Object
{
public:
    /** Default constructor. Creates a plane with a normal along the Y axis. */
    Plane();

    const Vector3& GetNormal() const;
    void SetNormal(const Vector3& normal);

    Double GetDistance() const;
    void SetDistance(Double distance);

    /**
     * @see charles::Object::DoesIntersect
     */
    bool DoesIntersect(const Ray &ray, TVector& t) const;
    bool point_is_on_surface(const Vector3 &p) const;
    Vector3 compute_normal(const Vector3 &p) const;

private:
    /** A normal vector, which specified the orientation of the plane. */
    Vector3 mNormal;

    /**
     * The distance from the origin along the normal vector that this plane is
     * set.
     */
    Double mDistance;
};

} /* namespace charles */

#endif
