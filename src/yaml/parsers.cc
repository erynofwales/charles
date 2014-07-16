/* parsers.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * YAML parser superclasses.
 */

#include <cassert>

#include "yaml.h"

#include "parsers.hh"


namespace yaml {

Parser::Parser(Scene& scene,
               ParserStack& parsers)
    : mScene(scene),
      mParsers(parsers)
{ }


Parser::~Parser()
{ }


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

void
Parser::HandleEvent(yaml_event_t& event)
{
    /* Shouldn't ever get here. */
    assert(false);
}

#pragma clang diagnostic pop


void
Parser::SetDone(bool done)
{
    mDone = done;
}


bool
Parser::GetDone()
    const
{
    return mDone;
}


Scene&
Parser::GetScene()
    const
{
    return mScene;
}


ParserStack&
Parser::GetParsers()
    const
{
    return mParsers;
}

} /* namespace yaml */
