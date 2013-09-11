/* writer_png.h
 *
 * Declaration of the PNG writer.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __WRITER_PNG_H__
#define __WRITER_PNG_H__

#include "writer.h"


class PNGWriter
    : public Writer
{
public:
    int write_scene(const Scene &scene, const std::string &filename);
};

#endif
