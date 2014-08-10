/* object.h
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <iostream>
#include <memory>
#include <vector>

#include "material.hh"
#include "stats.hh"
#include "basics/basics.hh"


namespace charles {

struct Object
{
    typedef std::shared_ptr<Object> Ptr;

    Object(const basics::Vector4& origin = basics::Vector4());
    virtual ~Object();

    Material& GetMaterial();
    void SetMaterial(const Material& material);

    /**
     * Determine if the given ray intersects with this object. Converts the
     * ray's origin and direction to object space before calling the protected
     * Object::DoIntersect method. All intersection t values are returned in the
     * `t` argument, in ascending order.
     */
    bool Intersect(const basics::Ray& ray, TVector& t, Stats& stats) const;

    /**
     * Get the normal vector at the given point p. p is assumed to be on the
     * surface.
     */
    basics::Vector4 Normal(const basics::Vector4& p) const;

    /** Write a string representation of this object to the stream. */
    virtual void Write(std::ostream& ost) const;

protected:
    /**
     * Do the actual intersection work. Subclasses are expected to override
     * this.
     */
    virtual bool DoIntersect(const basics::Ray& ray, TVector& t, Stats& stats) const = 0;

    /**
     * Do the actual work of finding a normal for point p. Subclasses are
     * expected to override this.
     */
    virtual basics::Vector4 DoNormal(const basics::Vector4& p) const = 0;

private:
    /** Convert `ray` to object space from global space. */
    basics::Ray ToObjectSpace(const basics::Ray& ray) const;

    /** Convert `v` to object space from global space. */
    basics::Vector4 ToObjectSpace(const basics::Vector4& v) const;

    /** Convert `v` to global space from object space. */
    basics::Vector4 FromObjectSpace(const basics::Vector4& v) const;

    /** A translation matrix from global coordinates to this object's space. */
    basics::Matrix4 mTranslation;

    /** This object's material, surface properties, etc. */
    Material mMaterial;
};


/** Write a string representation of the Object to an output stream. */
std::ostream& operator<<(std::ostream& ost, const Object& object);

} /* namespace charles */

#endif
