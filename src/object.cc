/* object.c
 *
 * Definition of generic scene objects.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cassert>
#include <cmath>
#include <cstdlib>

#include "object.hh"

#include "material.hh"
#include "basics/basics.hh"


using charles::basics::Ray;
using charles::basics::Matrix4;
using charles::basics::Vector4;


namespace charles {

/*
 * charles::Object::Object --
 */
Object::Object(const Vector4& origin)
    : mTranslation(Matrix4::Translation(origin.X(), origin.Y(), origin.Z())),
      mMaterial()
{ }


/*
 * charles::Object::~Object --
 */
Object::~Object()
{ }


/*
 * charles::Object::GetMaterial --
 */
Material&
Object::GetMaterial()
{
    return mMaterial;
}


/*
 * charles::Object::Place --
 */
void
Object::Place(const Vector4 &p)
{
    mTranslation = Matrix4::Translation(p);
}


/*
 * charles::Object::SetMaterial --
 */
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
    return DoIntersect(ToObjectSpace(ray), t, stats);
}


/*
 * charles::Object::Normal --
 */
Vector4
Object::Normal(const Vector4& p)
    const
{
    return FromObjectSpace(DoNormal(ToObjectSpace(p)));
}


/*
 * charles::Object::ToObjectSpace --
 */
Ray
Object::ToObjectSpace(Ray ray)
    const
{
    ray.origin = mTranslation * ray.origin;
    return ray;
}


/*
 * charles::Object::ToObjectSpace --
 */
Vector4
Object::ToObjectSpace(const Vector4& v)
    const
{
    return mTranslation * v;
}


/*
 * charles::Object::FromObjectSpace --
 */
Vector4
Object::FromObjectSpace(const Vector4& v)
    const
{
    return Inverse(mTranslation) * v;
}


/*
 * charles::Object::Write --
 */
void
Object::Write(std::ostream& ost)
    const
{
    ost << "[Object]";
}


/*
 * charles::operator<< --
 */
std::ostream&
operator<<(std::ostream& ost,
           const Object& object)
{
    ost << "[";
    object.Write(ost);
    ost << " translate=" << object.mTranslation.Column(3) << "]";
    return ost;
}

} /* namespace charles */
