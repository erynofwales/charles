/* scene.c
 *
 * Definition of Scene-related functions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <chrono>
#include <cmath>
#include <cstdio>

#include "basics.h"
#include "light.h"
#include "log.hh"
#include "object.h"
#include "scene.h"
#include "writer.h"

#define LOG_NAME "scene"
#include "logModule.hh"

using namespace charles;


Scene::Scene()
    : width(640), height(480),
      mCamera(new PerspectiveCamera()),
      max_depth(5),
      min_weight(1e-4),
      ambient(new AmbientLight()),
      shapes(),
      lights(),
      mStats(),
      pixels(NULL)
{ }


Scene::~Scene()
{
    mCamera.reset();

    if (ambient != NULL) {
        delete ambient;
    }

    shapes.clear();

    for (PointLight *l : lights) {
        delete l;
    }
    lights.clear();

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


/*
 * Scene::GetCamera --
 */
Camera::Ptr
Scene::GetCamera()
    const
{
    return mCamera;
}


/*
 * Scene::SetCamera --
 */
void
Scene::SetCamera(Camera* camera)
{
    mCamera.reset(camera);
}


AmbientLight &
Scene::get_ambient()
    const
{
    return *ambient;
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
    LOG_INFO << "Rendering scene with " << shapes.size() << " objects.";
    printf("Rendering scene with %lu objects.\n", shapes.size());

    LogCamera();
    LogObjects();

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    pixels = new Color[width * height];

    Ray primary_ray;
    Vector3 o, d;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            primary_ray = mCamera->compute_primary_ray(x, width, y, height);
            mStats.primaryRays++;
            Color c = trace_ray(primary_ray);
            pixels[y * width + x] = c;
        }
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<float> seconds = end - start;

    _is_rendered = true;

    printf("Rendering completed in %f seconds.\n\n", seconds.count());
    LOG_INFO << "Rendering completed in " << seconds.count() << " seconds.";
    mStats.PrintRayTable();
    printf("\n");
    mStats.PrintIntersectionsTable();
}


/*
 * Scene::add_shape --
 *
 * Add a shape to the scene.
 */
void
Scene::add_shape(Object::Ptr shape)
{
    shapes.push_back(shape);
}


/*
 * Scene::add_light --
 *
 * Add a light to the scene.
 */
void
Scene::add_light(PointLight *light)
{
    lights.push_back(light);
}


/*
 * Scene::trace_ray --
 *
 * Trace the given ray through the scene, recursing until depth has been reached.
 */
Color
Scene::trace_ray(const Ray &ray,
                 const int depth,
                 const float weight)
{
    if (depth >= max_depth || weight <= min_weight) {
        return Color::Black;
    }

    Color out_color = Color::Black;
    Object::Ptr intersected_shape;
    TVector ts;
    Double nearest_t = INFINITY;

    ts.reserve(2);

    // Find intersections of this ray with objects in the scene.
    for (Object::Ptr s : shapes) {
        ts.clear();
        if (s->DoesIntersect(ray, ts, mStats)) {
            if (ts[0] < nearest_t) {
                intersected_shape = s;
                nearest_t = ts[0];
            }
        }
    }

    // If there was no intersection, return black.
    if (!intersected_shape) {
        return out_color;
    }

    Material& shape_material = intersected_shape->GetMaterial();
    const Color& shape_color = shape_material.GetDiffuseColor();

    Vector3 intersection = ray.parameterize(nearest_t);
    Vector3 normal = intersected_shape->compute_normal(intersection);

    /*
     * Diffuse lighting. (Shading, etc.)
     */

    Vector3 light_direction;
    Double ldotn, diffuse_level, ambient_level;
    Ray shadowRay;

    for (PointLight *l : lights) {
        light_direction = (l->GetOrigin() - intersection).normalize();
        ldotn = light_direction.dot(normal);

        /*
         * TODO: What is this even for? Removing it makes the darker showers
         * really bright.
         */
        if (ldotn < 0) {
            ldotn = 0.0;
        }

        diffuse_level = shape_material.GetDiffuseIntensity();
        ambient_level = 1.0 - diffuse_level;

        shadowRay = Ray(intersection, light_direction);
        for (Object::Ptr s : shapes) {
            if (s == intersected_shape) {
                /* Skip the intersected shape. */
                continue;
            }

            mStats.shadowRays++;

            /* Figure out if we're in shadow. */
            ts.clear();
            if (s->DoesIntersect(shadowRay, ts, mStats)) {
                diffuse_level = 0.0;
                break;
            }
        }

        /*
         * Compute basic Lambert diffuse shading for this object.
         */
        out_color += shape_color * (  ambient_level * ambient->compute_color_contribution()
                                    + diffuse_level * ldotn);
    }

    /*
     * Specular lighting. (Reflections, etc.)
     */

#if 0
    Double specular_level = shape_material.GetSpecularIntensity();
    const Color& specular_color = shape_material.GetSpecularColor();

    /*
     * Compute the reflection ray. Computing the direction of the reflection ray
     * is done by the following formula:
     *
     *     d = dr - 2n(dr . n)
     *
     * where d is the direction, dr is the direction of the incoming ray, and n
     * is the normal vector. Period (.) indicates the dot product.
     *
     * The origin of the reflection ray is the point on the surface where the
     * incoming ray intersected with it.
     */
    Ray reflection_ray = Ray(intersection,
                             ray.direction - 2.0 * normal * ray.direction.dot(normal));
    mStats.reflectionRays++;
    Color reflection_color = trace_ray(reflection_ray,
                                       depth + 1,
                                       weight * specular_level);

    // TODO: Mix in specular_color of material.
    out_color += specular_level * specular_color * reflection_color;
#endif

    return out_color;
}


void
Scene::LogCamera()
    const
{
    const Camera& c = *mCamera;

    LOG_DEBUG << "BEGIN CAMERA";
    LOG_DEBUG << "  type      = " << c.GetTypeString();
    LOG_DEBUG << "  origin    = " << c.GetOrigin();
    LOG_DEBUG << "  direction = " << c.get_direction();
    LOG_DEBUG << "  right     = " << c.GetRight();
    LOG_DEBUG << "  up        = " << c.GetUp();
    LOG_DEBUG << "  coordinate system is "
              << (c.IsLeftHanded() ? "left-handed" : "right-handed");
    LOG_DEBUG << "END CAMERA";
}


void
Scene::LogObjects()
    const
{
    LOG_DEBUG << "BEGIN SCENE OBJECTS";

    for (Object::Ptr obj : shapes) {
        LOG_DEBUG << "  " << *obj;
    }

    LOG_DEBUG << "END SCENE OBJECTS";
}
