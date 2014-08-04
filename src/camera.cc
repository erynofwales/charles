/* camera.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "camera.h"
#include "log.hh"

#define LOG_NAME "camera"
#include "logModule.hh"


#pragma mark - Generic Camera

Camera::Camera()
    : mDirection(Vector3::Z),
      mRight(1.33, 0, 0),
      mUp(Vector3::Y)
{ }


Camera::Camera(const Camera& other)
  : mDirection(other.mDirection),
    mRight(other.mRight),
    mUp(other.mUp)
{ }


Camera::~Camera()
{ }


/*
 * Camera::GetOrigin --
 */
const Vector3&
Camera::GetOrigin()
    const
{
    return mOrigin;
}


/*
 * Camera::SetOrigin --
 */
void
Camera::SetOrigin(const Vector3 &origin)
{
    mOrigin = origin;
}


const Vector3&
Camera::get_direction()
    const
{
    return mDirection;
}

void
Camera::set_direction(const Vector3 &direction)
{
    mDirection = direction;
}


const Vector3&
Camera::GetRight()
    const
{
    return mRight;
}


void
Camera::SetRight(const Vector3& right)
{
    mRight = right;
}


const Vector3&
Camera::GetUp()
    const
{
    return mUp;
}


void
Camera::SetUp(const Vector3& up)
{
    mUp = up;
}


bool
Camera::IsLeftHanded()
    const
{
    /*
     * The cross product of the up and direction vectors is a vector
     * perpendicular to the plane containing those vectors. By definition the
     * right vector is (in almost all cases) perpendicular to that plane.
     *
     * The dot product indicates the angle between this vector and the right
     * vector. If it's greater than 0, then the vector is pointing right of the
     * up-direction plane and the coordinate system is right handed. If less
     * than 0, the vector is pointing left of the up-direction plane and the
     * coordinate system is left-handed.
     */
    return mUp.cross(mDirection).dot(mRight) < 0.0;
}


void
Camera::LookAt(const Vector3& pt)
{
    /*
     * Precalulate these in order to preserve the aspect ratio and orientation
     * of the camera across the LookAt operation.
     */
    const Double directionLength = mDirection.length();
    const Double rightLength = mRight.length();
    const Double upLength = mUp.length();
    const bool isLeftHanded = IsLeftHanded();

    /* Orient the camera towards the point. */
    mDirection = (pt - mOrigin).normalize();
    /* TODO: Check for zero length direction vector. */

    /*
     * Create a new right vector, normalized and perpendicular to the plane
     * containing the Y unit vector and direction vector.
     *
     * The up vector is perpendicular to the plane containing the new right
     * vector and the direction vector.
     *
     * TODO: This is always the Y vector. POV-Ray has a sky vector, which
     * specifies the vector along which LookAt pans and tilts the camera. It
     * might be worth looking into, at some point.
     */
    mRight = Vector3::Y.cross(mDirection).normalize();
    mUp = mDirection.cross(mRight);

    /*
     * Now, fix up the direction, right, and up vectors so that their magnitudes
     * match what they were before the move.
     */
    mDirection *= directionLength;
    mRight *= isLeftHanded ? rightLength : -rightLength;
    mUp *= upLength;

    LOG_DEBUG << "Camera is looking at " << pt;
}


std::string
Camera::GetTypeString()
    const
{
    return "GENERIC";
}


void
Camera::WriteType(std::ostream& ost)
    const
{
    ost << GetTypeString();
}

#pragma mark - Perspective Camera

PerspectiveCamera::PerspectiveCamera()
    : Camera()
{ }


PerspectiveCamera::PerspectiveCamera(const Camera& other)
    : Camera(other)
{ }


Ray
PerspectiveCamera::compute_primary_ray(const int x,
                                       const int width,
                                       const int y,
                                       const int height)
    const
{
    /*
     * Center x and y in the pixel and convert them to be coordinates between
     * -0.5 and 0.5.
     */
    double x0 = (x + 0.5) / width - 0.5;
    double y0 = ((height - 1.0) - (y - 0.5)) / height - 0.5;

    Vector3 direction = LinearCombination(1.0, get_direction(),
                                          x0, GetRight(),
                                          y0, GetUp());
    return Ray(GetOrigin(), direction.normalize());
}


std::string
PerspectiveCamera::GetTypeString()
    const
{
    return "perspective";
}

#pragma mark - Orthographic Camera

OrthographicCamera::OrthographicCamera()
    : Camera()
{ }


OrthographicCamera::OrthographicCamera(const Camera& other)
    : Camera(other)
{ }


/*
 * OrthographicCamera::compute_primary_ray --
 */
/**
 * Compute a primary ray given an (x,y) coordinate pair. The orthographic camera
 * projects rays parallel to the viewing direction through the (x,y) coordinate
 * given. Thus, the size of the orthographic camera should be set to the size of
 * the view into the scene.
 */
Ray
OrthographicCamera::compute_primary_ray(const int x,
                                        const int width,
                                        const int y,
                                        const int height)
    const
{
    /*
     * Center x and y in the pixel and convert them to be coordinates between
     * -0.5 and 0.5.
     */
    double x0 = (x + 0.5) / width + 0.5;
    double y0 = ((height - 1.0) - (y - 0.5)) / height - 0.5;

    Vector3 origin = LinearCombination(1.0, GetOrigin(),
                                       x0, GetRight(),
                                       y0, GetUp());
    return Ray(origin, get_direction());
}


std::string
OrthographicCamera::GetTypeString()
    const
{
    return "orthographic";
}


std::ostream&
operator<<(std::ostream& ost,
           const Camera& camera)
{
    ost << "[Camera ";
    camera.WriteType(ost);
    ost << " origin=" << camera.mOrigin
        << " direction=" << camera.mDirection
        << " right=" << camera.mRight
        << " up=" << camera.mUp
        << "]";
    return ost;
}
