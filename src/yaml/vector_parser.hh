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


namespace yaml {

/**
 * Parse a YAML sequence of homogeneous scalars into a vector of the templated
 * type.
 */
template<typename T>
struct VectorParser
    : public UtilityParser<std::vector<T> >
{
    typedef T Type;
    typedef std::vector<T> VectorType;

    /** Constructor */
    VectorParser(Scene& scene, ParserStack& parsers,
                 typename UtilityParser<VectorType>::CallbackFunction callback)
        : UtilityParser<VectorType>(scene, parsers, callback),
          mVector()
    { }

    /**
     * Handle a YAML parser event.
     *
     * @param [in] event The parser event
     */
    void
    HandleEvent(yaml_event_t& event)
    {
        if (event.type == YAML_SEQUENCE_END_EVENT) {
            /*
             * XXX: Need to prefix with this-> for some reason. Maybe the
             * compiler can't figure out the type properly?
             */
            this->SetDone(true);

            /* We have a completed vector. Notify the caller. */
            this->Notify(mVector);
            return;
        }

        if (event.type != YAML_SCALAR_EVENT) {
            assert(event.type != YAML_SCALAR_EVENT);
        }

        Type value;
        std::string valueString((char*)event.data.scalar.value,
                                event.data.scalar.length);
        if (!ParseScalar<Type>(valueString, value)) {
            assert(false);
        }
        mVector.push_back(value);
    }

private:
    VectorType mVector;
};

} /* namespace yaml */

#endif /* __YAML_VECTOR_PARSER_HH__ */
