/* matrix.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cstring>
#include <stdexcept>
#include <sstream>

#include "basics/matrix.hh"

#include "basics/util.hh"


namespace charles {
namespace basics {

#pragma mark Static Methods

/*
 * charles::basics::Matrix4::Zero --
 */
/* static */ Matrix4
Matrix4::Zero()
{
    Matrix4 m;
    bzero(m.mData, sizeof(Double) * 16);
    return m;
}


/*
 * charles::basics::Matrix4::Identity --
 */
/* static */ Matrix4
Matrix4::Identity()
{
    auto m = Matrix4::Zero();
    for (size_t i = 0; i < 4; i++) {
        m(i,i) = 1.0;
    }
    return m;
}


/*
 * charles::basics::TranslationMatrix --
 */
/* static */ Matrix4
Translation(Double x,
            Double y,
            Double z)
{
    Matrix4 m = Matrix4::Identity();
    m(0,3) = x;
    m(1,3) = y;
    m(2,3) = z;
    return m;
}

#pragma mark Constructors and Assignment

/*
 * charles::basics::Matrix4::Matrix4 --
 */
Matrix4::Matrix4()
    : mData()
{ }


/*
 * charles::basics::Matrix4::Matrix4 --
 */
Matrix4::Matrix4(const Double data[16])
{
    memcpy(mData, data, sizeof(Double) * 16);
}


/*
 * charles::basics::Matrix4::Matrix4 --
 */
Matrix4::Matrix4(const Matrix4 &rhs)
    : Matrix4(rhs.mData)
{ }


/*
 * charles::basics::Matrix4::operator= --
 */
Matrix4&
Matrix4::operator=(const Matrix4 &rhs)
{
    memcpy(mData, rhs.mData, sizeof(Double) * 16);
    return *this;
}

#pragma mark Boolean Operators

/*
 * charles::basics::Matrix4::operator== --
 */
bool
Matrix4::operator==(const Matrix4 &rhs)
    const
{
    for (int i = 0; i < 16; i++) {
        if (!NearlyEqual(mData[i], rhs.mData[i])) {
            return false;
        }
    }
    return true;
}


/*
 * charles::basics::Matrix4::operator!= --
 */
bool
Matrix4::operator!=(const Matrix4 &rhs)
    const
{
    return !(*this == rhs);
}

#pragma mark Element Access

/*
 * charles::basics::Matrix4::operator() --
 */
Double&
Matrix4::operator()(UInt i, UInt j)
{
    if (i >= 4 || j >= 4) {
        std::stringstream ss;
        ss << "matrix index out of bounds: i = " << i << ", j = " << j;
        throw std::out_of_range(ss.str());
    }
    return mData[i * 4 + j];
}


/*
 * charles::basics::Matrix4::operator() --
 */
Double
Matrix4::operator()(UInt i, UInt j)
    const
{
    return operator()(i, j);
}


/*
 * charles::basics::Matrix4::CArray --
 */
const Double*
Matrix4::CArray()
    const
{
    return mData;
}

#pragma mark Maths

/*
 * charles::basics::Matrix4::operator* --
 */
Matrix4
Matrix4::operator*(Double rhs)
    const
{
    return Matrix4(*this) *= rhs;
}


/*
 * charles::basics::Matrix4::operator/ --
 */
Matrix4
Matrix4::operator/(Double rhs)
    const
{
    return Matrix4(*this) /= rhs;
}


/*
 * charles::basics::Matrix4::operator*= --
 */
Matrix4&
Matrix4::operator*=(Double rhs)
{
    for (UInt i = 0; i < 16; i++) {
        mData[i] *= rhs;
    }
    return *this;
}


/*
 * charles::basics::Matrix4::operator/= --
 */
Matrix4&
Matrix4::operator/=(Double rhs)
{
    return *this *= (1.0 / rhs);
}


/*
 * charles::basics::Matrix4::operator* --
 */
Matrix4
Matrix4::operator*(const Matrix4& rhs)
    const
{
    Matrix4 result;
    for (UInt i = 0; i < 4; i++) {
        for (UInt j = 0; j < 4; j++) {
            /* Each cell is Sigma(k=0, M)(lhs[ik] * rhs[kj]) */
            result(i,j) = 0.0;
            for (UInt k = 0; k < 4; k++) {
                result(i,j) += mData[i*4 + k] * rhs(k,j);
            }
        }
    }
    return result;
}


/*
 * charles::basics::operator* --
 */
Matrix4
operator*(Double lhs,
          const Matrix4& rhs)
{
    /* Scalar multiplication is commutative. */
    return rhs * lhs;
}

} /* namespace mespace  */
} /* namespace charles */

