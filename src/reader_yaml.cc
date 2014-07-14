/* reader_yaml.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * An input file reader for YAML files.
 */

#include <cstdio>
#include <stack>

#include "yaml.h"

#include "reader_yaml.hh"


struct Parser;
typedef std::stack<Parser *> ParserStack;


struct Parser
{
    Parser(Scene& scene,
           ParserStack& parsers)
        : mScene(scene),
          mParsers(parsers)
    { }

    virtual
    ~Parser()
    { }

    virtual void
    handle_start_event(yaml_event_t& event)
    { }

    virtual void
    handle_end_event(yaml_event_t& event)
    { }

    virtual void
    handle_event(yaml_event_t& event)
    { }

protected:
    Scene& mScene;
    ParserStack &mParsers;

private:
    Parser();
    Parser(Parser& other);
};


struct DocumentParser
    : public Parser
{
    DocumentParser(Scene& scene,
                   ParserStack& parsers)
        : Parser(scene, parsers)
    {
        printf("DocumentParser\n"); 
    }

    ~DocumentParser()
    {
        printf("~DocumentParser\n");
    }

    void
    handle_event(yaml_event_t& event)
    {
        
    }
};


struct StreamParser
    : public Parser
{
    StreamParser(Scene& scene,
                 ParserStack& parsers)
        : Parser(scene, parsers)
    {
        printf("StreamParser\n"); 
    }

    ~StreamParser()
    {
        printf("~StreamParser\n"); 
    }

    void
    handle_start_event(yaml_event_t& event)
    {
        printf("Stream start\n"); 
    }

    void
    handle_end_event(yaml_event_t& event)
    {
        switch (event.type) {
            case YAML_DOCUMENT_START_EVENT:
                mParsers.push(new DocumentParser(mScene, mParsers));
                mParsers.top()->handle_start_event(event);
                break;
            default:
                /* TODO: Error out, somehow. */
                break;
        }
    }

    void
    handle_event(yaml_event_t& event)
    { }

private:
    StreamParser();
    StreamParser(StreamParser& other);
};


struct SceneDocumentParser
{

};


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

    ParserStack parsers;
    bool success = true;
    bool done = false;
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
                parsers.push(new StreamParser(mScene, parsers));
                parsers.top()->handle_start_event(event);
                break;
            case YAML_STREAM_END_EVENT:
                printf("YAML_STREAM_END_EVENT\n");
                parsers.top()->handle_end_event(event);
                delete parsers.top();
                parsers.pop();
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

        done = (event.type == YAML_STREAM_END_EVENT);
        yaml_event_delete(&event);
    }

error:
    yaml_parser_delete(&parser);
    return success;
}
