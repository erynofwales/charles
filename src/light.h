/* light.h
 *
 * Lights light the scene.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "object.h"


class Light
    : public Object
{
public:
    Light();
    Light(float i);
    Light(Vector3 o, float i);

    float get_intensity() const;
    void set_intensity(float i);

private:
    float intensity;
};

#endif
