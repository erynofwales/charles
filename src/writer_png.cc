/* writer_png.c
 *
 * Definition of the PNG writer.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <csetjmp>
#include <cstdlib>
#include <string>

#include "scene.hh"
#include "writer_png.h"
#include "basics/basics.hh"

extern "C" {
#include <png.h>
}


using charles::basics::Color;


static void png_user_error(png_structp png, png_const_charp msg);
static void png_user_warning(png_structp png, png_const_charp msg);


namespace charles {

/*
 * PNGWriter::write_scene --
 *
 * Write the given scene to a file in PNG format.
 */
int
PNGWriter::write_scene(const Scene &scene, const std::string &filename)
{
    if (!scene.IsRendered()) {
        return -1;
    }

    FILE *file = fopen(filename.c_str(), "wb");
    if (!file) {
        return -1;
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
                 scene.GetWidth(), scene.GetHeight(),
                 8, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    // Set up output.
    png_init_io(png, file);

    // Write header information.
    png_write_info(png, png_info);

    // Write it!
    const Color* pixels = scene.GetPixels();
    png_byte *row = NULL;
    int nbytes = 0;
    for (UInt y = 0; y < scene.GetHeight(); y++) {
        row = new png_byte[scene.GetWidth() * 3];
        if (row == NULL) {
            // TODO: DANGER! WILL ROBINSON!
        }
        for (UInt x = 0; x < scene.GetWidth(); x++) {
            Color c = pixels[y * scene.GetWidth() + x];
            row[x*3+0] = 0xff * c.red;
            row[x*3+1] = 0xff * c.green;
            row[x*3+2] = 0xff * c.blue;
            nbytes += 3;
        }
        png_write_row(png, row);
        delete[] row;
    }

    // Clean up!
    png_write_end(png, png_info);
    png_destroy_write_struct(&png, &png_info);

    // Return number of bytes written.
    return nbytes;
}

} /* namespace charles */


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

/*
 * png_user_error --
 *
 * Called by libpng when it encounters an error.
 */

/* static */ void
png_user_error(png_structp png,
               png_const_charp msg)
{ }


/*
 * png_user_warning --
 *
 * Called by libpng when it encounters an warning.
 */

/* static */ void
png_user_warning(png_structp png,
                 png_const_charp msg)
{ }

#pragma clang diagnostic pop