/* camera.c
 *
 * Camera definitions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <stdlib.h>
#include "camera.h"


Camera *
camera_init()
{
    Camera *new_camera = malloc(sizeof(Camera));
    if (new_camera == NULL) {
        return NULL;
    }

    // Set some useful defaults.
    new_camera->projection = CameraProjectionOrthographic;
    new_camera->location = vector_init(0, 0, 0);
    // The default image plane is a rectangle from (-1, 1) to (1, -1).
    new_camera->image_plane = rect_init(-1, 1, 2, 2);

    return new_camera;
}


void
camera_destroy(Camera *camera)
{
    if (camera == NULL) {
        return;
    }

    free(camera);
}
