/* material.h
 *
 * Materials are applied to shapes and determine color, texture mapping, shading, etc.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include "material.h"


Material::Material()
    : diffuse_level(0.8),
      diffuse_color(Color::White),
      specular_level(0.5),
      specular_color(Color::White)
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


float
Material::get_specular_level()
    const
{
    return specular_level;
}


void
Material::set_specular_level(const float &ks)
{
    specular_level = ks;
    _clamp_parameter(specular_level);
}


const Color &
Material::get_specular_color()
    const
{
    return specular_color;
}


void
Material::set_specular_color(const Color &c)
{
    specular_color = c;
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
