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
#include "object.h"
#include "objectBox.hh"
#include "object_sphere.h"
#include "yaml/objectParser.hh"
#include "yaml/vectorParser.hh"


using namespace charles;


namespace yaml {

ObjectParser::ObjectParser(Scene& scene,
                           ParserStack& parsers,
                           const std::string& tag)
    : ScalarMappingParser(scene, parsers),
      mObject(nullptr),
      mSection(NoSection)
{
    if (tag == "!Object.Box") {
        mType = Type::Box;
        mObject.reset(new Box());
    } else if (tag == "!Object.Sphere") {
        mType = Type::Sphere;
        mObject.reset(new Sphere());
    } else {
        assert(false);
    }
    GetScene().add_shape(mObject);
}


ObjectParser::~ObjectParser()
{
    mObject.reset();
}


void
ObjectParser::HandleKeyEvent(const std::string& key)
{
    static const std::map<std::string, Section> sCommonSections = {
        {"color", ColorSection}
    };

    static const std::map<std::string, Section> sSphereSections = {
        {"origin", OriginSection},
        {"radius", RadiusSection}
    };

    static const std::map<std::string, Section> sBoxSections = {
        {"near", NearSection},
        {"far", FarSection}
    };

    if (sCommonSections.count(key) > 0) {
        mSection = sCommonSections.at(key);
        return;
    }

    if (mType == Type::Box) {
        if (sBoxSections.count(key) > 0) {
            mSection = sBoxSections.at(key);
        } else {
            mSection = NoSection;
        }
    } else if (mType == Type::Sphere) {
        if (sSphereSections.count(key) > 0) {
            mSection = sSphereSections.at(key);
        } else {
            mSection = NoSection;
        }
    } else {
        assert(false);
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
        case NearSection:
            HandleNearEvent(event);
            break;
        case FarSection:
            HandleFarEvent(event);
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
        mObject->GetMaterial().SetDiffuseColor(color);
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
        mObject->SetOrigin(origin);
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
    std::dynamic_pointer_cast<Sphere>(mObject)->set_radius(radius);
    mSection = NoSection;
    SetShouldExpectKey(true);
}


void
ObjectParser::HandleNearEvent(yaml_event_t& event)
{
    if (event.type != YAML_SEQUENCE_START_EVENT) {
        /* TODO: Clean this up. */
        assert(event.type != YAML_SEQUENCE_START_EVENT);
        return;
    }

    auto onDone = [this](Vector3 near) {
        std::dynamic_pointer_cast<Box>(mObject)->SetNear(near);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new Vector3Parser(GetScene(), GetParsers(), onDone));
}


void
ObjectParser::HandleFarEvent(yaml_event_t& event)
{
    if (event.type != YAML_SEQUENCE_START_EVENT) {
        /* TODO: Clean this up. */
        assert(event.type != YAML_SEQUENCE_START_EVENT);
        return;
    }

    auto onDone = [this](Vector3 far) {
        std::dynamic_pointer_cast<Box>(mObject)->SetFar(far);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new Vector3Parser(GetScene(), GetParsers(), onDone));
}

} /* namespace yaml */
