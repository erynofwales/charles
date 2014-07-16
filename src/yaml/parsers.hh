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
#include <stack>

#include "yaml.h"

#include "scene.h"


namespace yaml {

struct Parser;
typedef std::stack<Parser*> ParserStack;


/**
 * A Parser handles parsing a chunk of YAML, updating its mScene member as
 * necessary.
 */
struct Parser
{
    /** Constructor */
    Parser(Scene& scene, ParserStack& parsers);

    /** Destructor */
    virtual ~Parser();

    /**
     * Called by the parser event loop to handle a libyaml parser event.
     *
     * @param [in] event A libyaml parser event object
     */
    virtual void HandleEvent(yaml_event_t& event);


    /** Set the done flag. */
    void SetDone(bool done);

    /**
     * Returns true if the parser is done parsing.
     *
     * @returns `true` if done, `false` if not
     */
    bool GetDone() const;

protected:
    Scene& GetScene() const;
    ParserStack& GetParsers() const;

private:
    /** The Scene being described by the YAML this parser is parsing. */
    Scene& mScene;

    /** The stack of parsers. */
    ParserStack& mParsers;

    /** `true` if the parser is done parsing */
    bool mDone;
};


/**
 * UtilityParsers handle small reusable bits of YAML and their constructors take
 * a C++11 lambda, which will be called back with the result of the parsed data.
 */
template<typename CallbackType>
struct UtilityParser
    : public Parser
{
    typedef std::function<CallbackType> CallbackFunction;

    UtilityParser(Scene& scene,
                  ParserStack& parsers,
                  CallbackFunction callback)
        : Parser(scene, parsers),
          mCallback(callback)
    { }

    virtual
    ~UtilityParser()
    { }

private:
    CallbackFunction mCallback;
};

} /* namespace yaml */

#endif /* __YAML_PARSERS_HH__ */
