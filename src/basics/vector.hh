/* vector.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __BASICS_VECTOR_HH__
#define __BASICS_VECTOR_HH__

#include <ostream>

#include "basics/matrix.hh"
#include "basics/types.hh"


namespace charles {
namespace basics {

/** A 4x1 matrix, used for specifying points and directions in 3D space. */
struct Vector4
{
    Vector4();
    Vector4(Double x, Double y, Double z);

    Vector4 &operator=(const Vector4 &rhs);

    /**
     * @defgroup Component access
     * @{
     */
    Double& X();
    Double  X() const;
    Double& Y();
    Double  Y() const;
    Double& Z();
    Double  Z() const;

    Double &operator()(UInt i);
    Double  operator()(UInt i) const;

    /** Get the underlying C array. */
    const Double *CArray() const;
    /** @} */

    bool operator==(const Vector4 &rhs) const;
    bool operator!=(const Vector4 &rhs) const;

    /**
     * @defgroup Scalar multiplication
     * @{
     */
    Vector4 operator*(Double rhs) const;
    Vector4 operator/(Double rhs) const;
    Vector4 &operator*=(Double rhs);
    Vector4 &operator/=(Double rhs);
    /** @} */

    /**
     * @defgroup Vector addition and subtraction
     * @{
     */
    Vector4 operator+(const Vector4 &rhs) const;
    Vector4 operator-(const Vector4 &rhs) const;
    Vector4 &operator+=(const Vector4 &rhs);
    Vector4 &operator-=(const Vector4 &rhs);
    /** @} */

    /** Negate this vector. */
    Vector4 operator-() const;

    /** Get the length-squared of this vector. */
    Double Length2() const;

    /** Get the length of this vector. */
    Double Length() const;

    /** Get the dot product of `this` and `rhs`. */
    Double Dot(const Vector4 &rhs) const;

    /** Get the cross product of `this` and `rhs`. */
    Vector4 Cross(const Vector4& rhs) const;

    /** Normalize this vector. */
    Vector4& Normalize();

private:
    Double mData[4];
};


/** Scalar multiplication of vectors, with the scalar factor on the left. */
Vector4 operator*(Double lhs, const Vector4 &rhs);


/** Normalize a copy of the given vector. */
Vector4 Normalized(Vector4 v);


Vector4 LinearCombination(Double k1, const Vector4 &v1,
                          Double k2, const Vector4 &v2,
                          Double k3, const Vector4 &v3);


std::ostream& operator<<(std::ostream &ost, const Vector4 &v);

} /* namespace basics */
} /* namespace charles */

#endif /* __BASICS_VECTOR_HH__ */

