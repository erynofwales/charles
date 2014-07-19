/* scene_parser.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * A SceneParser parses a YAML Scene object.
 */

#ifndef __YAML_SCENE_PARSER_HH__
#define __YAML_SCENE_PARSER_HH__

#include <string>

#include "parsers.hh"
#include "scalarMappingParser.hh"


namespace yaml {

struct SceneParser
    : public ScalarMappingParser
{
    SceneParser(Scene& scene, ParserStack& parsers);
    ~SceneParser();

protected:
    void HandleKeyEvent(const std::string& key);
    void HandleValueEvent(yaml_event_t& event);

private:
    enum Section {
        NoSection,
        CameraSection,
        DimensionsSection,
        ObjectsSection,
    };

    void HandleDimensionsEvent(yaml_event_t& event);
    void HandleObjectsEvent(yaml_event_t& event);

    Section mSection;
};

} /* namespace yaml */

#endif /* __YAML_SCENE_PARSER_HH__ */
