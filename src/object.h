/* object.h
 *
 * Declaration of abstract, top-level scene objects. The Object class is the top of this hierarchy. All other scene
 * objects are based on it. The Shape class defines a visible shape in the scene.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <iostream>
#include <memory>
#include <vector>

#include "basics.h"
#include "material.h"
#include "stats.hh"
#include "texture.h"
#include "types.hh"

namespace charles {

struct Object
{
    typedef std::shared_ptr<Object> Ptr;

    Object();
    Object(Vector3 o);
    virtual ~Object();

    Vector3 GetOrigin() const;
    void SetOrigin(const Vector3& origin);

    Material& GetMaterial();
    void SetMaterial(const Material& material);

    /**
     * Determines if the given ray intersects with this object. All intersection
     * t values are returned in the `t` argument, in increasing order.
     *
     * @param [in]  ray     The ray to test for intersection
     * @param [out] t       A vector of all intersection t values
     * @return `true` if the ray intersects with this object
     */
    virtual bool DoesIntersect(const Ray& ray, TVector& t, Stats& stats) const = 0;
    virtual bool point_is_on_surface(const Vector3 &p) const = 0;
    virtual Vector3 compute_normal(const Vector3 &p) const = 0;

private:
    /** The location of this object. */
    Vector3 mOrigin;

    /** This object's material, surface properties, etc. */
    Material mMaterial;
};

} /* namespace charles */

#endif
