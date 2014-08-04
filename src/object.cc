/* object.c
 *
 * Definition of generic scene objects.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cassert>
#include <cmath>
#include <cstdlib>

#include "basics.h"
#include "material.h"
#include "object.h"

namespace charles {

#pragma mark - Objects

/*
 * Object::Object --
 *
 * Default constructor. Create a new Object with an origin at (0, 0, 0).
 */
Object::Object()
    : Object(Vector3::Zero)
{ }


/*
 * Object::Object --
 *
 * Constructor. Create a new Object with an origin at o.
 */
Object::Object(Vector3 origin)
    : mOrigin(origin),
      mMaterial()
{ }


Vector3
Object::GetOrigin()
    const
{
    return mOrigin;
}


Object::~Object()
{ }


void
Object::SetOrigin(const Vector3& origin)
{
    mOrigin = origin;
}


Material&
Object::GetMaterial()
{
    return mMaterial;
}


void
Object::SetMaterial(const Material& material)
{
    mMaterial = material;
}


void
Object::Write(std::ostream& ost)
    const
{
    ost << "[Object]";
}


std::ostream&
operator<<(std::ostream& ost,
           const Object& object)
{
    object.Write(ost);
    return ost;
}

} /* namespace charles */
