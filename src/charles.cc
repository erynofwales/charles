/* charles.c
 *
 * Entry point for Charles, including main().
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cstdio>

#include "basics.h"
#include "light.h"
#include "material.h"
#include "object_sphere.h"
#include "object_plane.h"
#include "scene.h"
#include "writer_png.h"

const char *OUT_FILE = "charles_out.png";


int
main(int argc,
     const char *argv[])
{
    Scene scene = Scene();

    scene.get_ambient().set_intensity(1.0);

    Material *m1 = new Material();
    m1->set_diffuse_color(Color::Red);
    Material *m2 = new Material();
    m2->set_diffuse_color(Color::Green);
    Material *m3 = new Material();
    m3->set_diffuse_color(Color::Blue);
    Material *m4 = new Material();
    m4->set_diffuse_color(Color(1.0, 0.0, 1.0));

    // Make some spheres.
    Sphere *s1 = new Sphere(Vector3(233, 290, 0), 80.0);
    Sphere *s2 = new Sphere(Vector3(407, 290, 0), 80.0);
    Sphere *s3 = new Sphere(Vector3(320, 140, 0), 80.0);
    Sphere *s4 = new Sphere(Vector3(620, 360, 0), 20.0);
    s1->set_material(m1);
    s2->set_material(m2);
    s3->set_material(m3);
    s4->set_material(m4);
    scene.add_shape(s1);
    scene.add_shape(s2);
    scene.add_shape(s3);
    scene.add_shape(s4);

    // Make a plane
    Plane *p1 = new Plane(Vector3(0, 460, 400), Vector3(0, 1, 0.01));
    p1->set_material(m1);
    scene.add_shape(p1);

    PointLight *l1 = new PointLight(Vector3(0.0, 240.0, 100.0), Color::White, 1.0);
    scene.add_light(l1);

    // Render.
    scene.render();

    Writer *writer = new PNGWriter();
    scene.write(*writer, OUT_FILE);

    return 0;
}
