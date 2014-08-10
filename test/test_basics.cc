/* test_basics.c
 *
 * Unit tests for the basics module.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include "gtest/gtest.h"

#include "basics/basics.hh"


using charles::basics::Vector4;
using charles::basics::Matrix4;


class Vector4Test
    : public ::testing::Test
{
public:
    virtual void SetUp();

protected:
    Vector4 v1, v2;
};


void
Vector4Test::SetUp()
{
    v1 = Vector4(1, 3, 5);
    v2 = Vector4(7, 13, 17);
}


TEST_F(Vector4Test, OperatorEq)
{
    v1 = v2;
    EXPECT_EQ(v2, v1);
}


TEST_F(Vector4Test, OperatorMul)
{
    Vector4 out;

    out = v1 * 5;
    EXPECT_EQ(5, out.X());
    EXPECT_EQ(15, out.Y());
    EXPECT_EQ(25, out.Z());

    out = v1 * -7;
    EXPECT_EQ(-7, out.X());
    EXPECT_EQ(-21, out.Y());
    EXPECT_EQ(-35, out.Z());

    out = v1;
    out *= 5;
    EXPECT_EQ(5, out.X());
    EXPECT_EQ(15, out.Y());
    EXPECT_EQ(25, out.Z());

    out = v1;
    out *= -7;
    EXPECT_EQ(-7, out.X());
    EXPECT_EQ(-21, out.Y());
    EXPECT_EQ(-35, out.Z());
}


TEST_F(Vector4Test, OperatorDiv)
{
    Vector4 out;

    out = v1 / 5.0;
    EXPECT_FLOAT_EQ(1.0/5.0, out.X());
    EXPECT_FLOAT_EQ(3.0/5.0, out.Y());
    EXPECT_FLOAT_EQ(5.0/5.0, out.Z());

    out = v1 / -7.0;
    EXPECT_FLOAT_EQ(1.0/-7.0, out.X());
    EXPECT_FLOAT_EQ(3.0/-7.0, out.Y());
    EXPECT_FLOAT_EQ(5.0/-7.0, out.Z());

    out = v1;
    out /= 5.0;
    EXPECT_FLOAT_EQ(1.0/5.0, out.X());
    EXPECT_FLOAT_EQ(3.0/5.0, out.Y());
    EXPECT_FLOAT_EQ(5.0/5.0, out.Z());

    out = v1;
    out /= -7.0;
    EXPECT_FLOAT_EQ(1.0/-7.0, out.X());
    EXPECT_FLOAT_EQ(3.0/-7.0, out.Y());
    EXPECT_FLOAT_EQ(5.0/-7.0, out.Z());
}


TEST_F(Vector4Test, OperatorAdd)
{
    Vector4 out;

    out = v1 + v2;
    EXPECT_EQ(8, out.X());
    EXPECT_EQ(16, out.Y());
    EXPECT_EQ(22, out.Z());

    out = v1;
    out += v2;
    EXPECT_EQ(8, out.X());
    EXPECT_EQ(16, out.Y());
    EXPECT_EQ(22, out.Z());
}


TEST_F(Vector4Test, OperatorSub)
{
    Vector4 out;

    out = v1 - v2;
    EXPECT_EQ(-6, out.X());
    EXPECT_EQ(-10, out.Y());
    EXPECT_EQ(-12, out.Z());

    out = v2 - v1;
    EXPECT_EQ(6, out.X());
    EXPECT_EQ(10, out.Y());
    EXPECT_EQ(12, out.Z());

    v1 -= v2;
    EXPECT_EQ(-6, v1.X());
    EXPECT_EQ(-10, v1.Y());
    EXPECT_EQ(-12, v1.Z());
}


TEST_F(Vector4Test, OperatorBoolEq)
{
    EXPECT_EQ(v1, v1);
    EXPECT_EQ(v2, v2);
}


TEST_F(Vector4Test, OperatorBoolNe)
{
    EXPECT_NE(v1, v2);
    EXPECT_NE(v2, v1);
}


TEST_F(Vector4Test, Length2)
{
    EXPECT_EQ(35.0, v1.Length2());
    EXPECT_EQ(507.0, v2.Length2());
}


TEST_F(Vector4Test, Length)
{
    EXPECT_FLOAT_EQ(5.916079783099616, v1.Length());
    EXPECT_FLOAT_EQ(22.5166604983954, v2.Length());
}


TEST_F(Vector4Test, DotProduct)
{
    EXPECT_EQ(131.0, v1.Dot(v2));
}

#pragma mark Matrix4 Tests

class Matrix4Test
    : public ::testing::Test
{
public:
    virtual void SetUp();

protected:
    Matrix4 m1, m2;
    Matrix4 id;
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

    id = Matrix4::Identity();
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


TEST_F(Matrix4Test, MatrixMatrixMultiplication)
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
}


TEST_F(Matrix4Test, MatrixIdentityMultiplication)
{
    Matrix4 p1 = m1 * id;
    for (UInt i = 0; i < 16; i++) {
        EXPECT_EQ(p1.CArray()[i], m1.CArray()[i]);
    }

    Matrix4 p2 = id * m1;
    for (UInt i = 0; i < 16; i++) {
        EXPECT_EQ(p2.CArray()[i], m1.CArray()[i]);
    }
}


TEST_F(Matrix4Test, IdentityVectorMultiplication)
{
    Vector4 v1(1, 2, 3);

    Vector4 p1 = id * v1;
    EXPECT_EQ(p1.X(), v1.X());
    EXPECT_EQ(p1.Y(), v1.Y());
    EXPECT_EQ(p1.Z(), v1.Z());
}


TEST_F(Matrix4Test, Transpose)
{
    Matrix4 t1 = Transposed(m1);
    for (UInt i = 0; i < 4; i++) {
        for (UInt j = 0; j < 4; j++) {
            EXPECT_EQ(m1(i,j), t1(j,i));
        }
    }

    t1.Transpose();
    for (UInt i = 0; i < 4; i++) {
        for (UInt j = 0; j < 4; j++) {
            EXPECT_EQ(m1(i,j), t1(i,j));
        }
    }
}
