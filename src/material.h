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
    enum {
        DiffuseLightingTypeLambert = 1,
    } DiffuseLightingType;

    Material();

    float get_diffuse_level() const;
    void set_diffuse_level(const float &kd);
    const Color &get_diffuse_color() const;
    void set_diffuse_color(const Color &c);

    float get_specular_level() const;
    void set_specular_level(const float &kd);
    const Color &get_specular_color() const;
    void set_specular_color(const Color &c);

private:
    void _clamp_parameter(float &param);

    // Diffuse parameters.
    float diffuse_level;
    Color diffuse_color;

    // Specular parameters.
    float specular_level;
    Color specular_color;
};

#endif
