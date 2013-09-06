/* scene.h
 *
 * Definition of Scene type and related functions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __SCENE_H__
#define __SCENE_H__

#include <stdio.h>
#include "basics.h"


typedef struct _Scene
{
    int height, width;      /* Pixel dimensions. */
} Scene;


Scene *scene_init();
void scene_destroy(Scene *scene);
void scene_load(Scene *scene, FILE *scene_file);
void scene_render(Scene *scene);


#endif
