/* test_basics.c
 *
 * Unit tests for the basics module.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include "gtest/gtest.h"

#include "basics.h"


class Vector3Test
    : public ::testing::Test
{
public:
    virtual void SetUp();

protected:
    Vector3 v1, v2;
};


void
Vector3Test::SetUp()
{
    v1 = Vector3(1, 3, 5);
    v2 = Vector3(7, 13, 17);
}


TEST_F(Vector3Test, OperatorEq)
{
    v1 = v2;
    EXPECT_EQ(v2, v1);
}


TEST_F(Vector3Test, OperatorMul)
{
    Vector3 out;

    out = v1 * 5;
    EXPECT_EQ(5, out.x);
    EXPECT_EQ(15, out.y);
    EXPECT_EQ(25, out.z);

    out = v1 * -7;
    EXPECT_EQ(-7, out.x);
    EXPECT_EQ(-21, out.y);
    EXPECT_EQ(-35, out.z);

    out = v1;
    out *= 5;
    EXPECT_EQ(5, out.x);
    EXPECT_EQ(15, out.y);
    EXPECT_EQ(25, out.z);

    out = v1;
    out *= -7;
    EXPECT_EQ(-7, out.x);
    EXPECT_EQ(-21, out.y);
    EXPECT_EQ(-35, out.z);
}


// TODO: Test divison.
#if 0
TEST_F(Vector3Test, OperatorDiv)
{
    Vector3 out;

    out = v1 / 5.0;
    EXPECT_EQ(1.0/5.0, out.x);
    EXPECT_EQ(3.0/5.0, out.y);
    EXPECT_EQ(5.0/5.0, out.z);

    out = v1 / -7.0;
    EXPECT_EQ(1.0/-7.0, out.x);
    EXPECT_EQ(3.0/-7.0, out.y);
    EXPECT_EQ(5.0/-7.0, out.z);

    out = v1;
    out /= 5.0;
    EXPECT_EQ(1.0/5.0, out.x);
    EXPECT_EQ(3.0/5.0, out.y);
    EXPECT_EQ(5.0/5.0, out.z);

    out = v1;
    out /= -7.0;
    EXPECT_EQ(1.0/-7.0, out.x);
    EXPECT_EQ(3.0/-7.0, out.y);
    EXPECT_EQ(5.0/-7.0, out.z);
}
#endif


TEST_F(Vector3Test, OperatorAdd)
{
    Vector3 out;

    out = v1 + v2;
    EXPECT_EQ(8, out.x);
    EXPECT_EQ(16, out.y);
    EXPECT_EQ(22, out.z);

    out = v1;
    out += v2;
    EXPECT_EQ(8, out.x);
    EXPECT_EQ(16, out.y);
    EXPECT_EQ(22, out.z);
}


TEST_F(Vector3Test, OperatorSub)
{
    Vector3 out;

    out = v1 - v2;
    EXPECT_EQ(-6, out.x);
    EXPECT_EQ(-10, out.y);
    EXPECT_EQ(-12, out.z);

    v1 -= v2;
    EXPECT_EQ(-6, v1.x);
    EXPECT_EQ(-10, v1.y);
    EXPECT_EQ(-12, v1.z);
}


TEST_F(Vector3Test, OperatorBoolEq)
{
    EXPECT_EQ(v1, v1);
    EXPECT_EQ(v2, v2);
}


TEST_F(Vector3Test, OperatorBoolNe)
{
    EXPECT_NE(v1, v2);
    EXPECT_NE(v2, v1);
}


TEST_F(Vector3Test, Length2)
{
    EXPECT_EQ(35.0, v1.length2());
    EXPECT_EQ(507.0, v2.length2());
}


// TODO: Test length()


TEST_F(Vector3Test, DotProduct)
{
    EXPECT_EQ(131.0, v1.dot(v2));
}
