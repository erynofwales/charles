/* scene.h
 *
 * Definition of Scene type and related functions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __SCENE_H__
#define __SCENE_H__

#include "basics.h"


typedef struct _Scene
{
    int height, width;      /* Pixel dimensions. */
} Scene;


void scene_init(Scene *scene);
void scene_destroy(Scene *scene);
void scene_render(Scene *scene);


#endif
