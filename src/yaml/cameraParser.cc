/* camera_parser.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cassert>

#include "camera.hh"
#include "yaml/cameraParser.hh"
#include "yaml/vectorParser.hh"


namespace charles {
namespace yaml {

CameraParser::CameraParser(Scene& scene,
                           ParserStack& parsers)
    : ScalarMappingParser(scene, parsers),
      mCamera(new PerspectiveCamera()),
      mSection(NoSection),
      mType(TypePerspective)
{
    GetScene().SetCamera(mCamera);
}


CameraParser::~CameraParser()
{ }


void
CameraParser::HandleKeyEvent(const std::string& key)
{
    static const std::map<std::string, Section> sSections = {
        {"direction", DirectionSection},
        {"lookAt", LookAtSection},
        {"origin", OriginSection},
        {"right", RightSection},
        {"type", TypeSection},
        {"up", UpSection},
    };

    if (sSections.count(key) > 0) {
        mSection = sSections.at(key);
    }
    else {
        mSection = NoSection;
    }
}


void
CameraParser::HandleValueEvent(yaml_event_t& event)
{
    switch (mSection) {
        case DirectionSection:
            HandleDirectionEvent(event);
            break;
        case LookAtSection:
            HandleLookAtEvent(event);
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
CameraParser::HandleLookAtEvent(yaml_event_t& event)
{
    if (event.type != YAML_SEQUENCE_START_EVENT) {
        /* TODO: Clean this up. */
        assert(event.type != YAML_SEQUENCE_START_EVENT);
        return;
    }

    auto onDone = [this](Vector3 lookAt) {
        mCamera->LookAt(lookAt);
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
        mCamera->SetOrigin(origin);
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

    auto onDone = [this](Vector3 right) {
        mCamera->SetRight(right);
        mSection = NoSection;
        SetShouldExpectKey(true);
    };

    GetParsers().push(new Vector3Parser(GetScene(), GetParsers(), onDone));
}


void
CameraParser::HandleTypeEvent(yaml_event_t& event)
{
    if (event.type != YAML_SCALAR_EVENT) {
        assert(event.type != YAML_SCALAR_EVENT);
        return;
    }

    std::string value = std::string((char*)event.data.scalar.value,
                                    event.data.scalar.length);
    if (value == "perspective") {
        if (mType == TypeOrthographic) {
            Camera *newCamera = new PerspectiveCamera(*mCamera);
            delete mCamera;
            mCamera = newCamera;
            GetScene().SetCamera(newCamera);
        }
    }
    else if (value == "orthographic") {
        if (mType == TypePerspective) {
            Camera *newCamera = new OrthographicCamera(*mCamera);
            delete mCamera;
            mCamera = newCamera;
            GetScene().SetCamera(newCamera);
        }
    }
    else {
        assert(false);
    }

    mSection = NoSection;
    SetShouldExpectKey(true);
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
} /* namespace charles */
