/* writer_png.h
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __WRITERPNG_HH__
#define __WRITERPNG_HH__

#include "writer.h"


namespace charles {

/**
 * Write for producing PNG files.
 */
class PNGWriter
    : public Writer
{
public:
    int write_scene(const Scene &scene, const std::string &filename);
};

} /* namespace charles */

#endif
