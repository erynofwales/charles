/* camera.h
 *
 * The Camera is the eye into the scene. It defines several parameters and a single compute_primary_ray method
 * that generates rays with which the ray tracer draws the scene.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include "camera.h"


#pragma mark - Generic Camera

Camera::Camera()
    : height(Vector3::Y),
      width(4.0 / 3.0 * Vector3::X),
      direction(Vector3::Z),
      mRight(1.33, 0, 0),
      mUp(Vector3::Y)
{ }


Camera::~Camera()
{ }


/*
 * Camera::get_width --
 * Camera::set_width --
 * Camera::get_height --
 * Camera::set_height --
 *
 * Get and set width and height vectors.
 */
const Vector3 &
Camera::get_width()
    const
{
    return width;
}

void
Camera::set_width(const Vector3 &w)
{
    width = w;
}

const Vector3 &
Camera::get_height()
    const
{
    return height;
}

void
Camera::set_height(const Vector3 &h)
{
    height = h;
}


/*
 * Camera::get_direction --
 * Camera::set_direction --
 *
 * Get and set direction vector.
 */
const Vector3 &
Camera::get_direction()
    const
{
    return direction;
}

void
Camera::set_direction(const Vector3 &d)
{
    direction = d;
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

#pragma mark - Perspective Camera

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
    return Ray(get_origin(), direction);
}

#pragma mark - Orthographic Camera

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
    // Calculate the point on the image plane that the given (x,y) coordinate pair corresponds to.
    float dir_x = (x / width) + 0.5;
    float dir_y = (y / height) + 0.5;
    Vector3 ray_origin = (dir_x * get_width()) + (dir_y * get_height()) + get_direction();

    // Calculate the direction of the ray, given the camera's origin and normalize that vector.
    Vector3 ray_direction = (ray_origin - get_origin()).normalize();

    return Ray(ray_origin, ray_direction);
}
