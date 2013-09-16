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
      direction(Vector3::Z)
{ }


Camera::~Camera()
{ }

#pragma mark - Orthographic Camera

/*
 * OrthographicCamera::compute_primary_ray --
 *
 * Compute a primary ray given an (x,y) coordinate pair. The orthographic camera projects rays parallel to the viewing
 * direction through the (x,y) coordinate given. Thus, the size of the orthographic camera should be set to the size of
 * the view into the scene.
 */
Ray
OrthographicCamera::compute_primary_ray(const int &x,
                                        const int &y)
    const
{
    return 0;
}
