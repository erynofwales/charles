/* vector_parser.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * A VectorParser is a utility parser that processes a sequence of identically
 * typed values and calls back with a vector containing those values
 */

#ifndef __YAML_VECTOR_PARSER_HH__
#define __YAML_VECTOR_PARSER_HH__

#include <cstdio>
#include <vector>

#include "parsers.hh"


namespace charles {
namespace yaml {

/**
 * Parse a YAML sequence of homogeneous scalars into a vector of the templated
 * type.
 */
template<typename T>
struct ScalarSequenceParser
    : public UtilityParser<std::vector<T>>
{
    typedef T Type;
    typedef std::vector<T> VectorType;
    typedef typename UtilityParser<VectorType>::CallbackFunction CallbackFunction;

    ScalarSequenceParser(Scene& scene,
                         Parser::Stack& parsers)
        : UtilityParser<VectorType>(scene, parsers),
          mVector()
    { }

    ScalarSequenceParser(Scene& scene,
                         Parser::Stack& parsers,
                         CallbackFunction callback)
        : UtilityParser<VectorType>(scene, parsers, callback),
          mVector()
    { }

    bool HandleScalar(const std::string& anchor,
                      const std::string& tag,
                      const std::string& value,
                      bool plainImplicit,
                      bool quotedImplicit,
                      Parser::ScalarStyle style,
                      const Parser::Mark& startMark,
                      const Parser::Mark& endMark);

    bool HandleSequenceEnd(const Parser::Mark& startMark,
                           const Parser::Mark& endMark);

private:
    VectorType mVector;
};


struct Vector3Parser
    : ScalarSequenceParser<double>
{
    typedef std::function<void(Vector3)> CallbackFunction;

    Vector3Parser(Scene& scene, Parser::Stack& parsers, CallbackFunction onDone);
};


struct ColorParser
    : ScalarSequenceParser<double>
{
    typedef std::function<void(Color)> CallbackFunction;

    ColorParser(Scene& scene, Parser::Stack& parsers, CallbackFunction onDone);
    ~ColorParser();
};

} /* namespace yaml */
} /* namespace charles */

#endif /* __YAML_VECTOR_PARSER_HH__ */
