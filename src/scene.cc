/* scene.c
 *
 * Definition of Scene-related functions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cmath>
#include <cstdio>

#include "basics.h"
#include "light.h"
#include "object.h"
#include "scene.h"
#include "writer.h"


Scene::Scene()
    : width(640), height(480),
      max_depth(5),
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


int
Scene::get_width()
    const
{
    return width;
}


int
Scene::get_height()
    const
{
    return height;
}


const Color *
Scene::get_pixels()
    const
{
    return pixels;
}


/*
 * scene_load --
 *
 * Load scene objects into this Scene from the given file.
 */
void
Scene::read(const std::string &filename)
{ }


/*
 * scene_save --
 *
 * Write a rendered scene to the given file.
 */
void
Scene::write(Writer &writer, const std::string &filename)
{
    writer.write_scene(*this, filename);
}


/*
 * Scene::render --
 *
 * Render the given Scene.
 */
void
Scene::render()
{
    pixels = new Color[width * height];

    Ray primary_ray;
    Vector3 o, d;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Assemble a ray and trace it.
            o = Vector3(x, y, -1000);
            d = Vector3(0, 0, 1);
            d.normalize();
            primary_ray = Ray(o, d);
            Color c = trace_ray(primary_ray, 0);
            pixels[y * width + x] = c;
        }
    }

    _is_rendered = true;
}


/*
 * Scene::add_shape --
 *
 * Add a shape to the scene.
 */
void
Scene::add_shape(Shape *shape)
{
    shapes.push_back(shape);
}


/*
 * Scene::add_light --
 *
 * Add a light to the scene.
 */
void
Scene::add_light(Light *light)
{
    lights.push_back(light);
}


/*
 * Scene::trace_ray --
 *
 * Trace the given ray through the scene, recursing until depth has been reached.
 */
Color
Scene::trace_ray(const Ray &ray, const int depth)
{
    Shape *intersected_shape = NULL;
    float *t = NULL;
    float nearest_t = INFINITY;
    int nints;

    // Find intersections of this ray with objects in the scene.
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
        return Color::Black;
    }

    Color out_color = intersected_shape->get_material().get_color();

    Vector3 intersection = ray.parameterize(nearest_t);
    Vector3 normal = intersected_shape->compute_normal(intersection);

    for (Light *l : lights) {
        Vector3 light_direction = intersection - l->get_origin();
        light_direction.normalize();

        float ldotn = light_direction.dot(normal);
        out_color.red *= ((ldotn >= 0.0) ? ldotn : 0.0) * l->get_intensity();
        out_color.green *= ((ldotn >= 0.0) ? ldotn : 0.0) * l->get_intensity();
        out_color.blue *= ((ldotn >= 0.0) ? ldotn : 0.0) * l->get_intensity();
    }

    return out_color;
}
