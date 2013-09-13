/* scene.h
 *
 * Definition of the Scene class.
 *
 * Scenes are the top level object in charles. Scenes contain objects, lights, a camera,
 * etc. and can be rendered to pixel data and written to a file.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __SCENE_H__
#define __SCENE_H__

#include <list>
#include <string>
#include "basics.h"


class AmbientLight;
class PointLight;
class Shape;
class Writer;


class Scene
{
public:
    Scene();
    ~Scene();

    bool is_rendered() const;
    int get_width() const;
    int get_height() const;
    const Color *get_pixels() const;

    void read(const std::string &filename);
    void write(Writer &writer, const std::string &filename);
    void render();

    void add_shape(Shape *obj);
    void add_light(PointLight *light);

private:
    Color trace_ray(const Ray &ray, const int depth);

    // Pixel dimensions of the image.
    int width, height;

    // Ray tracing parameters.
    int max_depth;

    // Scene objects.
    AmbientLight *ambient;
    std::list<Shape *> shapes;
    std::list<PointLight *> lights;

    // Rendering stats
    unsigned int nrays;

    // Rendering output.
    bool _is_rendered;
    Color *pixels;
};

#endif
