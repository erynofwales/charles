/* reader_yaml.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * An input file reader for YAML files.
 */


#ifndef __READER_YAML_HH__
#define __READER_YAML_HH__

#include "reader.hh"
#include "scene.h"


struct YAMLReader
    : public Reader
{
    YAMLReader(Scene& scene)
        : Reader(scene)
    { }

    ~YAMLReader() { }

    ssize_t read_file(const std::string& filename);
};

#endif /* __READER_YAML_HH__ */
