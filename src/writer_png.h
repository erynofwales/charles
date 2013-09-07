/* writer_png.h
 *
 * Declaration of the PNG writer.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#ifndef __WRITER_PNG_H
#define __WRITER_PNG_H

#include <stdio.h>
#include "scene.h"


int write_scene_png(Scene *scene, FILE *file);


#endif
