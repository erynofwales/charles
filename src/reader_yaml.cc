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
    handle_event(yaml_event_t& event)
    {
        /* TODO: Shouldn't ever get here. */
        abort(); 
    }

    bool
    done()
        const
    {
        return mDone;
    }

protected:
    Scene& mScene;
    ParserStack &mParsers;
    bool mDone;
};


struct SceneParser
    : public Parser
{
    SceneParser(Scene& scene, ParserStack& parsers)
        : Parser(scene, parsers),
          mSection(SceneParser::NoSection),
          mDimension(SceneParser::NoDimension)
    {
        printf("SceneParser\n");
    }

    ~SceneParser()
    {
        printf("~SceneParser\n");
    }
    
    void
    handle_event(yaml_event_t& event)
    {
        switch (mSection) {
            case NoSection:
                handle_toplevel_event(event);
                break;
            case CameraSection:
                handle_camera_event(event);
                break;
            case DimensionsSection:
                handle_dimensions_event(event);
                break;
            case ObjectsSection:
                handle_objects_event(event);
                break;
            default:
                /* TODO: WHAT. Fail gracefully. */
                abort();
                break;
        }
    }

    void
    handle_toplevel_event(yaml_event_t& event)
    {
        static const std::string CAMERA = "camera";
        static const std::string DIMENSIONS = "dimensions";
        static const std::string OBJECTS = "objects";

        if (event.type == YAML_MAPPING_END_EVENT) {
            mDone = true;
            return;
        }

        if (event.type != YAML_SCALAR_EVENT) {
            /* TODO: Invalid event type for top-level Scene. Fail. */
            abort();
        }

        std::string key = (char *)event.data.scalar.value;
        if (key == CAMERA) {
            mSection = SceneParser::CameraSection;
        }
        else if (key == DIMENSIONS) {
            mSection = SceneParser::DimensionsSection;
        }
        else if (key == OBJECTS) {
            mSection = SceneParser::ObjectsSection;
        }
        else {
            /* TODO: Invalid key. Fail. */
            abort();
        }
    }

    void
    handle_camera_event(yaml_event_t& event)
    { }

    void
    handle_dimensions_event(yaml_event_t& event)
    {
        int dim;

        switch (mDimension) {
            case NoDimension:
                switch (event.type) {
                    case YAML_SEQUENCE_START_EVENT:
                        printf("  start dimensions\n");
                        mDimension = SceneParser::WidthDimension;
                        break;
                    default:
                        /* TODO: Fail gracefully. */
                        abort();
                }
                break;
            case WidthDimension:
                switch (event.type) {
                    case YAML_SCALAR_EVENT:
                        printf("  width = %s\n", event.data.scalar.value);
                        sscanf((char *)event.data.scalar.value, "%d", &dim);
                        mScene.set_width(dim);
                        mDimension = SceneParser::HeightDimension;
                        break;
                    default:
                        /* TODO: Fail gracefully. */
                        abort();
                }
                break;
            case HeightDimension:
                if (event.type == YAML_SCALAR_EVENT) {
                    printf("  height = %s\n", event.data.scalar.value);
                    sscanf((char *)event.data.scalar.value, "%d", &dim);
                    mScene.set_height(dim);
                    mDimension = SceneParser::DoneDimension;
                }
                else {
                    /* TODO: Fail gracefully. */
                    abort();
                }
                break;
            case DoneDimension:
                if (event.type == YAML_SEQUENCE_END_EVENT) {
                    printf("  end dimensions\n");
                    mSection = NoSection;
                }
                else {
                    /* TODO: Fail gracefully. */
                    abort();
                }
                break;
        }
    }

    void
    handle_objects_event(yaml_event_t& event)
    { }

private:
    enum {
        NoSection,
        CameraSection,
        DimensionsSection,
        ObjectsSection,
    } mSection;

    enum {
        NoDimension,
        HeightDimension,
        WidthDimension,
        DoneDimension
    } mDimension;
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
        switch (event.type) {
            case YAML_DOCUMENT_END_EVENT:
                mDone = true;
                break;
            case YAML_MAPPING_START_EVENT:
                mParsers.push(new SceneParser(mScene, mParsers));
                break;
            default:
                /* TODO: Fail gracefully. */
                abort();
                break;
        }
    }
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

            /* Don't care about these... */
            case YAML_STREAM_START_EVENT:
                printf("YAML_STREAM_START_EVENT\n");
                break;
            case YAML_STREAM_END_EVENT:
                printf("YAML_STREAM_END_EVENT\n");
                break;

            case YAML_DOCUMENT_START_EVENT:
                printf("YAML_DOCUMENT_START_EVENT\n");
                parsers.push(new DocumentParser(mScene, parsers));
                break;

            default:
                if (parsers.top()->done()) {
                    delete parsers.top();
                    parsers.pop();
                }
                if (!parsers.empty()) {
                    parsers.top()->handle_event(event);
                }

#if 0
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
#endif
        }

        done = (event.type == YAML_STREAM_END_EVENT);
        yaml_event_delete(&event);
    }

error:
    yaml_parser_delete(&parser);
    return success;
}
