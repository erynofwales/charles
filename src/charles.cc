/* charles.c
 *
 * Entry point for Charles, including main().
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cstdio>

#include "basics.h"

const char *OUT_FILE = "charles_out.png";


int
main(int argc,
     const char *argv[])
{
#if 0
    FILE *out_file = fopen(OUT_FILE, "wb");
    if (!out_file) {
        return -1;
    }

    Scene *scene = scene_init();

    Object *obj = object_init(ObjectTypeSphere);
    Texture *tex = texture_init();
    Color color = {255, 0, 0, 255};
    texture_set_color(tex, color);
    object_set_texture(obj, tex);
    Vector3 loc = {233, 290, 0};
    object_set_location(obj, loc);
    object_sphere_set_radius(obj, 100);
    scene_add_object(scene, obj);

    obj = object_init(ObjectTypeSphere);
    tex = texture_init();
    Color color2 = {0, 255, 0, 255};
    texture_set_color(tex, color2);
    object_set_texture(obj, tex);
    loc = vector_init(407, 290, 0);
    object_set_location(obj, loc);
    object_sphere_set_radius(obj, 100);
    scene_add_object(scene, obj);

    obj = object_init(ObjectTypeSphere);
    tex = texture_init();
    Color color3 = {0, 0, 255, 255};
    texture_set_color(tex, color3);
    object_set_texture(obj, tex);
    loc = vector_init(320, 140, 0);
    object_set_location(obj, loc);
    object_sphere_set_radius(obj, 100);
    scene_add_object(scene, obj);

    scene_render(scene);
    write_scene_png(scene, out_file);

    scene_destroy(scene);
    fclose(out_file);
#endif

    return 0;
}
