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
#include "yaml/vector_parser.hh"


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

    printf("%s: got key = %s", __PRETTY_FUNCTION__, key.c_str());

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
        assert(event.type != YAML_SEQUENCE_START_EVENT);
        return;
    }

    auto onDone = [this](std::vector<double> color) {
        if (color.size() < 3) {
            assert(color.size() < 3);
        }
        if (!mObject->get_material()) {
            mObject->set_material(new Material());
        }
        mObject->get_material()->set_diffuse_color(Color(color[0], color[1], color[2]));

        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new VectorParser<double>(GetScene(), GetParsers(), onDone));
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
        SetShouldExpectKey(true);
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
