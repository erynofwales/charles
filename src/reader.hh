/* reader.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __READER_HH__
#define __READER_HH__

#include "scene.hh"


namespace charles {
    
/**
 * Interface for an input file reader.
 */
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

} /* namespace charles */

#endif /* __READER_HH__ */
