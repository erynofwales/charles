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
#include "yaml/scalarMappingParser.hh"


class Sphere;


namespace yaml {

struct ObjectParser
    : public ScalarMappingParser
{
    ObjectParser(Scene& scene, ParserStack& parsers);
    ~ObjectParser();

protected:
    void HandleKeyEvent(const std::string& key);
    void HandleValueEvent(yaml_event_t& event);

private:
    enum Section {
        NoSection,
        ColorSection,
        OriginSection,
        RadiusSection
    };

    void HandleColorEvent(yaml_event_t& event);
    void HandleOriginEvent(yaml_event_t& event);
    void HandleRadiusEvent(yaml_event_t& event);

    Sphere* mObject;
    Section mSection;
};

} /* namespace yaml */

#endif /* __YAML_OBJECTPARSER_HH__ */
