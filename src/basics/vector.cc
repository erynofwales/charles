/* vector.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

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


/*
 * charles::basics::Vector4::Y --
 */
Double&
Vector4::Y()
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

} /* namespace basics */
} /* namespace charles */

