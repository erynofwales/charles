/* matrix.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cstring>
#include <stdexcept>
#include <sstream>
#include <type_traits>

#include "basics/matrix.hh"

#include "basics/util.hh"
#include "basics/vector.hh"


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
 * charles::basics::Translation --
 */
/* static */ Matrix4
Matrix4::Translation(const Vector4& p)
{
    return Translation(p.X(), p.Y(), p.Z());
}


/*
 * charles::basics::TranslationMatrix --
 */
/* static */ Matrix4
Matrix4::Translation(Double x,
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
    : mData(),
      mTransposed(false)
{ }


/*
 * charles::basics::Matrix4::Matrix4 --
 */
Matrix4::Matrix4(const Double data[16])
    : mTransposed(false)
{
    memcpy(mData, data, sizeof(Double) * 16);
}


/*
 * charles::basics::Matrix4::Matrix4 --
 */
Matrix4::Matrix4(const Matrix4 &rhs)
    : Matrix4(rhs.mData)
{
    /*
     * Needs to be in the body instead of the initializer list because
     * (apparently) delegating constructors must be the only thing in the list.
     */
    mTransposed = rhs.mTransposed;
}


/*
 * charles::basics::Matrix4::operator= --
 */
Matrix4&
Matrix4::operator=(const Matrix4 &rhs)
{
    memcpy(mData, rhs.mData, sizeof(Double) * 16);
    mTransposed = rhs.mTransposed;
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
Matrix4::operator()(UInt i,
                    UInt j)
{
    if (i >= 4 || j >= 4) {
        std::stringstream ss;
        ss << "matrix index out of bounds: i = " << i << ", j = " << j;
        throw std::out_of_range(ss.str());
    }

    if (!mTransposed) {
        return mData[i*4 + j];
    } else {
        return mData[i + j*4];
    }
}


/*
 * charles::basics::Matrix4::operator() --
 */
Double
Matrix4::operator()(UInt i,
                    UInt j)
    const
{
    if (i >= 4 || j >= 4) {
        std::stringstream ss;
        ss << "matrix index out of bounds: i = " << i << ", j = " << j;
        throw std::out_of_range(ss.str());
    }
    if (!mTransposed) {
        return mData[i*4 + j];
    } else {
        return mData[i + j*4];
    }
}


Vector4
Matrix4::Column(const UInt i)
    const noexcept
{
    return Vector4(operator()(i,0), operator()(i,1), operator()(i,2), operator()(i,3));
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
 * charles::basics::Matrix4::operator* --
 */
Vector4
Matrix4::operator*(const Vector4 &rhs)
    const
{
    Vector4 result;
    for (UInt i = 0; i < 4; i++) {
        result(i) = 0.0;
        for (UInt k = 0; k < 4; k++) {
            result(i) += mData[i*4 + k] * rhs(k);
        }
    }
    return result;
}


/*
 * charles::basics::Matrix4::Transpose --
 */
Matrix4&
Matrix4::Transpose()
{
    mTransposed = !mTransposed;
    return *this;
}


Matrix4&
Matrix4::Inverse()
{
    /* XXX: Only translation matrices are supported right now. */
    operator()(0,3) = -operator()(0,3);
    operator()(1,3) = -operator()(1,3);
    operator()(2,3) = -operator()(2,3);
    return *this;
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


/*
 * charles::basics::Transposed --
 */
Matrix4
Transpose(Matrix4 m)
{
    return m.Transpose();
}


/*
 * charles::basics::Inverse --
 */
Matrix4
Inverse(Matrix4 m)
{
    return m.Inverse();
}


/*
 * charles::basics::operator<< --
 */
std::ostream&
operator<<(std::ostream &ost,
           const Matrix4 &m)
{
    ost << "[";
    for (UInt i = 0; i < 4; i++) {
        if (i != 0) {
            ost << " ";
        }
        ost << "[";
        for (UInt j = 0; j < 4; j++) {
            ost << m(i,j);
            if (j < 3) {
                ost << " ";
            }
        }
        ost << "]";
        if (i < 3) {
            ost << "\n";
        }
    }
    ost << "]";
    return ost;
}


} /* namespace mespace  */
} /* namespace charles */

