/* material.h
 *
 * Materials are applied to shapes and determine color, texture mapping, shading, etc.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "basics.h"
#include "types.hh"

namespace charles {

struct Material
{
    enum class DiffuseShaderModel {
        Lambert,
    };

    enum class SpecularShaderModel {
        Blinn,
        Phong
    };

    Material();

    Double GetDiffuseIntensity() const;
    void SetDiffuseIntensity(const Double& kd);

    const Color& GetDiffuseColor() const;
    void SetDiffuseColor(const Color& c);

    Double GetSpecularIntensity() const;
    void SetSpecularIntensity(const Double& kd);

    const Color &GetSpecularColor() const;
    void SetSpecularColor(const Color& c);

private:
    void ClampParameter(Double& param);

    // Diffuse parameters.
    DiffuseShaderModel mDiffuseModel;
    Double mDiffuseIntensity;
    Color mDiffuseColor;

    // Specular parameters.
    SpecularShaderModel mSpecularModel;
    Double mSpecularIntensity;
    Color mSpecularColor;
};

} /* namespace charles */

#endif
