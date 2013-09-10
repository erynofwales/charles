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

class Shape;


class Scene
{
public:
    Scene();
    ~Scene();

    bool is_rendered() const;

    void read(FILE *f);
    void write(FILE *f);
    void render();

    void add_shape(Shape *obj);

private:
    Color trace_ray(const Ray &ray, const int depth);

    int height, width;
    std::list<Shape *> shapes;

    bool _is_rendered;
    Color *pixels;
};

#endif
