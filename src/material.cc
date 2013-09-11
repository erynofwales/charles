/* material.h
 *
 * Materials are applied to shapes and determine color, texture mapping, shading, etc.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include "material.h"


Color
Material::get_color()
    const
{
    return color;
}


void
Material::set_color(const Color &c)
{
    color = c;
}
