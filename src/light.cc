/* light.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "light.hh"


using charles::basics::Color;


namespace charles {

Light::Light(const Color& color,
             const Double& intensity)
    : mColor(color),
      mIntensity(ClampIntensity(intensity))
{ }


Color&
Light::GetColor()
{
    return mColor;
}


const Color&
Light::GetColor()
    const
{
    return mColor;
}


void
Light::SetColor(const Color& color)
{
    mColor = color;
}


Double
Light::GetIntensity()
    const
{
    return mIntensity;
}


void
Light::SetIntensity(const Double& intensity)
{
    mIntensity = ClampIntensity(intensity);
}


Color&&
Light::Contribution()
    const
{
    return mColor * mIntensity;
}


Double
Light::ClampIntensity(const Double& intensity)
{
    if (intensity < 0.0) {
        return 0.0;
    } else if (intensity > 1.0) {
        return 1.0;
    }
    return intensity;
}

} /* namespace charles */
