/* camera.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <memory>

#include "basics/basics.hh"


namespace charles {

/**
 * The Camera is the eye into the scene. It defines several parameters and a
 * single compute_primary_ray method that generates rays with which the ray
 * tracer draws the scene.
 */
struct Camera
{
    typedef std::shared_ptr<Camera> Ptr;

    Camera();
    Camera(const Camera& other);
    virtual ~Camera();

    basics::Vector4& GetOrigin();
    const basics::Vector4& GetOrigin() const;
    void SetOrigin(const basics::Vector4& origin);

    basics::Vector4& GetDirection();
    const basics::Vector4& GetDirection() const;
    void SetDirection(const basics::Vector4& direction);

    basics::Vector4& GetRight();
    const basics::Vector4& GetRight() const;
    void SetRight(const basics::Vector4& right);

    basics::Vector4& GetUp();
    const basics::Vector4& GetUp() const;
    void SetUp(const basics::Vector4& up);

    /** Get the camera's handedness. Left handed is the default. */
    bool IsLeftHanded() const;

    /** Pan and tilt the camera towards the given point. */
    void LookAt(const basics::Vector4& p);

    virtual basics::Ray PrimaryRay(const int x, const int width,
                                   const int y, const int height) const = 0;

protected:
    virtual std::string GetTypeString() const;

private:
    friend std::ostream& operator<<(std::ostream& ost, const Camera& camera);

    void WriteType(std::ostream& ost) const;

    /**
     * The location of the camera in the scene. Depending on the type of camera,
     * this is the point from which rays will be emitted.
     */
    basics::Vector4 mOrigin;

    /** A vector defining where the camera is pointed. */
    basics::Vector4 mDirection;

    /**
     * A vector defining the width of the camera's image plane. The ratio of
     * this and mUp determine the aspect ratio of the image.
     */
    basics::Vector4 mRight;

    /**
     * A vector defining the height of the camera's image plane. The ratio of
     * this and mRight determine the aspect ratio of the image.
     */
    basics::Vector4 mUp;
};


class PerspectiveCamera
    : public Camera
{
public:
    PerspectiveCamera();
    PerspectiveCamera(const Camera& other);

    basics::Ray PrimaryRay(const int x, const int width,
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

    /**
     * Compute a primary ray given an (x,y) coordinate pair. The orthographic
     * camera projects rays parallel to the viewing direction through the (x,y)
     * coordinate given. Thus, the size of the orthographic camera should be set
     * to the size of the view into the scene.
     */
    basics::Ray PrimaryRay(const int x, const int width,
                           const int y, const int height) const;

private:
    std::string GetTypeString() const;
};


std::ostream& operator<<(std::ostream& ost, const Camera& camera);

} /* namespace charles */

#endif
