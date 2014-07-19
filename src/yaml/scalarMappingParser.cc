/* scalarMappingParser.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * Implementation of ScalarMappingParser.
 */

#include <cassert>
#include <cstdio>

#include "scalarMappingParser.hh"


namespace yaml {

ScalarMappingParser::ScalarMappingParser(Scene& scene,
                                         ParserStack& parsers)
    : Parser(scene, parsers),
      mShouldExpectKey(true)
{ }


ScalarMappingParser::~ScalarMappingParser()
{ }


void
ScalarMappingParser::HandleEvent(yaml_event_t& event)
{
    if (event.type == YAML_MAPPING_END_EVENT) {
        SetDone(true);
        return;
    }

    if (mShouldExpectKey && event.type == YAML_SCALAR_EVENT) {
        HandleKeyEvent(std::string((char*)event.data.scalar.value,
                                   event.data.scalar.length));
    }
    else {
        HandleValueEvent(event);
    }
}

#pragma mark key/value handling

void
ScalarMappingParser::HandleKeyEvent(const std::string& key)
{
    printf("%s: key = %s\n", __PRETTY_FUNCTION__, key.c_str());
    assert(false);
}


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

void
ScalarMappingParser::HandleValueEvent(yaml_event_t& event)
{
    assert(false);
}

#pragma clang diagnostic pop


void
ScalarMappingParser::SetShouldExpectKey(bool shouldExpectKey)
{
    mShouldExpectKey = shouldExpectKey;
}


bool
ScalarMappingParser::GetShouldExpectKey()
    const
{
    return mShouldExpectKey;
}

} /* namespace yaml */
