/* material.h
 *
 * Materials are applied to shapes and determine color, texture mapping, shading, etc.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "basics.h"


class Material
{
public:
    Color get_color() const;
    void set_color(const Color &c);

private:
    Color color;
};

#endif
