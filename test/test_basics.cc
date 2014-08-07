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


TEST_F(Vector3Test, OperatorDiv)
{
    Vector3 out;

    out = v1 / 5.0;
    EXPECT_FLOAT_EQ(1.0/5.0, out.x);
    EXPECT_FLOAT_EQ(3.0/5.0, out.y);
    EXPECT_FLOAT_EQ(5.0/5.0, out.z);

    out = v1 / -7.0;
    EXPECT_FLOAT_EQ(1.0/-7.0, out.x);
    EXPECT_FLOAT_EQ(3.0/-7.0, out.y);
    EXPECT_FLOAT_EQ(5.0/-7.0, out.z);

    out = v1;
    out /= 5.0;
    EXPECT_FLOAT_EQ(1.0/5.0, out.x);
    EXPECT_FLOAT_EQ(3.0/5.0, out.y);
    EXPECT_FLOAT_EQ(5.0/5.0, out.z);

    out = v1;
    out /= -7.0;
    EXPECT_FLOAT_EQ(1.0/-7.0, out.x);
    EXPECT_FLOAT_EQ(3.0/-7.0, out.y);
    EXPECT_FLOAT_EQ(5.0/-7.0, out.z);
}


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

    out = v2 - v1;
    EXPECT_EQ(6, out.x);
    EXPECT_EQ(10, out.y);
    EXPECT_EQ(12, out.z);

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


TEST_F(Vector3Test, Length)
{
    EXPECT_FLOAT_EQ(5.916079783099616, v1.length());
    EXPECT_FLOAT_EQ(22.5166604983954, v2.length());
}


TEST_F(Vector3Test, DotProduct)
{
    EXPECT_EQ(131.0, v1.dot(v2));
}

#pragma mark Matrix4 Tests

class Matrix4Test
    : public ::testing::Test
{
public:
    virtual void SetUp();

protected:
    Matrix4 m1, m2;
};


void
Matrix4Test::SetUp()
{
    const Double m1Cells[] = { 1,  2,  3,  4,
                               5,  6,  7,  8,
                               9, 10, 11, 12,
                              13, 14, 15, 16};
    m1 = Matrix4(m1Cells);

    const Double m2Cells[] = {  1,  1,    2,   3,
                                5,  8,   13,  21,
                               34,  55,  89, 144,
                              233, 377, 610, 987};
    m2 = Matrix4(m2Cells);
}


TEST(Matrix4StaticTest, Zero)
{
    Matrix4 zero = Matrix4::Zero();
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(zero.CArray()[i], 0.0);
    }
}


TEST(Matrix4StaticTest, Identity)
{
    Matrix4 id = Matrix4::Identity();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_EQ(id.CArray()[i * 4 + j], ((i == j) ? 1.0 : 0.0));
        }
    }
}


TEST_F(Matrix4Test, OperatorCall)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_EQ(m1(i, j), 4 * i + j + 1);
        }
    }
}


TEST_F(Matrix4Test, ScalarMultiplication)
{
    Matrix4 p1 = m1 * 2.0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_EQ(p1(i, j), m1(i, j) * 2.0);
        }
    }

    Matrix4 p2 = 2.0 * m1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_EQ(p2(i, j), m1(i, j) * 2.0);
        }
    }
}


TEST_F(Matrix4Test, MatrixMultiplication)
{
    const Double p1Expect[] = {1045,  1690,  2735,  4425,
                               2137,  3454,  5591,  9045,
                               3229,  5218,  8447, 13665,
                               4321,  6982, 11303, 18285};
    Matrix4 p1 = m1 * m2;
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(p1.CArray()[i], p1Expect[i]);
    }

    const Double p2Expect[] = {   63,    70,    77,    84,
                                 435,   482,   529,   576,
                                2982,  3304,  3626,  3948,
                               20439, 22646, 24853, 27060};
    Matrix4 p2 = m2 * m1;
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(p2.CArray()[i], p2Expect[i]);
    }

    /* Multiplication with the identity matrix produces the same matrix. */
    Matrix4 p3 = m1 * Matrix4::Identity();
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(p3.CArray()[i], m1.CArray()[i]);
    }
    Matrix4 p4 = Matrix4::Identity() * m1;
    for (int i = 0; i < 16; i++) {
        EXPECT_EQ(p4.CArray()[i], m1.CArray()[i]);
    }
}
