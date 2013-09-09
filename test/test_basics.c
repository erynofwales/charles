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


START_TEST(test_vector_add_vector)
{
    Vector3 v, a, sum;

    v = vector_init(1, 2, 3);

    a = vector_init(4, 5, 6);
    sum = vector_add_vector(v, a);
    ck_assert(sum.x == 5);
    ck_assert(sum.y == 7);
    ck_assert(sum.z == 9);

    a = vector_init(0, 0, 0);
    sum = vector_add_vector(v, a);
    ck_assert(sum.x == v.x);
    ck_assert(sum.y == v.y);
    ck_assert(sum.z == v.z);

    a = vector_init(-3, -7, -13);
    sum = vector_add_vector(v, a);
    ck_assert(sum.x == -2);
    ck_assert(sum.y == -5);
    ck_assert(sum.z == -10);
}
END_TEST


START_TEST(test_vector_mul_scalar)
{
    Vector3 v, p;

    v = vector_init(1, 2, 3);

    p = vector_mul_scalar(v, 7);
    ck_assert(p.x == 7);
    ck_assert(p.y == 14);
    ck_assert(p.z == 21);

    p = vector_mul_scalar(v, 0);
    ck_assert(p.x == 0);
    ck_assert(p.y == 0);
    ck_assert(p.z == 0);

    p = vector_mul_scalar(v, -13);
    ck_assert(p.x == -13);
    ck_assert(p.y == -26);
    ck_assert(p.z == -39);
}
END_TEST


START_TEST(test_vector_sub_vector)
{
    Vector3 v, s, diff;

    v = vector_init(1, 2, 3);

    s = vector_init(4, 5, 6);
    diff = vector_sub_vector(v, s);
    ck_assert(diff.x == -3);
    ck_assert(diff.y == -3);
    ck_assert(diff.z == -3);
}
END_TEST


START_TEST(test_vector_negate)
{
    Vector3 v, neg;

    v = vector_init(1, 2, 3);
    neg = vector_negate(v);
    ck_assert(neg.x == -1);
    ck_assert(neg.y == -2);
    ck_assert(neg.z == -3);
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

    a = vector_init(3, 5, 7);
    b = vector_init(7, 3, 5);
    ck_assert(vector_dot(a, b) == 71.0);
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
    tcase_add_test(tc_vector, test_vector_add_vector);
    tcase_add_test(tc_vector, test_vector_mul_scalar);
    tcase_add_test(tc_vector, test_vector_sub_vector);
    tcase_add_test(tc_vector, test_vector_negate);
    tcase_add_test(tc_vector, test_vector_length2);
    tcase_add_test(tc_vector, test_vector_length);
    tcase_add_test(tc_vector, test_vector_dot);
    tcase_add_test(tc_vector, test_vector_normalize);
    suite_add_tcase(s, tc_vector);

    return s;
}
