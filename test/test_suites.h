/* test_suites.h
 *
 * Declarations of test suite creator functions.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __TEST_SUITES_H__
#define __TEST_SUITES_H__

#include <check.h>


Suite *test_basics_create_suite();
Suite *test_object_create_suite();


#endif
