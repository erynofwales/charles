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
    : AmbientLight(c, 1.0)
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
    : AmbientLight(),
      Object()
{ }


PointLight::PointLight(const Vector3 &o)
    : AmbientLight(),
      Object(o)
{ }


PointLight::PointLight(const Vector3 &o,
                       const Color &c)
    : AmbientLight(c),
      Object(o)
{ }


PointLight::PointLight(const Vector3 &o,
                       const Color &c,
                       const float &i)
    : AmbientLight(c, i),
      Object(o)
{ }
