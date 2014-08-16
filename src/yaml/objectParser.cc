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

#include "material.hh"
#include "object.hh"
#include "objectBox.hh"
#include "objectPlane.hh"
#include "objectSphere.hh"
#include "yaml/objectParser.hh"
#include "yaml/vectorParser.hh"


using charles::basics::Color;
using charles::basics::Vector4;


namespace charles {
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
    } else if (tag == "!Object.Plane") {
        mType = Type::Plane;
        mObject.reset(new Plane());
    } else if (tag == "!Object.Sphere") {
        mType = Type::Sphere;
        mObject.reset(new Sphere());
    } else {
        assert(false);
    }
    GetScene().AddObject(mObject);
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

    static const std::map<std::string, Section> sPlaneSections = {
        {"normal", NormalSection},
        {"distance", DistanceSection}
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
    } else if (mType == Type::Plane) {
        if (sPlaneSections.count(key) > 0) {
            mSection = sPlaneSections.at(key);
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

        /* Spheres */
        case OriginSection:
            HandleOriginEvent(event);
            break;
        case RadiusSection:
            HandleRadiusEvent(event);
            break;

        /* Boxes */
        case NearSection:
            HandleNearEvent(event);
            break;
        case FarSection:
            HandleFarEvent(event);
            break;

        /* Planes */
        case NormalSection:
            HandleNormalEvent(event);
            break;
        case DistanceSection:
            HandleDistanceEvent(event);
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

    auto onDone = [this](Vector4 origin) {
        mObject->Place(origin);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new Vector4Parser(GetScene(), GetParsers(), onDone));
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
    std::dynamic_pointer_cast<Sphere>(mObject)->SetRadius(radius);
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

    auto onDone = [this](Vector4 near) {
        std::dynamic_pointer_cast<Box>(mObject)->SetNear(near);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new Vector4Parser(GetScene(), GetParsers(), onDone));
}


void
ObjectParser::HandleFarEvent(yaml_event_t& event)
{
    if (event.type != YAML_SEQUENCE_START_EVENT) {
        /* TODO: Clean this up. */
        assert(event.type != YAML_SEQUENCE_START_EVENT);
        return;
    }

    auto onDone = [this](Vector4 far) {
        std::dynamic_pointer_cast<Box>(mObject)->SetFar(far);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new Vector4Parser(GetScene(), GetParsers(), onDone));
}


void
ObjectParser::HandleNormalEvent(yaml_event_t& event)
{
    if (event.type != YAML_SEQUENCE_START_EVENT) {
        /* TODO: Clean this up. */
        assert(event.type != YAML_SEQUENCE_START_EVENT);
        return;
    }

    auto onDone = [this](Vector4 normal) {
        std::dynamic_pointer_cast<Plane>(mObject)->SetNormal(normal);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new Vector4Parser(GetScene(), GetParsers(), onDone));
}


void
ObjectParser::HandleDistanceEvent(yaml_event_t& event)
{
    if (event.type != YAML_SCALAR_EVENT) {
        /* TODO: Clean this up. */
        assert(false);
    }

    Double distance;
    std::string scalar((char *)event.data.scalar.value,
                       event.data.scalar.length);
    if (!ParseScalar<Double>(scalar, distance)) {
        /* TODO: Clean this up. */
        assert(false);
    }
    std::dynamic_pointer_cast<Plane>(mObject)->SetDistance(distance);
    mSection = NoSection;
    SetShouldExpectKey(true);
}

} /* namespace yaml */
} /* namespace charles */
