/* scene.c
 *
 * Definition of Scene-related functions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#include "scene.h"


/*
 * scene_init --
 */
void
scene_init(Scene *scene)
{
    scene->height = 0;
    scene->width = 0;
}


/*
 * scene_destroy --
 */
void
scene_destroy(Scene *scene)
{ }


/*
 * scene_render --
 */
void
scene_render(Scene *scene)
{
    for (int y = 0; y < scene->height; y++) {
        for (int x = 0; x < scene->width; x++) {
            // TODO: Process the scene.
        }
    }
}
