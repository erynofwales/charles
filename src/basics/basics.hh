/* basics.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * Top-level include for the basics module.
 */

#ifndef __BASICS_BASICS_HH__
#define __BASICS_BASICS_HH__

#include <cmath>

#include "basics/color.hh"
#include "basics/matrix.hh"
#include "basics/ray.hh"
#include "basics/types.hh"
#include "basics/util.hh"
#include "basics/vector.hh"

inline bool
TooFar(const Double& value)
{
    return value > MAX_DISTANCE;
}

#endif /* __BASICS_BASICS_HH__ */
