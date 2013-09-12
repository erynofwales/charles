/* test_basics.c
 *
 * Unit tests for the basics module.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include "gtest/gtest.h"

#include "basics.h"


TEST(Vector3Test, OperatorAdd)
{
    Vector3 v1(3, 2, 1), v2(4, 5, 6);
    Vector3 sum = v1 + v2;
    EXPECT_EQ(7, sum.x);
    EXPECT_EQ(7, sum.y);
    EXPECT_EQ(7, sum.z);
}
