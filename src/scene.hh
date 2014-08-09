/* scene.h
 * vim: tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __SCENE_H__
#define __SCENE_H__

#include <list>
#include <string>

#include "camera.hh"
#include "light.h"
#include "object.hh"
#include "stats.hh"
#include "basics/basics.hh"


class Writer;


namespace charles {

/**
 * Scenes are the top level object in charles. Scenes contain objects, lights, a
 * camera, etc. and can be rendered to pixel data and written to a file.
 */
struct Scene
{
    Scene();
    ~Scene();

    UInt GetWidth() const;
    void SetWidth(UInt w);
    UInt GetHeight() const;
    void SetHeight(UInt h);

    Camera::Ptr GetCamera() const;
    void SetCamera(Camera::Ptr camera);

    void Write(Writer& writer, const std::string& filename);

    void Render();
    bool IsRendered() const;
    const Color* GetPixels() const;

    AmbientLight& GetAmbient();
    void AddObject(Object::Ptr obj);
    void AddLight(PointLight* light);

private:
    Color TraceRay(const basics::Ray &ray,
                   const int depth = 0,
                   const Double weight = 1.0);

    void LogCamera() const;
    void LogObjects() const;

    /** Pixel width */
    UInt mWidth;
    /** Pixel height */
    UInt mHeight;

    Camera::Ptr mCamera;

    /** Maximum depth of the ray tree */
    int mMaxDepth;
    /** Minimum specular weight to apply before giving up */
    float mMinWeight;

    // Scene objects.
    AmbientLight mAmbient;
    std::list<charles::Object::Ptr> mObjects;
    std::list<PointLight *> mLights;

    // Rendering stats
    charles::Stats mStats;

    // Rendering output.
    bool mIsRendered;
    Color *mPixels;
};

} /* namespace charles */

#endif
