/* material.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __MATERIAL_HH__
#define __MATERIAL_HH__

#include "basics/basics.hh"


namespace charles {

/**
 * Materials are applied to shapes and determine color, texture mapping,
 * shading, etc.
 */
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

    basics::Color& GetDiffuseColor();
    void SetDiffuseColor(const basics::Color& c);

    Double GetSpecularIntensity() const;
    void SetSpecularIntensity(const Double& kd);

    basics::Color& GetSpecularColor();
    void SetSpecularColor(const basics::Color& c);

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
