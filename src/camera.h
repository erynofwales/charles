/* camera.h
 *
 * Camera type and related functions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __CAMERA_H
#define __CAMERA_H

#include "basics.h"


typedef enum {
    CameraProjectionOrthographic = 1,
} CameraProjection;


typedef struct _Camera
{
    CameraProjection projection;
    Vector3 location;
    Rect image_plane;
} Camera;


Camera *camera_init();
void camera_destroy(Camera *camera);


#endif
