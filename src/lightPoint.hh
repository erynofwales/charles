/* lightPoint.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __LIGHTPOINT_HH__
#define __LIGHTPOINT_HH__

#include "light.hh"


namespace charles {

/**
 * The simplest light source. Emits light in all directions uniformly, without
 * falloff.
 */
class PointLight
    : public Light
{
public:
    PointLight(const basics::Vector4 &origin,
               const basics::Color& color,
               const Double& intensity);

    basics::Vector4& GetOrigin();
    void SetOrigin(const basics::Vector4& origin);

private:
    basics::Vector4 mOrigin;
};

} /* namespace charles */

#endif /* __LIGHTPOINT_HH__ */
