/* camera.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "camera.hh"
#include "log.hh"

#define LOG_NAME "camera"
#include "logModule.hh"


using charles::basics::Ray;
using charles::basics::Vector4;


namespace charles {

#pragma mark - Generic Camera

/*
 * charles::Camera::Camera --
 */
Camera::Camera()
    : mDirection(0, 0, 1),
      mRight(1.33, 0, 0),
      mUp(0, 1, 0)
{ }


/*
 * charles::Camera::Camera --
 */
Camera::Camera(const Camera& rhs)
  : mOrigin(rhs.mOrigin),
    mDirection(rhs.mDirection),
    mRight(rhs.mRight),
    mUp(rhs.mUp)
{ }


/*
 * charles::Camera::~Camera --
 */
Camera::~Camera()
{ }


/*
 * Camera::GetOrigin --
 */
Vector4&
Camera::GetOrigin()
{
    return mOrigin;
}


/*
 * Camera::GetOrigin --
 */
const Vector4&
Camera::GetOrigin()
    const
{
    return mOrigin;
}


/*
 * Camera::SetOrigin --
 */
void
Camera::SetOrigin(const Vector4& origin)
{
    mOrigin = origin;
}


/*
 * Camera::GetDirection --
 */
Vector4&
Camera::GetDirection()
{
    return mDirection;
}


/*
 * Camera::GetDirection --
 */
const Vector4&
Camera::GetDirection()
    const
{
    return mDirection;
}


/*
 * Camera::SetDirection --
 */
void
Camera::SetDirection(const Vector4& direction)
{
    mDirection = direction;
}


/*
 * Camera::GetRight --
 */
Vector4&
Camera::GetRight()
{
    return mRight;
}


/*
 * Camera::GetRight --
 */
const Vector4&
Camera::GetRight()
    const
{
    return mRight;
}


/*
 * Camera::SetRight --
 */
void
Camera::SetRight(const Vector4& right)
{
    mRight = right;
}


/*
 * Camera::GetUp --
 */
Vector4&
Camera::GetUp()
{
    return mUp;
}


/*
 * Camera::GetUp --
 */
const Vector4&
Camera::GetUp()
    const
{
    return mUp;
}


/*
 * Camera::SetUp --
 */
void
Camera::SetUp(const Vector4& up)
{
    mUp = up;
}


/*
 * Camera::IsLeftHanded --
 */
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
    return mUp.Cross(mDirection).Dot(mRight) < 0.0;
}


/*
 * Camera::LookAt --
 */
void
Camera::LookAt(const Vector4& p)
{
    /*
     * Precalulate these in order to preserve the aspect ratio and orientation
     * of the camera across the LookAt operation.
     */
    const Double directionLength = mDirection.Length();
    const Double rightLength = mRight.Length();
    const Double upLength = mUp.Length();
    const bool isLeftHanded = IsLeftHanded();

    /* Orient the camera towards the point. */
    mDirection = basics::Normalized(p - mOrigin);
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
    mRight = basics::Normalized(Vector4(0, 1, 0).Cross(mDirection));
    mUp = mDirection.Cross(mRight);

    /*
     * Now, fix up the direction, right, and up vectors so that their magnitudes
     * match what they were before the move.
     */
    mDirection *= directionLength;
    mRight *= isLeftHanded ? rightLength : -rightLength;
    mUp *= upLength;

    LOG_DEBUG << "Camera is looking at " << p;
}


/*
 * charles::Camera::GetTypeString --
 */
std::string
Camera::GetTypeString()
    const
{
    return "GENERIC";
}


/*
 * charles::Camera::WriteType --
 */
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
PerspectiveCamera::PrimaryRay(const int x,
                              const int width,
                              const int y,
                              const int height)
    const
{
    /*
     * Center x and y in the pixel and convert them to be coordinates between
     * -0.5 and 0.5.
     */
    Double x0 = (x + 0.5) / width - 0.5;
    Double y0 = ((height - 1.0) - (y - 0.5)) / height - 0.5;

    Vector4 direction = LinearCombination(1.0, GetDirection(),
                                          x0, GetRight(),
                                          y0, GetUp());
    return Ray(GetOrigin(), basics::Normalized(direction));
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
Ray
OrthographicCamera::PrimaryRay(const int x,
                               const int width,
                               const int y,
                               const int height)
    const
{
    /*
     * Center x and y in the pixel and convert them to be coordinates between
     * -0.5 and 0.5.
     */
    Double x0 = (x + 0.5) / width + 0.5;
    Double y0 = ((height - 1.0) - (y - 0.5)) / height - 0.5;

    Vector4 origin = LinearCombination(1.0, GetOrigin(),
                                       x0, GetRight(),
                                       y0, GetUp());
    return Ray(origin, GetDirection());
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

} /* namespace charles */
