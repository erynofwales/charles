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

#include <memory>

#include "basics.h"


struct Camera
{
    typedef std::shared_ptr<Camera> Ptr;

    Camera();
    Camera(const Camera& other);
    virtual ~Camera();

    const Vector3& GetOrigin() const;
    void SetOrigin(const Vector3& origin);

    const Vector3& get_direction() const;
    void set_direction(const Vector3& direction);

    const Vector3& GetRight() const;
    void SetRight(const Vector3& right);

    const Vector3& GetUp() const;
    void SetUp(const Vector3& up);

    /**
     * Get the camera's handedness. Left handed is the default.
     *
     * @returns `true` if the camera is set up for left-handed coordinates.
     */
    bool IsLeftHanded() const;

    /**
     * Pan and tilt the camera towards the given point.
     *
     * @param [in] pt   The point at which to face the camera
     */
    void LookAt(const Vector3& pt);

    virtual Ray compute_primary_ray(const int x, const int width,
                                    const int y, const int height) const = 0;

    virtual std::string GetTypeString() const;

private:
    friend std::ostream& operator<<(std::ostream& ost, const Camera& camera);

    void WriteType(std::ostream& ost) const;

    /**
     * The location of the camera in the scene. Depending on the type of camera,
     * this is the point from which rays will be emitted.
     */
    Vector3 mOrigin;

    /** A normalized vector defining where the camera is pointed. */
    Vector3 mDirection;

    /**
     * A vector defining the width of the camera's image plane. The ratio of
     * this and mUp determine the aspect ratio of the image.
     */
    Vector3 mRight;

    /**
     * A vector defining the height of the camera's image plane. The ratio of
     * this and mRight determine the aspect ratio of the image.
     */
    Vector3 mUp;
};


class PerspectiveCamera
    : public Camera
{
public:
    PerspectiveCamera();
    PerspectiveCamera(const Camera& other);

    Ray compute_primary_ray(const int x, const int width,
                            const int y, const int height) const;

private:
    std::string GetTypeString() const;
};


class OrthographicCamera
    : public Camera
{
public:
    OrthographicCamera();
    OrthographicCamera(const Camera& other);

    Ray compute_primary_ray(const int x, const int width,
                            const int y, const int height) const;

private:
    std::string GetTypeString() const;
};


std::ostream& operator<<(std::ostream& ost, const Camera& camera);

#endif
