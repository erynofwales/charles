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
#include "camera.h"
#include "object.h"


class AmbientLight;
class PointLight;
class Writer;


class Scene
{
public:
    Scene();
    ~Scene();

    bool is_rendered() const;

    int get_width() const;
    void set_width(int w) { width = w; }
    int get_height() const;
    void set_height(int h) { height = h; }

    Camera::Ptr GetCamera() const;
    void SetCamera(Camera* camera);

    AmbientLight &get_ambient() const;
    const Color *get_pixels() const;

    void read(const std::string &filename);
    void write(Writer &writer, const std::string &filename);
    void render();

    void add_shape(charles::Object::Ptr obj);
    void add_light(PointLight *light);

private:
    Color trace_ray(const Ray &ray, const int depth = 0, const float weight = 1.0);

    // Pixel dimensions of the image.
    int width, height;

    Camera::Ptr mCamera;

    /*
     * Ray tracing parameters. max_depth indicates the maximum depth of the ray tree. min_weight indicates the minimum
     * specular weight to apply before giving up.
     */
    int max_depth;
    float min_weight;

    // Scene objects.
    AmbientLight *ambient;
    std::list<charles::Object::Ptr> shapes;
    std::list<PointLight *> lights;

    // Rendering stats
    struct Stats
    {
        unsigned long TotalRays() const;

        void PrintRayTable() const;

        unsigned long primaryRays;
        unsigned long shadowRays;
        unsigned long reflectionRays;
        unsigned long transmissionRays;

    private:
        void PrintRayRow(const std::string& title,
                         const unsigned long& value) const;
    } mStats;

    // Rendering output.
    bool _is_rendered;
    Color *pixels;
};

#endif
