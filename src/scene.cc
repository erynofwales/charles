/* scene.c
 *
 * Definition of Scene-related functions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cassert>
#include <cmath>
#include <cstdio>
#include <chrono>

#include "scene.hh"

#include "basics.h"
#include "light.h"
#include "log.hh"
#include "object.hh"
#include "writer.h"
#include "basics/basics.hh"

#define LOG_NAME "scene"
#include "logModule.hh"


using charles::basics::Ray;
using charles::basics::Vector4;


namespace charles {

/*
 * charles::Scene::Scene --
 */
Scene::Scene()
    : mWidth(640),
      mHeight(480),
      mCamera(new PerspectiveCamera()),
      mMaxDepth(5),
      mMinWeight(1e-6),
      mAmbient(),
      mObjects(),
      mLights(),
      mStats(),
      mPixels(NULL)
{ }


/*
 * charles::Scene::~Scene --
 */
Scene::~Scene()
{
    mCamera.reset();

    mObjects.clear();

    for (PointLight *l : mLights) {
        delete l;
    }
    mLights.clear();

    if (mPixels != NULL) {
        delete[] mPixels;
        mIsRendered = false;
    }
}


/*
 * charles::Scene::IsRendered --
 */
bool
Scene::IsRendered()
    const
{
    return mIsRendered;
}


/*
 * charles::Scene::GetWidth --
 */
UInt
Scene::GetWidth()
    const
{
    return mWidth;
}


/*
 * charles::Scene::SetWidth --
 */
void
Scene::SetWidth(UInt w)
{
    mWidth = w;
}


/*
 * charles::Scene::GetHeight --
 */
UInt
Scene::GetHeight()
    const
{
    return mHeight;
}


/*
 * charles::Scene::SetHeight --
 */
void
Scene::SetHeight(UInt h)
{
    mHeight = h;
}


/*
 * charles::Scene::GetCamera --
 */
Camera::Ptr
Scene::GetCamera()
    const
{
    return mCamera;
}


/*
 * charles::Scene::SetCamera --
 */
void
Scene::SetCamera(Camera::Ptr camera)
{
    mCamera = camera;
}


/*
 * charles::Scene::GetAmbient --
 */
AmbientLight&
Scene::GetAmbient()
{
    return mAmbient;
}


/*
 * charles::Scene::GetPixels --
 */
const Color*
Scene::GetPixels()
    const
{
    return mPixels;
}


/*
 * charles::Scene::Write --
 */
void
Scene::Write(Writer& writer,
             const std::string& filename)
{
    writer.write_scene(*this, filename);
}


/*
 * charles::Scene::Render --
 */
void
Scene::Render()
{
    LOG_INFO << "Rendering scene with " << mObjects.size() << " objects.";
    printf("Rendering scene with %lu objects.\n", mObjects.size());

    LogCamera();
    LogObjects();

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    mPixels = new Color[mWidth * mHeight];

    Ray primaryRay;
    Vector4 o, d;
    for (UInt y = 0; y < mHeight; y++) {
        for (UInt x = 0; x < mWidth; x++) {
            primaryRay = mCamera->PrimaryRay(x, mWidth, y, mHeight);
            mStats.primaryRays++;
            Color c = TraceRay(primaryRay);
            mPixels[y * mWidth + x] = c;
        }
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<Double> seconds = end - start;

    mIsRendered = true;

    printf("Rendering completed in %f seconds.\n\n", seconds.count());
    LOG_INFO << "Rendering completed in " << seconds.count() << " seconds.";
    mStats.PrintRayTable();
    printf("\n");
    mStats.PrintIntersectionsTable();
}


/*
 * charles::Scene::AddObject --
 */
void
Scene::AddObject(Object::Ptr obj)
{
    mObjects.push_back(obj);
}


/*
 * charles::Scene::AddLight --
 */
void
Scene::AddLight(PointLight* light)
{
    mLights.push_back(light);
}


/*
 * charles::Scene::TraceRay --
 */
Color
Scene::TraceRay(const Ray &ray,
                const int depth,
                const Double weight)
{
    if (depth >= mMaxDepth || weight <= mMinWeight) {
        return Color::Black;
    }

    Color outColor = Color::Black;
    Object::Ptr intersectedObj;
    TVector ts;
    Double nearestT = INFINITY;

    ts.reserve(2);

    // Find intersections of this ray with objects in the scene.
    for (Object::Ptr obj : mObjects) {
        ts.clear();
        if (obj->Intersect(ray, ts, mStats)) {
            if (ts[0] < nearestT) {
                intersectedObj = obj;
                nearestT = ts[0];
            }
        }
    }

    // If there was no intersection, return black.
    if (!intersectedObj) {
        return outColor;
    }

    Material& material = intersectedObj->GetMaterial();
    const Color& shapeColor = material.GetDiffuseColor();

    Vector4 intersection = ray.Parameterize(nearestT);
    Vector4 normal = intersectedObj->Normal(intersection);

    /*
     * Diffuse lighting. (Shading, etc.)
     */

    Vector4 lightDirection;
    Double ldotn, diffuseLevel, ambientLevel;
    Ray shadowRay;

    for (PointLight *l : mLights) {
        lightDirection = (l->GetOrigin() - intersection).normalize();
        ldotn = lightDirection.Dot(normal);

        /*
         * TODO: What is this even for? Removing it makes the darker showers
         * really bright.
         */
        if (ldotn < 0) {
            ldotn = 0.0;
        }

        diffuseLevel = material.GetDiffuseIntensity();
        ambientLevel = 1.0 - diffuseLevel;

        shadowRay = Ray(intersection, lightDirection);
        for (Object::Ptr obj : mObjects) {
            if (obj == intersectedObj) {
                /* Skip the intersected shape. */
                continue;
            }

            mStats.shadowRays++;

            /* Figure out if we're in shadow. */
            ts.clear();
            if (obj->Intersect(shadowRay, ts, mStats)) {
                diffuseLevel = 0.0;
                break;
            }
        }

        /*
         * Compute basic Lambert diffuse shading for this object.
         */
        outColor += shapeColor * (  ambientLevel * mAmbient.compute_color_contribution()
                                  + diffuseLevel * ldotn);
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

    return outColor;
}


/*
 * charles::Scene::LogCamera --
 */
void
Scene::LogCamera()
    const
{
    const Camera& c = *mCamera;

    LOG_DEBUG << "BEGIN CAMERA";
    LOG_DEBUG << "  type      = " << c.GetTypeString();
    LOG_DEBUG << "  origin    = " << c.GetOrigin();
    LOG_DEBUG << "  direction = " << c.GetDirection();
    LOG_DEBUG << "  right     = " << c.GetRight();
    LOG_DEBUG << "  up        = " << c.GetUp();
    LOG_DEBUG << "  coordinate system is "
              << (c.IsLeftHanded() ? "left-handed" : "right-handed");
    LOG_DEBUG << "END CAMERA";
}


/*
 * charles::Scene::LogObjects --
 */
void
Scene::LogObjects()
    const
{
    LOG_DEBUG << "BEGIN SCENE OBJECTS";

    for (Object::Ptr obj : mObjects) {
        LOG_DEBUG << "  " << *obj;
    }

    LOG_DEBUG << "END SCENE OBJECTS";
}

} /* namespace charles */
