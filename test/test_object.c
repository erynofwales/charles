/* test_object.c
 *
 * Unit tests for the object module.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <stdlib.h>

#include <check.h>

#include "object.h"
#include "test_suites.h"


void check_sphere_intersection(Object *sphere, Ray ray, int expected_nints);


START_TEST(test_sphere_does_intersect)
{
    // Create a sphere at the origin of radius 1.
    Object *sphere = object_init(ObjectTypeSphere);
    object_sphere_set_radius(sphere, 1.0);

    Vector3 loc, dir;
    Ray ray;

    loc = vector_init(0, 0, -5);
    dir = vector_init(0, 0, 1);
    ray = ray_init(loc, dir);
    check_sphere_intersection(sphere, ray, 2);

    loc = vector_init(0, -5, 0);
    dir = vector_init(
}
END_TEST


void
check_sphere_intersection(Object *sphere, Ray ray, int expected_nints)
{
    float *t;
    int nints = object_does_intersect(sphere, ray, &t);
    ck_assert(nints == expected_nints);
    if (nints > 0) {
        free(t);
    }
}


Suite *
test_object_create_suite()
{
    Suite *s = suite_create("object");

    TCase *tc_sphere = tcase_create("sphere");
    tcase_add_test(tc_sphere, test_sphere_does_intersect);
    suite_add_tcase(s, tc_sphere);

    return s;
}
