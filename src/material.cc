/* material.h
 *
 * Materials are applied to shapes and determine color, texture mapping, shading, etc.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include "material.h"


Material::Material()
    : diffuse_level(1.0),
      diffuse_color(Color::Black)
{ }


float
Material::get_diffuse_level()
    const
{
    return diffuse_level;
}


void
Material::set_diffuse_level(const float &kd)
{
    diffuse_level = kd;
    _clamp_parameter(diffuse_level);
}


const Color &
Material::get_diffuse_color()
    const
{
    return diffuse_color;
}


void
Material::set_diffuse_color(const Color &c)
{
    diffuse_color = c;
}


void
Material::_clamp_parameter(float &param)
{
    if (param < 0.0) {
        param = 0.0;
    }
    else if (param > 1.0) {
        param = 1.0;
    }
}
