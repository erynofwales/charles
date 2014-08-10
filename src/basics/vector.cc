/* vector.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cmath>
#include <cstring>

#include "basics/vector.hh"


namespace charles {
namespace basics {

/*
 * charles::basics::Vector4::Vector4 --
 */
Vector4::Vector4()
{
    bzero(mData, sizeof(Double) * 4);
}


/*
 * charles::basics::Vector4::Vector4 --
 */
Vector4::Vector4(Double x,
                 Double y,
                 Double z)
{
    mData[0] = x;
    mData[1] = y;
    mData[2] = z;
    mData[3] = 1.0;
}

#pragma mark Component Access

/*
 * charles::basics::Vector4::X --
 */
Double&
Vector4::X()
{
    return mData[0];
}


/*
 * charles::basics::Vector4::X --
 */
Double
Vector4::X()
    const
{
    return mData[0];
}


/*
 * charles::basics::Vector4::Y --
 */
Double&
Vector4::Y()
{
    return mData[1];
}


/*
 * charles::basics::Vector4::Y --
 */
Double
Vector4::Y()
    const
{
    return mData[1];
}


/*
 * charles::basics::Vector4::Z --
 */
Double&
Vector4::Z()
{
    return mData[2];
}


/*
 * charles::basics::Vector4::Z --
 */
Double
Vector4::Z()
    const
{
    return mData[2];
}

#pragma mark Maths

/*
 * charles::basics::Vector4::operator* --
 */
Vector4
Vector4::operator*(Double rhs)
    const
{
    return Vector4(*this) *= rhs;
}


/*
 * charles::basics::Vector4::operator* --
 */
Vector4
Vector4::operator/(Double rhs)
    const
{
    return Vector4(*this) /= rhs;
}


/*
 * charles::basics::Vector4::operator*= --
 */
Vector4&
Vector4::operator*=(Double rhs)
{
    for (int i = 0; i < 4; i++) {
        mData[i] *= rhs;
    }
    return *this;
}


/*
 * charles::basics::Vector4::operator/= --
 */
Vector4&
Vector4::operator/=(Double rhs)
{
    return *this *= (1.0 / rhs);
}


/*
 * charles::basics::Vector4::operator+ --
 */
Vector4
Vector4::operator+(const Vector4 &rhs)
    const
{
    return Vector4(*this) += rhs;
}


/*
 * charles::basics::Vector4::operator- --
 */
Vector4
Vector4::operator-(const Vector4 &rhs)
    const
{
    return Vector4(*this) -= rhs;
}


/*
 * charles::basics::Vector4::operator+= --
 */
Vector4&
Vector4::operator+=(const Vector4 &rhs)
{
    mData[0] += rhs.mData[0];
    mData[1] += rhs.mData[1];
    mData[2] += rhs.mData[2];
    return *this;
}


/*
 * charles::basics::Vector4::operator-= --
 */
Vector4&
Vector4::operator-=(const Vector4 &rhs)
{
    return *this += -rhs;
}


/*
 * charles::basics::Vector4::operator- --
 */
Vector4
Vector4::operator-()
    const
{
    return Vector4(-X(), -Y(), -Z());
}


/*
 * charles::basics::Vector4::Length2 --
 */
Double
Vector4::Length2()
    const
{
    return X()*X() + Y()*Y() + Z()*Z();
}


/*
 * charles::basics::Vector4::Length --
 */
Double
Vector4::Length()
    const
{
    return std::sqrt(Length2());
}


/*
 * charles::basics::Vector4::Dot --
 */
Double
Vector4::Dot(const Vector4& rhs)
    const
{
    return X()*rhs.X() + Y()*rhs.Y() + Z()*rhs.Z();
}


/*
 * charles::basics::Vector4::Cross --
 */
Vector4
Vector4::Cross(const Vector4& rhs)
    const
{
    return Vector4(mData[1]*rhs.mData[2] - mData[2]*rhs.mData[1],
                   mData[2]*rhs.mData[0] - mData[0]*rhs.mData[2],
                   mData[0]*rhs.mData[1] - mData[1]*rhs.mData[0]);
}


/*
 * charles::basics::Vector4::Normalize --
 */
Vector4&
Vector4::Normalize()
{
    return *this /= Length();
}


/*
 * charles::basics::operator* --
 */
Vector4
operator*(Double lhs,
          const Vector4& rhs)
{
    return rhs * lhs;
}


/*
 * charles::basics::Normalized --
 */
Vector4
Normalized(Vector4 v)
{
    return v.Normalize();
}


/*
 * charles::basics::LinearCombination --
 */
Vector4
LinearCombination(const Double k1, const Vector4& v1,
                  const Double k2, const Vector4& v2,
                  const Double k3, const Vector4& v3)
{
    return Vector4(k1 * v1.X() + k2 * v2.X() + k3 * v3.X(),
                   k1 * v1.Y() + k2 * v2.Y() + k3 * v3.Y(),
                   k1 * v1.Z() + k2 * v2.Z() + k3 * v3.Z());
}


/*
 * charles::basics::operator<< --
 */
std::ostream&
operator<<(std::ostream& os, const Vector4& v)
{
    // Stream the vector like this: <x, y, z>
    os << "<" << v.X() << ", " << v.Y() << ", " << v.Z() << ">";
    return os;
}

} /* namespace basics */
} /* namespace charles */

