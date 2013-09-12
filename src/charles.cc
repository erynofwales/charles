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
#include "scene.h"
#include "writer_png.h"

const char *OUT_FILE = "charles_out.png";


int
main(int argc,
     const char *argv[])
{
    Scene scene = Scene();

    Material *m1 = new Material();
    m1->set_color(Color(1, 0, 0, 1));
    Material *m2 = new Material();
    m2->set_color(Color(0, 1, 0, 1));
    Material *m3 = new Material();
    m3->set_color(Color(0, 0, 1, 1));

    // Make some spheres.
    Sphere *s1 = new Sphere(Vector3(233, 290, 0), 100.0);
    Sphere *s2 = new Sphere(Vector3(407, 290, 0), 100.0);
    Sphere *s3 = new Sphere(Vector3(320, 140, 0), 100.0);
    s1->set_material(m1);
    s2->set_material(m2);
    s3->set_material(m3);
    scene.add_shape(s1);
    scene.add_shape(s2);
    scene.add_shape(s3);

    Light *l1 = new Light(Vector3(0.0, 240.0, -100.0), 1.0);
    scene.add_light(l1);

    // Render.
    scene.render();

    Writer *writer = new PNGWriter();
    scene.write(*writer, OUT_FILE);

    return 0;
}
