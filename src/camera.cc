/* camera.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "camera.h"


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
    /* TODO: What does this actually do? */
    const Double handedness = mUp.cross(mDirection).dot(mRight);

    mDirection = (pt - mOrigin).normalize();
    /* TODO: Check for zero length direction vector. */

    /*
     * TODO: This is always the Y vector. POV-Ray has a sky vector, which
     * specifies the vector along which LookAt pans and tilts the camera. It
     * might be worth looking into, at some point.
     */
    mRight = Vector3::Y.cross(mDirection).normalize();
    mUp = mDirection.cross(mRight);

    mDirection *= directionLength;
    mRight *= (handedness > 0.0) ? rightLength : -rightLength;
    mUp *= upLength;
}


void
Camera::WriteType(std::ostream& ost)
    const
{
    ost << "UNKNOWN";
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


void
PerspectiveCamera::WriteType(std::ostream& ost)
    const
{
    ost << "perspective";
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


void
OrthographicCamera::WriteType(std::ostream& ost)
    const
{
    ost << "orthographic";
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
