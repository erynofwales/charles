/* writer.h
 *
 * Writers handle the interface between (mostly) C libraries to write various image formats and the rest of Charles.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __WRITER_H__
#define __WRITER_H__

#include <string>


class Scene;


class Writer
{
public:
    virtual
    ~Writer()
    { }

    virtual int write_scene(const Scene &scene, const std::string &filename) = 0;
};

#endif
