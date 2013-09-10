/* scene.c
 *
 * Definition of Scene-related functions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cmath>
#include "basics.h"
#include "object.h"
#include "scene.h"


Scene::Scene()
    : height(640), width(480),
      pixels(NULL)
{ }


Scene::~Scene()
{
    if (pixels != NULL) {
        delete[] pixels;
        _is_rendered = false;
    }
}


bool
Scene::is_rendered()
    const
{
    return _is_rendered;
}


/*
 * scene_load --
 *
 * Load scene objects into this Scene from the given file.
 */
void
Scene::read(FILE *file)
{ }


/*
 * scene_save --
 *
 * Write a rendered scene to the given file.
 */
void
Scene::write(FILE *file)
{ }


/*
 * Scene::render --
 *
 * Render the given Scene.
 */
void
Scene::render()
{
    pixels = new Color[width * height];
    if (pixels == NULL) {
        // TODO: Print an error.
        return;
    }

    Ray primary_ray;
    Vector3 o, d;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Assemble a ray and trace it.
            o = Vector3(x, y, -1000);
            d = Vector3(0, 0, 1);
            d.normalize();
            primary_ray = Ray(o, d);
            pixels[y * width + x] = trace_ray(primary_ray, 0);
        }
    }

    _is_rendered = true;
}


void
Scene::add_shape(Shape *shape)
{
    shapes.push_back(shape);
}


Color
Scene::trace_ray(const Ray &ray, const int depth)
{
    Color out_color = Color::Black;

    // Find intersections of this ray with objects in the scene.
    Shape *intersected_shape = NULL;
    float *t = NULL;
    float nearest_t = INFINITY;
    int nints;
    for (Shape *s : shapes) {
        nints = s->does_intersect(ray, &t);
        if (nints > 0) {
            for (int i = 0; i < nints; i++) {
                if (t[i] < nearest_t) {
                    intersected_shape = s;
                    nearest_t = t[i];
                }
            }
            delete[] t;
        }
    }

    // If there was no intersection, return black.
    if (intersected_shape == NULL) {
        return out_color;
    }

    // TODO: Lighting.

    return Color::Red;
}
