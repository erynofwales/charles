/* test_object.c
 *
 * Unit tests for the object module.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <check.h>
#include "object.h"
#include "test_suites.h"


START_TEST(test_sphere_does_intersect)
{

}
END_TEST


Suite *
test_object_create_suite()
{
    Suite *s = suite_create("object");

    TCase *tc_sphere = tcase_create("sphere");
    tcase_add_test(tc_sphere, test_sphere_does_intersect);
    suite_add_tcase(s, tc_sphere);

    return s;
}
