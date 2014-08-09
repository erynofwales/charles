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
#include "basics/basics.hh"


using charles::basics::Vector4;


namespace charles {

#pragma mark - Objects

Object::Object(const Vector4& origin)
    : mTranslation(basics::TranslationMatrix(origin.X(), origin.Y(), origin.Z())),
      mMaterial()
{ }


/*
 */


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
