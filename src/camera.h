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
    virtual ~Camera();

    const Vector3 &get_width() const;
    void set_width(const Vector3 &w);
    const Vector3 &get_height() const;
    void set_height(const Vector3 &h);
    const Vector3 &get_direction() const;
    void set_direction(const Vector3 &d);
    float get_angle() const;

    virtual Ray compute_primary_ray(const int &x, const int &y) const = 0;
    const Vector3& GetRight() const;
    void SetRight(const Vector3& right);
    const Vector3& GetUp() const;
    void SetUp(const Vector3& up);


private:
    // Size of the image plane.
    Vector3 height, width;

    // Direction. A normalized vector defining where the camera is pointed.
    Vector3 direction;
    Vector3 mRight;
    Vector3 mUp;

};


class OrthographicCamera
    : public Camera
{
public:
    Ray compute_primary_ray(const int &x, const int &y) const;
};


#endif
