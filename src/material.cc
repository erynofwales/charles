/* material.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "material.hh"


using charles::basics::Color;


namespace charles {

Material::Material()
    : mDiffuseModel(DiffuseShaderModel::Lambert),
      mDiffuseIntensity(0.8),
      mDiffuseColor(Color::White),
      mSpecularModel(SpecularShaderModel::Phong),
      mSpecularIntensity(0.0),
      mSpecularColor(Color::White)
{ }


Double
Material::GetDiffuseIntensity()
    const
{
    return mDiffuseIntensity;
}


void
Material::SetDiffuseIntensity(const Double& kd)
{
    mDiffuseIntensity = kd;
    ClampParameter(mDiffuseIntensity);
}


Color&
Material::GetDiffuseColor()
{
    return mDiffuseColor;
}


void
Material::SetDiffuseColor(const Color& color)
{
    mDiffuseColor = color;
}


Double
Material::GetSpecularIntensity()
    const
{
    return mSpecularIntensity;
}


void
Material::SetSpecularIntensity(const Double& ks)
{
    mSpecularIntensity = ks;
    ClampParameter(mSpecularIntensity);
}


Color&
Material::GetSpecularColor()
{
    return mSpecularColor;
}


void
Material::SetSpecularColor(const Color& color)
{
    mSpecularColor = color;
}


void
Material::ClampParameter(Double& param)
{
    if (param < 0.0) {
        param = 0.0;
    }
    else if (param > 1.0) {
        param = 1.0;
    }
}

} /* namespace charles */
