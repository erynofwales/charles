/* lightPoint.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "lightPoint.hh"


using charles::basics::Vector4;


namespace charles {

PointLight::PointLight(const Vector4& origin,
                       const Color& color)
    : Light(color),
      mOrigin(origin)
{ }


Vector4
PointLight::GetOrigin()
{
    return mOrigin;
}


void
PointLight::SetOrigin(const Vector4& origin)
{
    mOrigin = origin;
}

} /* namespace charles */

