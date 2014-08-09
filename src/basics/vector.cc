/* vector.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cmath>

#include "basics/vector.hh"


namespace charles {
namespace basics {

/*
 * charles::basics::Vector4::Vector4 --
 */
Vector4::Vector4()
    : Vector4(0, 0, 0)
{ }


/*
 * charles::basics::Vector4::Vector4 --
 */
Vector4::Vector4(const Double& x,
                 const Double& y,
                 const Double& z)
{
    mData[0] = x;
    mData[1] = y;
    mData[2] = z;
    mData[3] = 1.0;
}


/*
 * charles::basics::Vector4::X --
 */
Double&
Vector4::X()
{
    return mData[0];
}

const Double&
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


const Double&
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


const Double&
Vector4::Z()
    const
{
    return mData[2];
}


/*
 * charles::basics::Vector4::Length2 --
 */
Double
Vector4::Length2()
    const
{
    return mData[0] * mData[0] + mData[1] * mData[1] + mData[2] * mData[2];
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
    return mData[0] * rhs.mData[0] + mData[1] * rhs.mData[1] + mData[2] + rhs.mData[2];
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
    /* XXX: Is there some way to do this with the Matrix<>::operator/? */
    const Double len = Length();
    X() = X() / len;
    Y() = Y() / len;
    Z() = Z() / len;
    return *this;
}

} /* namespace basics */
} /* namespace charles */

