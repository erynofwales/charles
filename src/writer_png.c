/* writer_png.c
 *
 * Definition of the PNG writer.
 *
 * Eryn Wells <eryn@erynwells.me>
 */


#include <setjmp.h>

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
    if (!file) {
        return -1;
    }

    // Set up the PNG data structures. libpng requires two: a PNG object and an info object.
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, png_user_error, png_user_warning);
    if (!png) {
        return -2;
    }

    png_infop png_info = png_create_info_struct(png);
    if (!png_info) {
        return -3;
    }

    // Set up libpng error handling. If an error occurs, libpng will longjmp back here... (Wat.)
    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &png_info);
        return -4;
    }

    // Set up output.
    png_init_io(png, file);

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
