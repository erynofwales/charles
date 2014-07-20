/* camera_parser.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "cameraParser.hh"


namespace yaml {

CameraParser::CameraParser(Scene& scene,
                           ParserStack& parsers)
    : ScalarMappingParser(scene, parsers),
      mCamera(new PerspectiveCamera())
{
    GetScene().SetCamera(mCamera);
}


CameraParser::~CameraParser()
{ }


void
CameraParser::HandleKeyEvent(const std::string& key)
{
    static const std::map<std::string, Section> sSections = {
        {"direction": DirectionSection},
        {"origin": OriginSection},
        {"right": RightSection},
        {"type": TypeSection},
        {"up": UpSection},
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
        case DirectionSection:
            HandleDirectionEvent(event);
            break;
        case OriginSection:
            HandleOriginEvent(event);
            break;
        case RightSection:
            HandleRightEvent(event);
            break;
        case TypeSection:
            HandleTypeEvent(event);
            break;
        case UpSection:
            HandleUpEvent(event);
            break;
        default:
            assert(false);
            break;
    }
}


void
CameraParser::HandleDirectionEvent(yaml_event_t& event)
{
    if (event.type != YAML_SEQUENCE_START_EVENT) {
        /* TODO: Clean this up. */
        assert(event.type != YAML_SEQUENCE_START_EVENT);
        return;
    }

    auto onDone = [this](Vector3 origin) {
        mCamera->set_direction(origin);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new Vector3Parser(GetScene(), GetParsers(), onDone));
}


void
CameraParser::HandleOriginEvent(yaml_event_t& event)
{
    if (event.type != YAML_SEQUENCE_START_EVENT) {
        /* TODO: Clean this up. */
        assert(event.type != YAML_SEQUENCE_START_EVENT);
        return;
    }

    auto onDone = [this](Vector3 origin) {
        mCamera->set_origin(origin);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new Vector3Parser(GetScene(), GetParsers(), onDone));
}


void
CameraParser::HandleRightEvent(yaml_event_t& event)
{
    if (event.type != YAML_SEQUENCE_START_EVENT) {
        /* TODO: Clean this up. */
        assert(event.type != YAML_SEQUENCE_START_EVENT);
        return;
    }

    auto onDone = [this](Vector3 origin) {
        mCamera->SetRight(origin);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new Vector3Parser(GetScene(), GetParsers(), onDone));
}


void
CameraParser::HandleUpEvent(yaml_event_t& event)
{
    if (event.type != YAML_SEQUENCE_START_EVENT) {
        /* TODO: Clean this up. */
        assert(event.type != YAML_SEQUENCE_START_EVENT);
        return;
    }

    auto onDone = [this](Vector3 origin) {
        mCamera->SetUp(origin);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new Vector3Parser(GetScene(), GetParsers(), onDone));
}

} /* namespace yaml */
