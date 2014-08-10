/* light.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <memory>

#include "basics/basics.hh"


namespace charles {

struct Light
{
    typedef std::shared_ptr<Light> Ptr;

    Light(const basics::Color& color,
          const Double& intensity = 1.0);

    basics::Color& GetColor();
    const basics::Color& GetColor() const;
    void SetColor(basics::Color& color);

    Double GetIntensity() const;
    void SetIntensity(const Double& intensity);

    virtual basics::Color&& Contribution() const;

private:
    Double ClampIntensity(const Double& intensity);

    /** The color of the light. */
    basics::Color mColor;

    /**
     * The intensity of the light. Normal values range from 0.0 to 1.0, but
     * they can be set higher.
     */
    Double mIntensity;
};


typedef Light AmbientLight;

} /* namespace charles */

#endif
