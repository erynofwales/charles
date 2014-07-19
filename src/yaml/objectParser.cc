/* object_parser.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * Implementation of ObjectParser.
 */

#include <cassert>
#include <string>
#include <vector>

#include "yaml/object_parser.hh"

#include "object_sphere.h"
#include "yaml/vector_parser.hh"


namespace yaml {

ObjectParser::ObjectParser(Scene& scene,
                            ParserStack& parsers)
    : Parser(scene, parsers)
{ }


void
ObjectParser::HandleEvent(yaml_event_t& event)
{
    switch (mSection) {
        case NoSection:
            HandleTopLevelEvent(event);
            break;
        case OriginSection:
            break;
        case RadiusSection:
            break;
        default:
            assert(false);
            break;
    }
}


void
ObjectParser::HandleTopLevelEvent(yaml_event_t& event)
{
    static const std::string ORIGIN = "origin";
    static const std::string RADIUS = "radius";

    if (event.type == YAML_MAPPING_END_EVENT) {
        SetDone(true);
        return;
    }

    if (event.type != YAML_SCALAR_EVENT) {
        /* TODO: Clean this up. */
        assert(false);
    }

    std::string value = (char *)event.data.scalar.value;
    if (value == ORIGIN) {
        mSection = OriginSection;
    }
    else if (value == RADIUS) {
        mSection = RadiusSection;
    }
    else {
        /* TODO: Clean this up. */
        assert(false);
    }
}


void
ObjectParser::HandleOriginEvent(yaml_event_t& event)
{
    if (event.type != YAML_SEQUENCE_START_EVENT) {
        /* TODO: Clean this up. */
        assert(false);
    }

    auto onDone = [this](std::vector<double> origin) {
        if (origin.size() < 3) {
            assert(origin.size() < 3);
        }
        mObject->set_origin(Vector3(origin[0], origin[1], origin[2]));
        mSection = NoSection;
    };
    
    GetParsers().push(new VectorParser<double>(GetScene(), GetParsers(), onDone));
}


void
ObjectParser::HandleRadiusEvent(yaml_event_t& event)
{
    if (event.type != YAML_SCALAR_EVENT) {
        /* TODO: Clean this up. */
        assert(false);
    }

    double radius;
    std::string scalar((char *)event.data.scalar.value,
                       event.data.scalar.length);
    if (!ParseScalar<double>(scalar, radius)) {
        /* TODO: Clean this up. */
        assert(false);
    }
    mObject->set_radius(radius);
    mSection = NoSection;
}

} /* namespace yaml */
