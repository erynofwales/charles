/* parsers.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * Some top-level YAML parser objects.
 */

#ifndef __YAML_PARSERS_HH__
#define __YAML_PARSERS_HH__

#include <functional>
#include <memory>
#include <stack>
#include <sstream>

#include "yaml.h"

#include "scene.h"


namespace charles {
namespace yaml {

/**
 * A Parser handles parsing a chunk of YAML, updating its mScene member as
 * necessary.
 */
struct Parser
{
    typedef std::shared_ptr<Parser> Ptr;
    typedef std::stack<Ptr> Stack;

    typedef yaml_mark_t Mark;

    enum class ScalarStyle {
        Any          = YAML_ANY_SCALAR_STYLE,
        Plain        = YAML_PLAIN_SCALAR_STYLE,
        SingleQuoted = YAML_SINGLE_QUOTED_SCALAR_STYLE,
        DoubleQuoted = YAML_DOUBLE_QUOTED_SCALAR_STYLE,
        Literal      = YAML_LITERAL_SCALAR_STYLE,
        Folded       = YAML_FOLDED_SCALAR_STYLE
    }

    enum class SequenceStyle {
        Any   = YAML_ANY_SEQUENCE_STYLE,
        Block = YAML_BLOCK_SEQUENCE_STYLE,
        Flow  = YAML_FLOW_SEQUENCE_STYLE
    };

    enum class MappingStyle {
        Any   = YAML_ANY_MAPPING_STYLE,
        Block = YAML_BLOCK_MAPPING_STYLE,
        Flow  = YAML_FLOW_MAPPING_STYLE
    };

    /** Constructor */
    Parser(Scene& scene, Stack& parsers);

    /** Destructor */
    virtual ~Parser();

    /**
     * Called by the parser event loop to handle a libyaml parser event.
     * Breaks out the event's data and calls the appropriate handler method.
     *
     * @param [in] event        A libyaml parser event object
     */
    virtual void HandleEvent(yaml_event_t& event);

    /**
     * Handle a STREAM-START event.
     *
     * @param [in] encoding     The character encoding of the stream
     * @param [in] startMark    The start of the event
     * @param [in] endMark      The end of the event
     * @return `true` or `false` indicating whether the event was successfully
     *         handled
     */
    virtual bool HandleStreamStart(const std::string& encoding,
                                   const Mark& startMark,
                                   const Mark& endMark);

    /**
     * Handle a STREAM-END event.
     *
     * @param [in] startMark    The start of the event
     * @param [in] endMark      The end of the event
     * @returns `true` or `false` indicating whether the event was successfully
     *          handled
     */
    virtual bool HandleStreamEnd(const Mark& startMark,
                                 const Mark& endMark);

    /**
     * Handle a DOCUMENT-START event.
     *
     * @param [in] versionDirective     TODO
     * @param [in] tagDirectives        TODO
     * @param [in] implicit     Is the start of the document implicitly
     *                          specified?
     * @param [in] startMark    The start of the event
     * @param [in] endMark      The end of the event
     * @returns `true` or `false` indicating whether the event was successfully
     *          handled
     */
    virtual bool HandleDocumentStart(/* TODO: Version directive ,*/
                                     /* TODO: Tag directive list ,*/
                                     bool implicit,
                                     const Mark& startMark,
                                     const Mark& endMark);

    /**
     * Handle a DOCUMENT-END event.
     *
     * @param [in] implicit     Is the end of the document implicitly specified?
     * @param [in] startMark    The start of the event
     * @param [in] endMark      The end of the event
     * @returns `true` or `false` indicating whether the event was successfully
     *          handled
     */
    virtual bool HandleDocumentEnd(bool implicit,
                                   const Mark& startMark,
                                   const Mark& endMark);

    virtual void HandleMappingStart(const std::string& anchor,
                                    const std::string& tag,
                                    bool implicit,
                                    MappingStyle style,
                                    const Mark& startMark,
                                    const Mark& endMark);
    virtual void HandleMappingEnd(const Mark& startMark,
                                  const Mark& endMark);

    virtual void HandleSequenceStart(const std::string& anchor,
                                     const std::string& tag,
                                     bool implicit,
                                     SequenceStyle style,
                                     const Mark& startMark,
                                     const Mark& endMark);
    virtual void HandleSequenceEnd(const Mark& startMark,
                                   const Mark& endMark);

    virtual void HandleAlias(const std::string& anchor,
                             const Mark& startMark,
                             const Mark& endMark);
    virtual void HandleScalar(const std::string& anchor,
                              const std::string& tag,
                              const std::string& value,
                              bool plainImplicit,
                              bool quotedImplicit,
                              ScalarStyle style,
                              const Mark& startMark,
                              const Mark& endMark);

    void SetDone(bool done);
    bool GetDone() const;

protected:
    Scene& GetScene() const;
    Stack& GetParsers() const;

private:
    /** The Scene being described by the YAML this parser is parsing. */
    Scene& mScene;

    /** The stack of parsers. */
    Stack& mParsers;

    /** `true` if the parser is done parsing */
    bool mDone;
};


/**
 * UtilityParsers handle small reusable bits of YAML. Their constructors take a
 * C++11 lambda, which will be called back with the result of the parsed data.
 */
template<typename T>
struct UtilityParser
    : public Parser
{
    typedef std::function<void (T)> CallbackFunction;

    UtilityParser(Scene& scene,
                  ParserStack& parsers)
        : Parser(scene, parsers),
          mCallback()
    { }

    UtilityParser(Scene& scene,
                  ParserStack& parsers,
                  CallbackFunction callback)
        : Parser(scene, parsers),
          mCallback(callback)
    { }

    virtual
    ~UtilityParser()
    { }

    void
    Notify(T value)
    {
        if (mCallback) {
            mCallback(value);
        }
    }

    void
    SetCallback(CallbackFunction callback)
    {
        mCallback = callback;
    }

private:
    CallbackFunction mCallback;
};


/**
 * Defines traits for the ParseScalar function. In particular, defines the
 * format strings for supported scalar types.
 */
template<typename T>
struct ScalarParserTraits
{
    static const char* fmt;
};


/**
 * Parse a YAML scalar value into a native datatype.
 *
 * @param [in]  scalar The YAML scalar value
 * @param [out] value  The parsed value of the scalar value
 * @return `true` if the conversion succeeded
 */
template<typename T>
bool
ParseScalar(const std::string& scalar,
            T& value)
{
    std::stringstream s(scalar);
    return (bool)(s >> value);
}

} /* namespace yaml */
} /* namespace charles */

#endif /* __YAML_PARSERS_HH__ */
