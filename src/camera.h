/* camera.h
 *
 * The Camera is the eye into the scene. It defines several parameters and a single compute_primary_ray method
 * that generates rays with which the ray tracer draws the scene.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "basics.h"
#include "object.h"


class Camera
    : public Object
{
public:
    Camera();
    ~Camera();

    virtual Ray compute_primary_ray(const int &x, const int &y) const = 0;

private:
    // Size of the image plane.
    Vector3 height, width;

    // Direction. A unit vector defining where the camera is pointed.
    Vector3 direction;

    // Horizontal viewing angle.
    float angle;
};


class OrthographicCamera
{
public:
    Ray compute_primary_ray(const int &x, const int &y) const;
};


#endif
