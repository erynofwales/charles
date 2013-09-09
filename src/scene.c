/* scene.c
 *
 * Definition of Scene-related functions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#include <math.h>
#include <stdlib.h>

#include "scene.h"
#include "texture.h"


struct _ObjectList
{
    Object *object;
    ObjectList *next;
};


static Color scene_trace_ray(Scene *scene, const Ray ray, const int depth);


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
    scene->width = 640;
    scene->height = 480;

    scene->pixels = malloc(sizeof(Color) * scene->height * scene->width);
    if (scene->pixels == NULL) {
        // TODO: Print an error.
        return;
    }

    Ray primary_ray;
    Vector3 location, direction;
    for (int y = 0; y < scene->height; y++) {
        for (int x = 0; x < scene->width; x++) {
            // Assemble a ray and trace it.
            location = vector_init(x, y, -1000);
            direction = vector_init(0, 0, 1);
            primary_ray = ray_init(location, vector_normalize(direction));
            scene->pixels[y * scene->width + x] = scene_trace_ray(scene, primary_ray, 0);
        }
    }

    scene->is_rendered = 1;
}


/*
 * scene_add_object --
 *
 * Add an Object to the Scene.
 */
void
scene_add_object(Scene *scene, Object *obj)
{
    ObjectList *ol = malloc(sizeof(ObjectList));
    if (ol == NULL) {
        return;
    }

    ol->object = obj;
    ol->next = NULL;

    if (scene->objects == NULL) {
        scene->objects = ol;
        return;
    }

    ObjectList *ptr = scene->objects;
    while (ptr != NULL) {
        if (ptr->next == NULL) {
            ptr->next = ol;
            break;
        }
        ptr = ptr->next;
    }
}


/* static */ Color
scene_trace_ray(Scene *scene, const Ray ray, const int depth)
{
    Color out_color = {0, 0, 0};

    // Find intersections of this ray with objects in the scene.
    Object *intersected_obj = NULL;
    float *t = NULL;
    float nearest_t = INFINITY;
    int nints;
    ObjectList *ptr = scene->objects;
    while (ptr != NULL) {
        nints = object_does_intersect(ptr->object, ray, &t);
        if (nints > 0) {
            for (int i = 0; i < nints; i++) {
                if (t[i] < nearest_t) {
                    intersected_obj = ptr->object;
                    nearest_t = t[i];
                }
            }
            free(t);
        }
        ptr = ptr->next;
    }

    // If there was no intersection, return black.
    if (intersected_obj == NULL) {
        return out_color;
    }

    // TODO: Lighting.

    Texture *tex = object_get_texture(intersected_obj);
    return texture_get_color(tex);
}
