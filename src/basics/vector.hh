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
    const Double& X() const;
    Double& Y();
    const Double& Y() const;
    Double& Z();
    const Double& Z() const;

    Vector4 operator*(const Double& rhs) const;

    Vector4 operator+(const Vector4& rhs) const;
    Vector4& operator+=(const Vector4& rhs);
    Vector4 operator-(const Vector4& rhs) const;
    Vector4& operator-=(const Vector4& rhs);

    Vector4 operator-() const;

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


/** Scalar multiplication of vectors, with the scalar factor on the left. */
Vector4 operator*(const Double& lhs, const Vector4& rhs);


/** Normalize the given vector and return a copy of it. */
Vector4& Normalized(const Vector4& v);

} /* namespace basics */
} /* namespace charles */

#endif /* __BASICS_VECTOR_HH__ */

