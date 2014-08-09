/* vector.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "basics/vector.hh"


namespace charles {
namespace basics {

Vector4::Vector4()
    : mCells({0.0, 0.0, 0.0, 1.0})
{

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

