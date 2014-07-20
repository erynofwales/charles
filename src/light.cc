/* light.cc
 *
 * Lights light the scene.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include "basics.h"
#include "light.h"
#include "object.h"

#pragma mark - Ambient Lights

AmbientLight::AmbientLight()
    : AmbientLight(Color::White)
{ }


AmbientLight::AmbientLight(const Color &c)
    : AmbientLight(c, 0.0)
{ }


AmbientLight::AmbientLight(const Color &c, const float &i)
    : color(c),
      intensity(i)
{
    _clamp_intensity();
}


const Color &
AmbientLight::get_color()
    const
{
    return color;
}


const float &
AmbientLight::get_intensity()
    const
{
    return intensity;
}

void
AmbientLight::set_intensity(const float &i)
{
    intensity = i;
    _clamp_intensity();
}


Color
AmbientLight::compute_color_contribution()
    const
{
    return color * intensity;
}


void
AmbientLight::_clamp_intensity()
{
    if (intensity < 0.0) {
        intensity = 0.0;
    }
    else if (intensity > 1.0) {
        intensity = 1.0;
    }
}

#pragma mark - Point Lights

PointLight::PointLight()
    : PointLight(Vector3())
{ }


PointLight::PointLight(const Vector3 &o)
    : PointLight(o, Color::White)
{ }


PointLight::PointLight(const Vector3 &o,
                       const Color &c)
    : PointLight(o, c, 1.0)
{ }


PointLight::PointLight(const Vector3 &o,
                       const Color &c,
                       const float &i)
    : AmbientLight(c, i),
      mOrigin(o)
{ }


const Vector3&
PointLight::GetOrigin()
    const
{
    return mOrigin;
}


void
PointLight::SetOrigin(const Vector3& origin)
{
    mOrigin = origin;
}
