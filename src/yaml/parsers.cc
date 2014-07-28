/* parsers.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * YAML parser superclasses.
 */

#include <cassert>
#include <ostream>

#include "yaml.h"

#include "parsers.hh"


namespace charles {
namespace yaml {

#pragma mark Parser

Parser::Parser(Scene& scene,
               Stack& parsers)
    : mScene(scene),
      mParsers(parsers),
      mDone(false)
{ }


Parser::~Parser()
{ }


bool
Parser::HandleEvent(const yaml_event_t& event)
{
#define YAML_BOOL(x) ((x) != 0)
#define YAML_STRING(x) ((char *)(x))

    bool success = true;

    switch (event.type) {
        case YAML_STREAM_START_EVENT:
            success = HandleStreamStart(Encoding(event.data.stream_start.encoding),
                                        event.start_mark,
                                        event.end_mark);
            break;

        case YAML_STREAM_END_EVENT:
            success = HandleStreamEnd(event.start_mark, event.end_mark);
            break;

        case YAML_DOCUMENT_START_EVENT:
            success = HandleDocumentStart(*event.data.document_start.version_directive,
                                          TagDirectiveList(),
                                          YAML_BOOL(event.data.document_start.implicit),
                                          event.start_mark,
                                          event.end_mark);
            break;

        case YAML_DOCUMENT_END_EVENT:
            success = HandleDocumentEnd(YAML_BOOL(event.data.document_end.implicit),
                                        event.start_mark,
                                        event.end_mark);
            break;

        case YAML_MAPPING_START_EVENT:
            success = HandleMappingStart(YAML_STRING(event.data.mapping_start.anchor),
                                         YAML_STRING(event.data.mapping_start.tag),
                                         YAML_BOOL(event.data.mapping_start.implicit),
                                         MappingStyle(event.data.mapping_start.style),
                                         event.start_mark,
                                         event.end_mark);
            break;

        case YAML_MAPPING_END_EVENT:
            success = HandleMappingEnd(event.start_mark, event.end_mark);
            break;

        case YAML_SEQUENCE_START_EVENT:
            success = HandleSequenceStart(YAML_STRING(event.data.sequence_start.anchor),
                                          YAML_STRING(event.data.sequence_start.tag),
                                          YAML_BOOL(event.data.sequence_start.implicit),
                                          SequenceStyle(event.data.sequence_start.style),
                                          event.start_mark,
                                          event.end_mark);
            break;

        case YAML_SEQUENCE_END_EVENT:
            success = HandleSequenceEnd(event.start_mark, event.end_mark);
            break;

        case YAML_ALIAS_EVENT:
            success = HandleAlias(YAML_STRING(event.data.alias.anchor),
                                  event.start_mark,
                                  event.end_mark);
            break;

        case YAML_SCALAR_EVENT:
            success = HandleScalar(YAML_STRING(event.data.scalar.anchor),
                                   YAML_STRING(event.data.scalar.tag),
                                   std::string(YAML_STRING(event.data.scalar.value),
                                               event.data.scalar.length),
                                   YAML_BOOL(event.data.scalar.plain_implicit),
                                   YAML_BOOL(event.data.scalar.quoted_implicit),
                                   ScalarStyle(event.data.scalar.style),
                                   event.start_mark,
                                   event.end_mark);
            break;

        default:
            assert(false);
            success = false;
            break;
    }

    return success;

#undef YAML_STR
#undef YAML_BOOL
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

bool
Parser::HandleStreamStart(Encoding encoding,
                          const Mark& startMark,
                          const Mark& endMark)
{
    PrintUnexpectedEventError("STREAM-START", startMark);
    assert(false);
    return false;
}


bool
Parser::HandleStreamEnd(const Mark& startMark,
                        const Mark& endMark)
{
    PrintUnexpectedEventError("STREAM-END", startMark);
    assert(false);
    return false;
}


bool
Parser::HandleDocumentStart(const VersionDirective versionDirective,
                            const TagDirectiveList& tagDirectives,
                            bool implicit,
                            const Mark& startMark,
                            const Mark& endMark)
{
    PrintUnexpectedEventError("DOCUMENT-START", startMark);
    assert(false);
    return false;
}


bool
Parser::HandleDocumentEnd(bool implicit,
                          const Mark& startMark,
                          const Mark& endMark)
{
    PrintUnexpectedEventError("DOCUMENT-END", startMark);
    assert(false);
    return false;
}


bool
Parser::HandleMappingStart(const std::string& anchor,
                           const std::string& tag,
                           bool implicit,
                           MappingStyle style,
                           const Mark& startMark,
                           const Mark& endMark)
{
    PrintUnexpectedEventError("MAPPING-START", startMark);
    assert(false);
    return false;
}


bool
Parser::HandleMappingEnd(const Mark& startMark,
                         const Mark& endMark)
{
    PrintUnexpectedEventError("MAPPING-END", startMark);
    assert(false);
    return false;
}


bool
Parser::HandleSequenceStart(const std::string& anchor,
                            const std::string& tag,
                            bool implicit,
                            SequenceStyle style,
                            const Mark& startMark,
                            const Mark& endMark)
{
    PrintUnexpectedEventError("SEQUENCE-START", startMark);
    assert(false);
    return false;
}


bool
Parser::HandleSequenceEnd(const Mark& startMark,
                          const Mark& endMark)
{
    PrintUnexpectedEventError("SEQUENCE-END", startMark);
    assert(false);
    return false;
}


bool
Parser::HandleAlias(const std::string& anchor,
                    const Mark& startMark,
                    const Mark& endMark)
{
    PrintUnexpectedEventError("ALIAS", startMark);
    assert(false);
    return false;
}


bool
Parser::HandleScalar(const std::string& anchor,
                     const std::string& tag,
                     const std::string& value,
                     bool plainImplicit,
                     bool quotedImplicit,
                     ScalarStyle style,
                     const Mark& startMark,
                     const Mark& endMark)
{
    PrintUnexpectedEventError("SCALAR", startMark);
    assert(false);
    return false;
}

#pragma clang diagnostic pop

void
Parser::PrintUnexpectedEventError(const std::string& eventName,
                                  const Parser::Mark& mark)
    const
{
    std::cerr << mark.line << ":" << mark.column
              << ": Unexpected " << eventName << " event.\n";
}

} /* namespace yaml */
} /* namespace charles */
