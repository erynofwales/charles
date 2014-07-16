/* scene_parser.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * A SceneParser parses a YAML Scene object.
 */

#ifndef __YAML_SCENE_PARSER_HH__
#define __YAML_SCENE_PARSER_HH__

#include "parsers.hh"


namespace yaml {

struct SceneParser
    : public Parser
{
    SceneParser(Scene& scene, ParserStack& parsers);
    ~SceneParser();

    void HandleEvent(yaml_event_t& event);
    void HandleTopLevelEvent(yaml_event_t& event);
    void HandleDimensionsEvent(yaml_event_t& event);

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

} /* namespace yaml */

#endif /* __YAML_SCENE_PARSER_HH__ */
