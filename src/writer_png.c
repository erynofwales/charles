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

    /*
     * Tell libpng about basic parameters for the image:
     *   - 8 bit depth
     *   - RGB (no alpha)
     *   - No interlacing
     *   - No compression
     */
    png_set_IHDR(png, png_info,
                 scene->width, scene->height,
                 8, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    // Set up output.
    png_init_io(png, file);

    // Write header information.
    png_write_info(png, png_info);

    // Write it!
    int nbytes = 0;
    for (int y = 0; y < scene->height; y++) {
        png_byte *row = malloc(png_sizeof(png_byte) * scene->width * 3);
        if (row == NULL) {
            // TODO: DANGER! WILL ROBINSON!
        }
        for (int x = 0; x < scene->width; x++) {
            row[x*3+0] = scene->pixels[y * scene->width + x].red;
            row[x*3+1] = scene->pixels[y * scene->width + x].green;
            row[x*3+2] = scene->pixels[y * scene->width + x].blue;
            nbytes += 3;

        }
        png_write_row(png, row);
        free(row);
    }

    // Clean up!
    png_write_end(png, png_info);
    png_destroy_write_struct(&png, &png_info);

    // Return number of bytes written.
    return nbytes;
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
