/* scene_parser.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * A SceneParser parses a YAML Scene object.
 */

#include <cassert>
#include <string>

#include "scene_parser.hh"


namespace yaml {

SceneParser::SceneParser(Scene& scene,
                         ParserStack& parsers)
    : Parser(scene, parsers),
      mSection(SceneParser::NoSection),
      mDimension(SceneParser::NoDimension)
{ }


SceneParser::~SceneParser()
{ }


void
SceneParser::HandleEvent(yaml_event_t& event)
{
    switch (mSection) {
        case NoSection:
            HandleTopLevelEvent(event);
            break;
        case CameraSection:
            break;
        case DimensionsSection:
            HandleDimensionsEvent(event);
            break;
        case ObjectsSection:
            break;
        default:
            /* TODO: WHAT. Fail gracefully. */
            assert(false);
            break;
    }
}


void
SceneParser::HandleTopLevelEvent(yaml_event_t& event)
{
    static const std::string CAMERA = "camera";
    static const std::string DIMENSIONS = "dimensions";
    static const std::string OBJECTS = "objects";

    if (event.type == YAML_MAPPING_END_EVENT) {
        SetDone(true);
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
SceneParser::HandleDimensionsEvent(yaml_event_t& event)
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
                    GetScene().set_width(dim);
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
                GetScene().set_height(dim);
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

} /* namespace yaml */
