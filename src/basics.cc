/* basics.c
 *
 * Definition of basic types.
 *
 *   - Vector3 is a three tuple vector of x, y, and z.
 *   - Ray is a vector plus a direction.
 *   - Color is a four tuple of red, green, blue, and alpha.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cassert>
#include <cmath>
#include <cstring>

#include "basics.h"

#pragma mark - Vectors

const Vector3 Vector3::Zero = Vector3();
const Vector3 Vector3::X = Vector3(1, 0, 0);
const Vector3 Vector3::Y = Vector3(0, 1, 0);
const Vector3 Vector3::Z = Vector3(0, 0, 1);


/*
 * Vector3::Vector3 --
 *
 * Default constructor. Create a zero vector.
 */
Vector3::Vector3()
    : Vector3(0.0, 0.0, 0.0)
{ }


/*
 * Vector3::Vector3 --
 *
 * Constructor. Create a vector consisting of the given coordinates.
 */
Vector3::Vector3(Double _x, Double _y, Double _z)
    : x(_x), y(_y), z(_z)
{ }


/*
 * Vector3::operator= --
 *
 * Copy the given vector's values into this vector. Return a reference to this vector.
 */
Vector3 &
Vector3::operator=(const Vector3 &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}


/*
 * Vector3::operator*= --
 * Vector3::operator/= --
 * Vector3::operator+= --
 * Vector3::operator-= --
 *
 * Perform the corresponding arithmetic operation on this vector and the given vector. These methods are destructive and
 * a reference to this vector is returned.
 */
Vector3 &
Vector3::operator*=(const Double &rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

Vector3 &
Vector3::operator/=(const Double &rhs)
{
    return *this *= (1.0f / rhs);
}

Vector3 &
Vector3::operator+=(const Vector3 &rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

Vector3 &
Vector3::operator-=(const Vector3 &rhs)
{
    return *this += -rhs;
}


/*
 * Vector3::operator* --
 * Vector3::operator/ --
 * Vector3::operator+ --
 * Vector3::operator- --
 *
 * Perform the corresponding operation on a copy of this vector. Return a new vector.
 */
Vector3
Vector3::operator*(const Double &rhs)
    const
{
    return Vector3(*this) *= rhs;
}

Vector3
Vector3::operator/(const Double &rhs)
    const
{
    return Vector3(*this) /= rhs;
}

Vector3
Vector3::operator+(const Vector3 &rhs)
    const
{
    return Vector3(*this) += rhs;
}

Vector3
Vector3::operator-(const Vector3 &rhs)
    const
{
    return Vector3(*this) -= rhs;
}


/*
 * Vector3::operator- --
 *
 * Negate this vector. Return a new vector.
 */
Vector3
Vector3::operator-()
    const
{
    return Vector3(-x, -y, -z);
}


/*
 * Vector3::operator== --
 * Vector3::operator!= --
 *
 * Compute boolean equality and non-equality of this and the given vectors.
 */
bool
Vector3::operator==(const Vector3 &rhs)
    const
{
    return x == rhs.x && y == rhs.y && z == rhs.z;
}

bool
Vector3::operator!=(const Vector3 &rhs)
    const
{
    return !(*this == rhs);
}


/*
 * Vector3::length2 --
 *
 * Compute and return the length-squared of this vector.
 */
Double
Vector3::length2()
    const
{
    return x*x + y*y + z*z;
}


/*
 * Vector3::length --
 *
 * Compute and return the length of this vector.
 */
Double
Vector3::length()
    const
{
    return sqrt(length2());
}


/*
 * Vector3::dot --
 *
 * Compute and return the dot product of this and the given vectors.
 */
Double
Vector3::dot(const Vector3 &v)
    const
{
    return x*v.x + y*v.y + z*v.z;
}


/*
 * Vector3::cross --
 *
 * Compute and return the cross product of this and the given vectors.
 */
Vector3
Vector3::cross(const Vector3 &v)
    const
{
    return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}


/*
 * Vector3::normalize --
 */
Vector3 &
Vector3::normalize()
{
    // Use the overloaded /= compound operator to do this.
    return *this /= length();
}


/*
 * Vector3::normalized --
 */
Vector3
Vector3::normalized()
    const
{
    return *this / length();
}


/*
 * operator* --
 *
 * Multiply the given float by the given vector. Return a new vector.
 */
const Vector3
operator*(const Double &lhs, const Vector3 &rhs)
{
    return rhs * lhs;
}


std::ostream &
operator<<(std::ostream &os, const Vector3 &v)
{
    // Stream the vector like this: <x, y, z>
    os << "<" << v.x << ", " << v.y << ", " << v.z << ">";
    return os;
}


Vector3
LinearCombination(const Double k1, const Vector3& v1,
                  const Double k2, const Vector3& v2,
                  const Double k3, const Vector3& v3)
{
    return Vector3(k1 * v1.x + k2 * v2.x + k3 * v3.x,
                   k1 * v1.y + k2 * v2.y + k3 * v3.y,
                   k1 * v1.z + k2 * v2.z + k3 * v3.z);
}

#pragma mark - Matrices

#if 0
/* static */ Matrix4
Matrix4::Zero()
{
    Matrix4 m;
    memset(m.mCells, 0, 16 * sizeof(Double));
    return m;
}


/* static */ Matrix4
Matrix4::Identity()
{
    Matrix4 m = Zero();
    for (int i = 0; i < 4; i++) {
        m.mCells[i * 4 + i] = 1.0;
    }
    return m;
}


/* static */ Matrix4
Matrix4::Translation(Double x,
                     Double y,
                     Double z)
{
    Matrix4 m = Identity();
    m.mCells[3] = x;
    m.mCells[7] = y;
    m.mCells[11] = z;
    return m;
}


/* static */ Matrix4
Matrix4::Rotation(Double x,
                  Double y,
                  Double z)
{
    Matrix4 m = Identity();

    if (x == 0.0 && y == 0.0 && z == 0.0) {
        /* No rotation, just return the identity matrix. */
    } else if (x != 0.0 && y == 0.0 && z == 0.0) {
        /*
         * Fill in m with values for an X rotation matrix.
         *
         *   [1     0       0  0]
         *   [0 cos(x) -sin(x) 0]
         *   [0 sin(x)  cos(x) 0]
         *   [0     0       0  1]
         */
        Double cosX = std::cos(x);
        Double sinX = std::sin(x);
        m.mCells[5] = cosX;
        m.mCells[6] = -sinX;
        m.mCells[9] = sinX;
        m.mCells[10] = cosX;
    } else if (x == 0.0 && y != 0.0 && z == 0.0) {
        /*
         * Fill in m with values for a Y rotation matrix.
         *
         *   [ cos(y) 0 sin(y) 0]
         *   [     0  1     0  0]
         *   [-sin(y) 0 cos(y) 0]
         *   [     0  0     0  1]
         */
        Double cosY = std::cos(y);
        Double sinY = std::sin(y);
        m.mCells[0] = cosY;
        m.mCells[2] = sinY;
        m.mCells[8] = -sinY;
        m.mCells[10] = cosY;
    } else if (x == 0.0 && y == 0.0 && z != 0.0) {
        /*
         * Fill in m with values for a Z rotation matrix.
         *
         *   [cos(z) -sin(z) 0 0]
         *   [sin(z)  cos(z) 0 0]
         *   [    0       0  1 0]
         *   [    0       0  0 1]
         */
        Double cosZ = std::cos(z);
        Double sinZ = std::sin(z);
        m.mCells[0] = cosZ;
        m.mCells[1] = -sinZ;
        m.mCells[4] = sinZ;
        m.mCells[5] = cosZ;
    } else {
        /*
         * TODO: Rotation in more than one dimension. So do a general rotation
         * matrix. There's some magic way to do this with matrix multiplication
         * that avoids gimbal lock. I should figure out how to do it properly.
         */
        assert(0);
    }

    return m;
}


/*
 * Matrix4::Matrix4 --
 */
Matrix4::Matrix4()
    : mCells()
{ }


/*
 * Matrix4::Matrix4 --
 */
Matrix4::Matrix4(const Double cells[16])
    : mCells()
{
    memcpy(mCells, cells, 16 * sizeof(Double));
}


/*
 * Matrix4::Matrix4 --
 */
Matrix4::Matrix4(const Matrix4& rhs)
    : Matrix4(rhs.mCells)
{ }


/*
 * Matrix4::operator() --
 */
Double&
Matrix4::operator()(const unsigned int row,
                    const unsigned int col)
{
    assert(row < 4 && col < 4);
    return mCells[4*row + col];
}


/*
 * Matrix4::operator* --
 */
Matrix4
Matrix4::operator*(const Double rhs)
    const
{
    return Matrix4(*this) *= rhs;
}


/*
 * Matrix4::operator*= --
 */
Matrix4&
Matrix4::operator*=(const Double rhs)
{
    for (int i = 0; i < 16; i++) {
        mCells[i] *= rhs;
    }
    return *this;
}


/*
 * Matrix4::operator* --
 */
Matrix4
Matrix4::operator*(const Matrix4& rhs)
    const
{
    return Matrix4(*this) *= rhs;
}


/*
 * Matrix4::operator*=
 */
Matrix4&
Matrix4::operator*=(const Matrix4& rhs)
{
    Matrix4 lhs(*this);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            /* Each cell is Sigma(k=0, 4)(lhs[ik] * rhs[kj]) */
            const int cell = i*4 + j;
            mCells[cell] = 0.0;
            for (int k = 0; k < 4; k++) {
                mCells[cell] += lhs.mCells[i*4 + k] * rhs.mCells[k*4 + j];
            }
        }
    }
    return *this;
}


/*
 * Matrix4::CArray --
 */
const Double*
Matrix4::CArray()
    const
{
    return mCells;
}


Matrix4
operator*(const Double rhs,
          const Matrix4& lhs)
{
    /* Scalar multiplication is commutative. */
    return lhs * rhs;
}
#endif

#pragma mark - Rays

/*
 * Ray::Ray --
 *
 * Default constructor. Create a ray at the origin (0, 0, 0) with direction (0, 0, 0).
 */
Ray::Ray()
    : Ray(Vector3::Zero, Vector3::Zero)
{ }


/*
 * Ray::Ray --
 *
 * Constructor. Create a ray with the given origin and direction.
 */
Ray::Ray(Vector3 o, Vector3 d)
    : origin(o), direction(d)
{ }


/*
 * Ray::parameterize --
 *
 * Compute and return the point given by parameterizing this Ray by time t.
 */
Vector3
Ray::parameterize(const Double& t)
    const
{
    return origin + t * direction;
}


std::ostream &
operator<<(std::ostream &os, const Ray &r)
{
    os << "[Ray " << r.origin << " " << r.direction << "]";
    return os;
}

#pragma mark - Colors
