/* charles.c
 *
 * Entry point for Charles, including main().
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <stdio.h>

#include <png.h>

#include "scene.h"
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

    scene_render(scene);
    write_scene_png(scene, out_file);

    scene_destroy(scene);
    fclose(out_file);

    return 0;
}
