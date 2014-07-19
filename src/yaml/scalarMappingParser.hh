/* scalarMappingParser.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * Declares a yaml::ScalarMappingParser.
 */


#ifndef __YAML_SCALARMAPPINGPARSER_HH__
#define __YAML_SCALARMAPPINGPARSER_HH__

#include <functional>
#include <map>
#include <string>

#include "yaml/parsers.hh"


namespace yaml {

struct ScalarMappingParser
    : public Parser
{
    ScalarMappingParser(Scene& scene, ParserStack& parsers);
    virtual ~ScalarMappingParser();

    void HandleEvent(yaml_event_t& event);

protected:
    virtual void HandleKeyEvent(const std::string& key);
    virtual void HandleValueEvent(yaml_event_t& event);

    void SetShouldExpectKey(bool shouldExpectKey);
    bool GetShouldExpectKey() const;

private:
	/** Subclasses set this to `true` when they're finished parsing the value. */
	bool mShouldExpectKey;
};

} /* namespace yaml */

#endif /* __YAML_SCALARMAPPINGPARSER_HH__ */
