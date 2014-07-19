/* scene_parser.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * A SceneParser parses a YAML Scene object.
 */

#include <cassert>
#include <string>

#include "objectParser.hh"
#include "sceneParser.hh"
#include "vector_parser.hh"


namespace yaml {

SceneParser::SceneParser(Scene& scene,
                         ParserStack& parsers)
    : ScalarMappingParser(scene, parsers),
      mSection(SceneParser::NoSection)
{ }


SceneParser::~SceneParser()
{ }


void
SceneParser::HandleKeyEvent(const std::string& key)
{
    static const std::map<std::string, Section> sSections = {
        {"dimensions", DimensionsSection},
        {"objects", ObjectsSection}
    };

    if (sSections.count(key) > 0) {
        mSection = sSections.at(key);
    }
    else {
        mSection = NoSection;
    }
}


void
SceneParser::HandleValueEvent(yaml_event_t& event)
{
    switch (mSection) {
        case CameraSection:
            break;
        case DimensionsSection:
            HandleDimensionsEvent(event);
            break;
        case ObjectsSection:
            HandleObjectsEvent(event);
            break;
        default:
            /* TODO: WHAT. Fail gracefully. */
            assert(false);
            break;
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
        SetShouldExpectKey(true);
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


void
SceneParser::HandleObjectsEvent(yaml_event_t& event)
{
    if (event.type == YAML_SEQUENCE_START_EVENT) {
        /* Ignore sequence-start for now. */
        printf("start objects\n");
        return;
    }
    else if (event.type == YAML_SEQUENCE_END_EVENT) {
        printf("end objects\n");
        mSection = NoSection;
        SetShouldExpectKey(true);
        return;
    }

    if (event.type != YAML_MAPPING_START_EVENT) {
        assert(event.type != YAML_MAPPING_START_EVENT);
        return;
    }

    printf("start object\n");
    GetParsers().push(new ObjectParser(GetScene(), GetParsers()));
}

} /* namespace yaml */