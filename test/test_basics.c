/* test_basics.c
 *
 * Unit tests for the basics module.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include "basics.h"
#include "test_suites.h"


START_TEST(test_vector_init)
{
    Vector3 v = vector_init(1, 2, 3);
    ck_assert(v.x == 1.0);
    ck_assert(v.y == 2.0);
    ck_assert(v.z == 3.0);
}
END_TEST


START_TEST(test_vector_length2)
{
    Vector3 v = vector_init(2, 2, 1);
    ck_assert(vector_length2(v) == 9.0);
}
END_TEST


START_TEST(test_vector_length)
{
    Vector3 v = vector_init(2, 2, 1);
    ck_assert(vector_length(v) == 3.0);
}
END_TEST


START_TEST(test_vector_dot)
{
    Vector3 a = vector_init(1, 1, 1);
    Vector3 b = vector_init(1, 1, 1);
    ck_assert(vector_dot(a, b) == 3.0);

    a = vector_init(2, 3, 4);
    b = vector_init(4, 4, 4);
    ck_assert(vector_dot(a, b) == (2 * 4) + (3 * 4) + (4 * 4));
}
END_TEST


START_TEST(test_vector_normalize)
{
    Vector3 v = vector_init(1, 0, 0);
    Vector3 norm_v = vector_normalize(v);
    ck_assert(v.x == norm_v.x);
    ck_assert(v.y == norm_v.y);
    ck_assert(v.z == norm_v.z);
}
END_TEST


Suite *
test_basics_create_suite()
{
    Suite *s = suite_create("basics");

    TCase *tc_vector = tcase_create("vector");
    tcase_add_test(tc_vector, test_vector_init);
    tcase_add_test(tc_vector, test_vector_length2);
    tcase_add_test(tc_vector, test_vector_length);
    tcase_add_test(tc_vector, test_vector_dot);
    tcase_add_test(tc_vector, test_vector_normalize);
    suite_add_tcase(s, tc_vector);

    return s;
}
