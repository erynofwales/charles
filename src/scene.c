/* scene.c
 *
 * Definition of Scene-related functions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#include <stdlib.h>
#include "scene.h"


/*
 * scene_init --
 *
 * Initialize and return a new Scene. If the Scene could not be created, NULL is returned.
 */
Scene *
scene_init()
{
    Scene *new_scene = malloc(sizeof(Scene));
    if (!new_scene) {
        return NULL;
    }

    // Set some default values.
    new_scene->height = 0;
    new_scene->width = 0;
    new_scene->camera = camera_init();

    return new_scene;
}


/*
 * scene_destroy --
 *
 * Cleanup a Scene.
 */
void
scene_destroy(Scene *scene)
{
    if (scene == NULL) {
        return;
    }

    camera_destroy(scene->camera);
    free(scene);
}


/*
 * scene_load --
 *
 * Load a scene from a file into the given Scene object.
 */
void
scene_load(Scene *scene, FILE *scene_file)
{ }


/*
 * scene_render --
 *
 * Render the given Scene.
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
