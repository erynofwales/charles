/* util.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __BASICS_UTIL_HH__
#define __BASICS_UTIL_HH__

#include <cmath>


/**
 * A very small constant. If a value is between EPSILON and 0.0, it is
 * considered to be zero.
 */
const Double EPSILON = 1.0e-10;


/**
 * The maximum distance a ray can travel. This is the maximum value t can be.
 */
const Double MAX_DISTANCE = 1.0e7;


/**
 * Determine if the value is "close enough" to zero. Takes the absolute value
 * and compares it to `EPSILON`.
 *
 * @see EPSILON
 *
 * @param [in] value    The value to check
 * @returns `true` if the value is close enough to zero
 */
template <typename T>
inline bool
NearZero(T value)
{
    return std::fabs(value) < EPSILON;
}


/**
 * Determine if two values are "close enough" to be considered equal. Subtracts
 * one from the other and checks if the result is near zero.
 *
 * @see NearZero
 *
 * @param [in] left     The left parameter
 * @param [in] right    The right parameter
 * @returns `true` if the values are close enough to be equal
 */
template <typename T, typename U>
inline bool
NearlyEqual(T left,
            U right)
{
    return NearZero(left - right);
}


inline bool
TooFar(const Double& value)
{
    return value > MAX_DISTANCE;
}

#endif /* __BASICS_UTIL_HH__ */

