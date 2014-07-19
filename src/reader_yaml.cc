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

#include "reader_yaml.hh"

#include "yaml/parsers.hh"
#include "yaml/sceneParser.hh"


#if 0
struct ObjectParser
    : public Parser
{
    ObjectParser(Scene& scene, ParserStack& parsers)
        : Parser(scene, parsers),
          mSection(NoSection)
    {
        printf("ObjectParser\n");
    }

    ~ObjectParser()
    {
        printf("~ObjectParser\n");
    }

    void
    handle_event(yaml_event_t& event)
    {
        switch (mSection) {
            case NoSection:
                break;
            case TypeSection:
                break;
            case OriginSection:
                break;
        }
    }

private:
    enum {
        NoSection,
        TypeSection,
        OriginSection,
    } mSection;
};
#endif


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

    printf("Reading file: %s\n", filename.c_str());
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
                printf("YAML_NO_EVENT\n");
                break;

            case YAML_STREAM_START_EVENT:
                printf("YAML_STREAM_START_EVENT\n");
                break;
            case YAML_STREAM_END_EVENT:
                printf("YAML_STREAM_END_EVENT\n");
                break;

            case YAML_DOCUMENT_START_EVENT:
                printf("YAML_DOCUMENT_START_EVENT\n");
                break;
            case YAML_DOCUMENT_END_EVENT:
                printf("YAML_DOCUMENT_END_EVENT\n");
                break;

            case YAML_ALIAS_EVENT:
                printf("YAML_ALIAS_EVENT\n");
                break;
            case YAML_SCALAR_EVENT:
                printf("YAML_SCALAR_EVENT\n");
                break;

            case YAML_SEQUENCE_START_EVENT:
                printf("YAML_SEQUENCE_START_EVENT\n");
                break;
            case YAML_SEQUENCE_END_EVENT:
                printf("YAML_SEQUENCE_END_EVENT\n");
                break;

            case YAML_MAPPING_START_EVENT:
                printf("YAML_MAPPING_START_EVENT\n");
                break;
            case YAML_MAPPING_END_EVENT:
                printf("YAML_MAPPING_END_EVENT\n");
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
                    printf("parser done\n");
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
