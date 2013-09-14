/* light.h
 *
 * Lights light the scene.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "basics.h"
#include "object.h"


class AmbientLight
{
public:
    AmbientLight();
    AmbientLight(const Color &c);
    AmbientLight(const Color &c, const float &i);

    const Color &get_color() const;
    const float &get_intensity() const;
    void set_intensity(const float &i);

    Color compute_color_contribution() const;

protected:
    Color color;
    float intensity;

private:
    void _clamp_intensity();
};


class PointLight
    : public AmbientLight,
      public Object
{
public:
    PointLight();
    PointLight(const Vector3 &o);
    PointLight(const Vector3 &o, const Color &c);
    PointLight(const Vector3 &o, const Color &c, const float &i);
};

#endif
