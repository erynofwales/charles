/* vectorParser.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cassert>

#include "yaml/scalarSequenceParser.hh"


namespace charles {
namespace yaml {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

template<typename T>
bool
ScalarSequenceParser<T>::HandleScalar(const std::string& anchor,
                                      const std::string& tag,
                                      const std::string& value,
                                      bool plainImplicit,
                                      bool quotedImplicit,
                                      Parser::ScalarStyle style,
                                      const Parser::Mark& startMark,
                                      const Parser::Mark& endMark)
{
    Type scalarValue;
    if (!ParseScalar<Type>(value, scalarValue)) {
        assert(false);
        return false;
    }
    mVector.push_back(scalarValue);
    return true;
}


template<typename T>
bool
ScalarSequenceParser<T>::HandleSequenceEnd(const Parser::Mark& startMark,
                                           const Parser::Mark& endMark)
{
    /*
     * XXX: Need to prefix with this-> for some reason. Maybe the compiler can't
     * figure out the type properly?
     */
    this->SetDone(true);

    /* We have a completed vector. Notify the caller. */
    this->Notify(mVector);

    return true;
}

#pragma clang diagnostic pop


Vector3Parser::Vector3Parser(Scene& scene,
                             Parser::Stack& parsers,
                             CallbackFunction onDone)
    : ScalarSequenceParser(scene, parsers)
{
    auto onSeqDone = [this, onDone](std::vector<double> seq) {
        if (seq.size() != 3) {
            assert(seq.size() != 3);
            return;
        }
        onDone(Vector3(seq[0], seq[1], seq[2]));
    };
    SetCallback(onSeqDone);
}


ColorParser::ColorParser(Scene& scene,
                         Parser::Stack& parsers,
                         CallbackFunction onDone)
    : ScalarSequenceParser(scene, parsers)
{
    auto onSeqDone = [this, onDone](std::vector<double> seq) {
        size_t seqSize = seq.size();
        if (seqSize == 3) {
            onDone(Color(seq[0], seq[1], seq[2]));
        }
        else if (seqSize == 4) {
            onDone(Color(seq[0], seq[1], seq[2], seq[3]));
        }
        else {
            assert(seqSize != 3 || seqSize != 4);
        }
    };
    SetCallback(onSeqDone);
}

} /* namespace yaml */
} /* namespace charles */
