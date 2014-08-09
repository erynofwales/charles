/* basics.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * Top-level include for the basics module.
 */

#ifndef __BASICS_BASICS_HH__
#define __BASICS_BASICS_HH__

#include "basics/matrix.hh"
#include "basics/types.hh"
#include "basics/vector.hh"


/**
 * A very small constant. If a value is between EPSILON and 0.0, it is
 * considered to be zero.
 */
const Double EPSILON = 1.0e-10;

/**
 * The maximum distance a ray can travel. This is the maximum value t can be.
 */
const Double MAX_DISTANCE = 1.0e7;


#endif /* __BASICS_BASICS_HH__ */
