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
#include "vector_parser.hh"


namespace yaml {

SceneParser::SceneParser(Scene& scene,
                         ParserStack& parsers)
    : Parser(scene, parsers),
      mSection(SceneParser::NoSection)
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
    auto onDone = [this](std::vector<int> dimensions) {
        if (dimensions.size() < 2) {
            assert(dimensions.size() < 2);
        }
        Scene& sc = GetScene();
        sc.set_width(dimensions.at(0));
        sc.set_height(dimensions.at(1));

        mSection = NoSection;
    };

    switch (event.type) {
        case YAML_SEQUENCE_START_EVENT:
            GetParsers().push(new VectorParser<int>(GetScene(), GetParsers(), onDone));
            break;
        default:
            /* TODO: Fail gracefully. */
            assert(false);
    }
}

} /* namespace yaml */
