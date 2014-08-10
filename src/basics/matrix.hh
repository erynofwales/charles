/* matrix.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __BASICS_MATRIX_HH__
#define __BASICS_MATRIX_HH__

#include <cassert>
#include <cstring>
#include <type_traits>

#include "basics/types.hh"


namespace charles {
namespace basics {

struct Vector4;


/** A 4x4 matrix, used for 3D transforms. */
struct Matrix4
{
    /** Create a 4x4 matrix of zeros. */
    static Matrix4 Zero();

    /** Create a 4x4 identity matrix. */
    static Matrix4 Identity();

    /** Create a 4x4 translation matrix. */
    static Matrix4 Translation(Double x, Double y, Double z);

    Matrix4();
    Matrix4(const Double *data);
    Matrix4(const Matrix4 &rhs);

    Matrix4& operator=(const Matrix4 &rhs);

    bool operator==(const Matrix4 &rhs) const;
    bool operator!=(const Matrix4 &rhs) const;

    /**
     * Get the ij'th item. In debug builds, this will assert if i or j are
     * outside the bounds of the array.
     */
    Double& operator()(UInt i, UInt j);
    Double  operator()(UInt i, UInt j) const;

    /** Get the underlying C array */
    const Double *CArray() const;

    /*
     * TODO: For completeness, matrix addition and subtraction, though I have
     * yet to find a need for them...
     */

    /**
     * @defgroup Scalar multiplication
     * @{
     */
    Matrix4  operator*(Double rhs) const;
    Matrix4  operator/(Double rhs) const;
    Matrix4& operator*=(Double rhs);
    Matrix4& operator/=(Double rhs);
    /** @} */

    /**
     * @defgroup Matrix multiplication
     * @{
     */
    Matrix4 operator*(const Matrix4 &rhs) const;
    Vector4 operator*(const Vector4 &rhs) const;
    /** @} */

protected:
    /** The matrix data */
    Double mData[16];
};


/** Scalar multiplication, scalar factor on the left. */
Matrix4 operator*(const Double &lhs, const Matrix4 &rhs);

} /* namespace basics */
} /* namespace charles */

#endif /* __BASICS_MATRIX_HH__ */
