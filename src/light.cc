/* light.cc
 *
 * Lights light the scene.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include "basics.h"
#include "light.h"
#include "object.h"


Light::Light()
    : Light(1.0)
{ }


Light::Light(float i)
    : Light(Vector3::Zero, i)
{ }


Light::Light(Vector3 o, float i)
    : Object(o),
      intensity(i)
{ }


/*
 * Light::get_intensity --
 * Light::set_intensity --
 *
 * Get and set the intensity of this light.
 */
float
Light::get_intensity()
    const
{
    return intensity;
}

void
Light::set_intensity(float i)
{
    intensity = i;
}
