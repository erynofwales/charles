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


namespace yaml {

struct ObjectParser
    : public ScalarMappingParser
{
    ObjectParser(Scene& scene, ParserStack& parsers, const std::string& tag);
    ~ObjectParser();

protected:
    void HandleKeyEvent(const std::string& key);
    void HandleValueEvent(yaml_event_t& event);

private:
    enum class Type {
        Box,
        Plane,
        Sphere,
    };

    enum Section {
        NoSection,
        ColorSection,

        /* Sphere sections */
        OriginSection,
        RadiusSection,

        /* Box sections */
        NearSection,
        FarSection,

        /* Plane sections */
        NormalSection,
        DistanceSection,
    };

    void HandleColorEvent(yaml_event_t& event);

    void HandleOriginEvent(yaml_event_t& event);
    void HandleRadiusEvent(yaml_event_t& event);

    void HandleNearEvent(yaml_event_t& event);
    void HandleFarEvent(yaml_event_t& event);

    void HandleNormalEvent(yaml_event_t& event);
    void HandleDistanceEvent(yaml_event_t& event);

    charles::Object::Ptr mObject;
    Type mType;
    Section mSection;
};

} /* namespace yaml */

#endif /* __YAML_OBJECTPARSER_HH__ */
