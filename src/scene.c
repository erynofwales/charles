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
