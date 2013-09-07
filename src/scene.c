/* scene.c
 *
 * Definition of Scene-related functions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#include <math.h>
#include <stdlib.h>
#include "scene.h"


Color _scene_trace(Scene *scene, const Ray ray, const int depth);


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
    scene->pixels = malloc(sizeof(Color) * scene->height * scene->width);
    if (scene->pixels == NULL) {
        // TODO: Print an error.
        return;
    }

    float fov = 30.0;
    float aspect_ratio = scene->width / scene->height;
    float angle = tan(M_PI * 0.5 * fov / 180.0);

    float xx, yy;
    Ray primary_ray;
    Vector3 direction;
    for (int y = 0; y < scene->height; y++) {
        for (int x = 0; x < scene->width; x++) {
            // Compute (x, y) of ray direction.
            xx = (2 * ((x + 0.5) / scene->width) - 1) * angle * aspect_ratio;
            yy = (1 - 2 * ((y + 0.5) / scene->height)) * angle;

            // Assemble a ray and trace it.
            direction = vector_init(xx, yy, 1);
            primary_ray = ray_init(ZeroVector3, direction);
            scene->pixels[y * scene->height + x] = _scene_trace(scene, primary_ray, 0);
        }
    }
}


Color
_scene_trace(Scene *scene, const Ray ray, const int depth)
{
    Color out_color;
    out_color.red = 0;
    out_color.blue = 0;
    out_color.green = 0;
    out_color.alpha = 255;

    return out_color;
}
