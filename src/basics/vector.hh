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

template<UInt N>
struct Vector
    : public Matrix<N,1>
{ };


struct Vector4
    : public Vector<4>
{
    Vector4();
    Vector4(const Double& x, const Double& y, const Double& z);

    Double& X();
    Double& Y();
    Double& Z();

    /** Get the length-squared of this vector. */
    Double Length2() const;

    /** Get the length of this vector. */
    Double Length() const;

    /** Get the dot product of `this` and `rhs`. */
    Double Dot(const Vector4& rhs) const;

    /** Get the cross product of `this` and `rhs`. */
    Vector4 Cross(const Vector4& rhs) const;

    /** Normalize this vector. */
    Vector4& Normalize();
};


/** Normalize the given vector and return a copy of it. */
Vector4& Normalized(const Vector4& v);

} /* namespace basics */
} /* namespace charles */

#endif /* __BASICS_VECTOR_HH__ */

