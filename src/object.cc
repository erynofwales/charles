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

/*
 * charles::Object::Object --
 */
Object::Object(const Vector4& origin)
    : mTranslation(basics::TranslationMatrix(origin.X(), origin.Y(), origin.Z())),
      mMaterial()
{ }


/*
 * charles::Object::~Object --
 */
Object::~Object()
{ }


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


/*
 * charles::Object::Intersect --
 */
bool
Object::Intersect(const basics::Ray& ray,
                  TVector& t,
                  Stats& stats)
    const
{
    /* TODO: Remove basics:: when the old Ray class goes away. */
    basics::Ray objRay = ToObjectSpace(ray);
    return DoIntersect(objRay, t, stats);
}


/*
 * charles::Object::ToObjectSpace --
 */
/* TODO: Remove basics:: when the old Ray class goes away. */
basics::Ray
Object::ToObjectSpace(const basics::Ray& ray)
    const
{
    /* TODO: Remove basics:: when the old Ray class goes away. */
    basics::Ray objRay(ray);
    objRay.origin = mTranslation * objRay.origin;
    objRay.direction = mTranslation * objRay.direction;
    return objRay;
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
