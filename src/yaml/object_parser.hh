/* object_parser.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * An ObjectParser parses objects of various sorts.
 */

#ifndef __YAML_OBJECTPARSER_HH__
#define __YAML_OBJECTPARSER_HH__

#include "yaml/parsers.hh"


class Sphere;


namespace yaml {

struct ObjectParser
    : public Parser
{
    ObjectParser(Scene& scene, ParserStack& parsers);

    void HandleEvent(yaml_event_t& event);
    void HandleTopLevelEvent(yaml_event_t& event);
    void HandleOriginEvent(yaml_event_t& event);
    void HandleRadiusEvent(yaml_event_t& event);

private:
    Sphere* mObject;

    enum {
        NoSection,
        OriginSection,
        RadiusSection
    } mSection;
};

} /* namespace yaml */

#endif /* __YAML_OBJECTPARSER_HH__ */
