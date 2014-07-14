/* reader.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * Interface for an input file reader.
 */


#ifndef __READER_HH__
#define __READER_HH__

#include "scene.h"


struct Reader
{
    Reader(Scene& scene)
        : mScene(scene)
    { }

    virtual
    ~Reader()
    { }

    virtual ssize_t read_file(const std::string& filename) = 0;

protected:
    Scene& mScene;
};

#endif /* __READER_HH__ */
