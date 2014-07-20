/* camera.h
 *
 * The Camera is the eye into the scene. It defines several parameters and a
 * single compute_primary_ray method that generates rays with which the ray
 * tracer draws the scene.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "basics.h"
#include "object.h"


struct Camera
    : public Object
{
public:
    Camera();
    Camera(const Camera& other);
    virtual ~Camera();

    const Vector3 &get_direction() const;
    void set_direction(const Vector3 &d);
    float get_angle() const;

    const Vector3& GetRight() const;
    void SetRight(const Vector3& right);
    const Vector3& GetUp() const;
    void SetUp(const Vector3& up);

    virtual Ray compute_primary_ray(const int x, const int width,
                                    const int y, const int height) const = 0;

private:
    /** A normalized vector defining where the camera is pointed. */
    Vector3 mDirection;

    /**
     * A vector defining the width of the camera's image plane. The ratio of
     * this and mUp determine the aspect ratio of the image.
     */
    Vector3 mRight;

    /**
     * A vector defining the height of the camera's image plane. The ratio of
     * this and mUp determine the aspect ratio of the image.
     */
    Vector3 mUp;
};


class PerspectiveCamera
    : public Camera
{
    Ray compute_primary_ray(const int x, const int width,
                            const int y, const int height) const;
};


class OrthographicCamera
    : public Camera
{
public:
    Ray compute_primary_ray(const int x, const int width,
                            const int y, const int height) const;
};


#endif
