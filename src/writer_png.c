/* writer_png.c
 *
 * Definition of the PNG writer.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#include <setjmp.h>
#include <stdlib.h>

#include <png.h>

#include "writer_png.h"


static void png_user_error(png_structp png, png_const_charp msg);
static void png_user_warning(png_structp png, png_const_charp msg);


/*
 * write_scene_png --
 *
 * Write the given scene to file in PNG format.
 */
int
write_scene_png(Scene *scene, FILE *file)
{
    if (!scene->is_rendered) {
        return -1;
    }

    if (!file) {
        return -2;
    }

    // Set up the PNG data structures. libpng requires two: a PNG object and an info object.
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, png_user_error, png_user_warning);
    if (!png) {
        return -3;
    }

    png_infop png_info = png_create_info_struct(png);
    if (!png_info) {
        return -4;
    }

    // Set up libpng error handling. If an error occurs, libpng will longjmp back here... (Wat.)
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &png_info);
        return -5;
    }

    // Set up output.
    png_init_io(png, file);

    // Write it!
    png_byte **rows = malloc(png_sizeof(png_bytep) * scene->height);
    for (int y = 0; y < scene->height; y++) {
        rows[y] = malloc(png_sizeof(png_byte) * scene->width * 4);
        if (rows[y] == NULL) {
            // TODO: DANGER! WILL ROBINSON!
        }
        for (int x = 0; x < scene->width; x += 4) {
            rows[y][x] = scene->pixels[y * scene->height + x].red;
            rows[y][x+1] = scene->pixels[y * scene->height + x].green;
            rows[y][x+2] = scene->pixels[y * scene->height + x].blue;
            rows[y][x+3] = scene->pixels[y * scene->height + x].alpha;
        }
    }

    png_write_image(png, rows);

    for (int y = 0; y < scene->height; y++) {
        free(rows[y]);
    }
    free(rows);

    // Clean up!
    png_write_end(png, png_info);
    png_destroy_write_struct(&png, &png_info);

    // TODO: Return number of bytes written.
    return 0;
}


/*
 * png_user_error --
 *
 * Called by libpng when it encounters an error.
 */
/* static */ void
png_user_error(png_structp png,
               png_const_charp msg)
{

}


/*
 * png_user_warning --
 *
 * Called by libpng when it encounters an warning.
 */
/* static */ void
png_user_warning(png_structp png,
                 png_const_charp msg)
{

}
