/* charles.c
 *
 * Entry point for Charles, including main().
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cstdio>

#include "basics.h"
#include "light.h"
#include "object_sphere.h"
#include "scene.h"
#include "writer_png.h"

const char *OUT_FILE = "charles_out.png";


int
main(int argc,
     const char *argv[])
{
    Scene scene = Scene();

    // Make some spheres.
    Sphere *s1 = new Sphere(Vector3(233, 290, 0), 100.0);
    Sphere *s2 = new Sphere(Vector3(407, 290, 0), 100.0);
    Sphere *s3 = new Sphere(Vector3(320, 140, 0), 100.0);
    scene.add_shape(s1);
    scene.add_shape(s2);
    scene.add_shape(s3);

    Light *l1 = new Light(Vector3(0.0, 240.0, -100.0), 1.0);
    Light *l2 = new Light(Vector3(640.0, 240.0, -10000.0), 0.6);
    scene.add_light(l1);
    scene.add_light(l2);

    // Render.
    scene.render();

    Writer *writer = new PNGWriter();
    scene.write(*writer, OUT_FILE);

    return 0;
}
