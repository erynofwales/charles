/* camera_parser.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __YAML_CAMERAPARSER_HH__
#define __YAML_CAMERAPARSER_HH__

#include "yaml/scalarMappingParser.hh"


struct Camera;


namespace yaml {

struct CameraParser
    : public ScalarMappingParser
{
    CameraParser(Scene& scene, ParserStack& parsers);
    ~CameraParser();

protected:
    void HandleKeyEvent(const std::string& key);
    void HandleValueEvent(yaml_event_t& event);

private:
    enum Section {
        NoSection,
        DirectionSection,
        OriginSection,
        RightSection,
        TypeSection,
        UpSection
    };

    Camera *mCamera;
    Section mSection;

    void HandleDirectionEvent(yaml_event_t& event);
    void HandleOriginEvent(yaml_event_t& event);
    void HandleRightEvent(yaml_event_t& event);
    void HandleTypeEvent(yaml_event_t& event);
    void HandleUpEvent(yaml_event_t& event);
};

} /* namespace yaml */

#endif /* __YAML_CAMERAPARSER_HH__ */

