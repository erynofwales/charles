/* vector.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __BASICS_VECTOR_HH__
#define __BASICS_VECTOR_HH__

#include "basics/matrix.hh"
#include "basics/types.hh"


namespace charles {
namespace basics {

template<uint N>
struct Vector
    : public Matrix<N,1>
{ };


typedef Vector<4> Vector4;

} /* namespace basics */
} /* namespace charles */

#endif /* __BASICS_VECTOR_HH__ */

