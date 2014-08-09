/* basics.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * Top-level include for the basics module.
 */

#ifndef __BASICS_BASICS_HH__
#define __BASICS_BASICS_HH__

#include "basics/matrix.hh"
#include "basics/types.hh"
#include "basics/vector.hh"


namespace charles {
namespace basics {

/** A 4-square matrix */
typedef Matrix<4> Matrix4;

} /* namespace basics */
} /* namespace charles */

#endif /* __BASICS_BASICS_HH__ */
