/* test_asserts.c
 *
 * Some helpful asserts built on Check's asserts.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <check.h>
#include "test_asserts.h"


void
test_assert_within_epsilon(float value, float expected, float epsilon)
{
    ck_assert(value >= (expected - epsilon) && value <= (expected + epsilon));
}
