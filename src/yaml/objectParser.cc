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

#include "material.h"
#include "object_sphere.h"
#include "yaml/objectParser.hh"
#include "yaml/vectorParser.hh"


namespace yaml {

ObjectParser::ObjectParser(Scene& scene,
                            ParserStack& parsers)
    : ScalarMappingParser(scene, parsers),
      mObject(new Sphere()),
      mSection(NoSection)
{
    GetScene().add_shape(mObject);
}


ObjectParser::~ObjectParser()
{ }


void
ObjectParser::HandleKeyEvent(const std::string& key)
{
    static const std::map<std::string, Section> sSections = {
        {"color", ColorSection},
        {"origin", OriginSection},
        {"radius", RadiusSection}
    };

    if (sSections.count(key) > 0) {
        mSection = sSections.at(key);
    }
    else {
        mSection = NoSection;
    }
}


void
ObjectParser::HandleValueEvent(yaml_event_t& event)
{
    switch (mSection) {
        case ColorSection:
            HandleColorEvent(event);
            break;
        case OriginSection:
            HandleOriginEvent(event);
            break;
        case RadiusSection:
            HandleRadiusEvent(event);
            break;
        default:
            assert(false);
            break;
    }
}


void
ObjectParser::HandleColorEvent(yaml_event_t& event)
{
    if (event.type != YAML_SEQUENCE_START_EVENT) {
        /* TODO: Clean this up. */
        assert(event.type != YAML_SEQUENCE_START_EVENT);
        return;
    }

    auto onDone = [this](Color color) {
        if (!mObject->get_material()) {
            mObject->set_material(new Material());
        }
        mObject->get_material()->set_diffuse_color(color);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new ColorParser(GetScene(), GetParsers(), onDone));
}


void
ObjectParser::HandleOriginEvent(yaml_event_t& event)
{
    if (event.type != YAML_SEQUENCE_START_EVENT) {
        /* TODO: Clean this up. */
        assert(event.type != YAML_SEQUENCE_START_EVENT);
        return;
    }

    auto onDone = [this](Vector3 origin) {
        mObject->set_origin(origin);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new Vector3Parser(GetScene(), GetParsers(), onDone));
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
    SetShouldExpectKey(true);
}

} /* namespace yaml */
