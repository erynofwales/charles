/* reader_yaml.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * An input file reader for YAML files.
 */

#include <cstdio>
#include <cstdlib>
#include <stack>
#include <string>

#include "yaml.h"

#include "charles.hh"
#include "log.hh"
#include "reader_yaml.hh"

#include "yaml/parsers.hh"
#include "yaml/sceneParser.hh"

#define LOG_NAME "yaml"
#include "logModule.hh"


namespace charles {

ssize_t
YAMLReader::read_file(const std::string& filename)
{

    FILE *yaml_infile = fopen(filename.c_str(), "rb");
    if (!yaml_infile) {
        fprintf(stderr, "Couldn't open file: %s\n", filename.c_str());
        return -1;
    }

    yaml_parser_t parser;
    yaml_parser_initialize(&parser);

    printf("Reading %s\n", filename.c_str());
    yaml_parser_set_input_file(&parser, yaml_infile);

    yaml::ParserStack parsers;
    bool success = true;
    bool done = false;
    bool sawDocument = false;
    yaml_event_t event;
    while (!done) {
        if (!yaml_parser_parse(&parser, &event)) {
            success = false;
            goto error;
        }

        switch (event.type) {
            case YAML_NO_EVENT:
                LOG_TRACE << "YAML_NO_EVENT";
                break;

            case YAML_STREAM_START_EVENT:
                LOG_TRACE << "YAML_STREAM_START_EVENT";
                break;
            case YAML_STREAM_END_EVENT:
                LOG_TRACE << "YAML_STREAM_END_EVENT";
                break;

            case YAML_DOCUMENT_START_EVENT:
                LOG_TRACE << "YAML_DOCUMENT_START_EVENT";
                break;
            case YAML_DOCUMENT_END_EVENT:
                LOG_TRACE << "YAML_DOCUMENT_END_EVENT";
                break;

            case YAML_ALIAS_EVENT:
                LOG_TRACE << "YAML_ALIAS_EVENT";
                break;
            case YAML_SCALAR_EVENT:
                LOG_TRACE << "YAML_SCALAR_EVENT";
                break;

            case YAML_SEQUENCE_START_EVENT:
                LOG_TRACE << "YAML_SEQUENCE_START_EVENT";
                break;
            case YAML_SEQUENCE_END_EVENT:
                LOG_TRACE << "YAML_SEQUENCE_END_EVENT";
                break;

            case YAML_MAPPING_START_EVENT:
                LOG_TRACE << "YAML_MAPPING_START_EVENT";
                break;
            case YAML_MAPPING_END_EVENT:
                LOG_TRACE << "YAML_MAPPING_END_EVENT";
                break;
        }

        if (event.type == YAML_DOCUMENT_START_EVENT) {
            sawDocument = true;
            parsers.push(new yaml::SceneParser(mScene, parsers));
        }
        else {
            sawDocument = false;
            if (!parsers.empty()) {
                parsers.top()->HandleEvent(event);
                if (parsers.top()->GetDone()) {
                    delete parsers.top();
                    parsers.pop();
                }
            }
        }

        done = (event.type == YAML_STREAM_END_EVENT);
        yaml_event_delete(&event);
    }

error:
    yaml_parser_delete(&parser);
    return success;
}

} /* namespace charles */
