/* reader_yaml.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __READERYAML_HH__
#define __READERYAML_HH__

#include "reader.hh"
#include "scene.hh"

namespace charles {

/**
 * An input file reader for YAML files.
 */
struct YAMLReader
    : public Reader
{
    YAMLReader(Scene& scene)
        : Reader(scene)
    { }

    ssize_t read_file(const std::string& filename);
};

} /* namespace charles */

#endif /* __READER_YAML_HH__ */
