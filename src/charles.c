/* charles.c
 *
 * Entry point for Charles, including main().
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <stdio.h>

#include <png.h>

#include "basics.h"
#include "object.h"
#include "scene.h"
#include "texture.h"
#include "writer_png.h"

char *OUT_FILE = "charles_out.png";


int
main(int argc,
     const char *argv[])
{
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
    object_sphere_set_radius(obj, 1);
    scene_add_object(scene, obj);

    scene_render(scene);
    write_scene_png(scene, out_file);

    scene_destroy(scene);
    fclose(out_file);

    return 0;
}
