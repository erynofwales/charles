/* test_object.c
 *
 * Unit tests for the object module.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <stdlib.h>

#include <check.h>

#include "object.h"
#include "test_asserts.h"
#include "test_suites.h"


void check_sphere_intersection(Object *sphere, Ray ray, Vector3 *tvectors, int ntvectors);


START_TEST(test_sphere_does_intersect)
{
    // Create a sphere at the origin of radius 1.
    Object *sphere = object_init(ObjectTypeSphere);
    object_sphere_set_radius(sphere, 1.0);

    Vector3 loc, dir;
    Vector3 tvectors[2];
    Ray ray;

    loc = vector_init(0, 0, -5);
    dir = vector_init(0, 0, 1);
    ray = ray_init(loc, dir);
    tvectors[0] = vector_init(0, 0, -1);
    tvectors[1] = vector_init(0, 0, 1);
    check_sphere_intersection(sphere, ray, tvectors, 2);

    loc = vector_init(0, -5, 0);
    dir = vector_init(0, 1, 0);
    tvectors[0] = vector_init(0, -1, 0);
    tvectors[1] = vector_init(0, 1, 0);
    check_sphere_intersection(sphere, ray, tvectors, 2);
}
END_TEST


void
check_sphere_intersection(Object *sphere, Ray ray, Vector3 *tvectors, int ntvectors)
{
    float *t;
    int nints = object_does_intersect(sphere, ray, &t);
    ck_assert(nints == ntvectors);

    Vector3 rp;
    for (int i = 0; i < nints; i++) {
        rp = ray_parameterize(ray, t[i]);
        test_assert_within_epsilon(rp.x, tvectors[i].x, 1e-4);
        test_assert_within_epsilon(rp.y, tvectors[i].y, 1e-4);
        test_assert_within_epsilon(rp.z, tvectors[i].z, 1e-4);
    }

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
