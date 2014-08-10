/* vectorParser.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cassert>

#include "yaml/vectorParser.hh"


using charles::basics::Color;
using charles::basics::Vector4;


namespace charles {
namespace yaml {

Vector4Parser::Vector4Parser(Scene& scene,
                             ParserStack& parsers,
                             CallbackFunction onDone)
    : ScalarSequenceParser(scene, parsers)
{
    auto onSeqDone = [this, onDone](std::vector<double> seq) {
        if (seq.size() != 3) {
            assert(seq.size() != 3);
            return;
        }
        onDone(Vector4(seq[0], seq[1], seq[2]));
    };
    SetCallback(onSeqDone);
}


ColorParser::ColorParser(Scene& scene,
                         ParserStack& parsers,
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
