/* basics.h
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __BASICS_H__
#define __BASICS_H__

#include <cmath>
#include <iostream>

#include "types.hh"

/*
 * XXX: THIS SHOULD NOT BE HERE. REMOVE IT WHEN MOVING TO CHARLES NAMESPACE IS
 * DONE.
 */
using charles::Double;


/**
 * A very small constant. If a value is between EPSILON and 0.0, it is
 * considered to be zero.
 */
const Double EPSILON = 1.0e-10;

/**
 * The maximum distance a ray can travel. This is the maximum value t can be.
 */
const Double MAX_DISTANCE = 1.0e7;


/**
 * Determine if the value is "close enough" to zero. Takes the absolute value
 * and compares it to `EPSILON`.
 *
 * @see EPSILON
 *
 * @param [in] value    The value to check
 * @returns `true` if the value is close enough to zero
 */
template <typename T>
inline bool
NearZero(const T value)
{
    return std::fabs(value) < EPSILON;
}


/**
 * Determine if two values are "close enough" to be considered equal. Subtracts
 * one from the other and checks if the result is near zero.
 *
 * @see NearZero
 *
 * @param [in] left     The left parameter
 * @param [in] right    The right parameter
 * @returns `true` if the values are close enough to be equal
 */
template <typename T>
inline bool
NearlyEqual(const T left,
            const T right)
{
    return NearZero(left - right);
}


inline bool
TooFar(const Double& value)
{
    return value > MAX_DISTANCE;
}


struct Vector3
{
    Vector3();
    Vector3(Double x, Double y, Double z);

    Vector3 &operator=(const Vector3 &v);
    Vector3 &operator*=(const Double &rhs);
    Vector3 &operator/=(const Double &rhs);
    Vector3 &operator+=(const Vector3 &rhs);
    Vector3 &operator-=(const Vector3 &rhs);
    Vector3 operator*(const Double &rhs) const;
    Vector3 operator/(const Double &rhs) const;
    Vector3 operator+(const Vector3 &rhs) const;
    Vector3 operator-(const Vector3 &rhs) const;
    Vector3 operator-() const;

    bool operator==(const Vector3 &rhs) const;
    bool operator!=(const Vector3 &rhs) const;

    Double length2() const;
    Double length() const;
    Double dot(const Vector3 &v) const;
    Vector3 cross(const Vector3 &v) const;

    /** Normalize and return a reference to this vector. */
    Vector3 &normalize();

    /** Return a copy of this vector, normalized. Does not modify this vector. */
    Vector3 normalized() const;

    static const Vector3 Zero;
    // Unit vectors in each of the three cartesian directions.
    static const Vector3 X, Y, Z;

    Double x, y, z;
};

const Vector3 operator*(const Double &lhs, const Vector3 &rhs);
std::ostream &operator<<(std::ostream &os, const Vector3 &v);


Vector3 LinearCombination(const Double k1, const Vector3& v1,
                          const Double k2, const Vector3& v2,
                          const Double k3, const Vector3& v3);


#if 0
struct Matrix4
{
    /** Create a 4x4 zero matrix. That is, all cells are 0. */
    static Matrix4 Zero();

    /** Create a 4x4 identity matrix. */
    static Matrix4 Identity();

    Matrix4();
    Matrix4(const Double cells[16]);
    Matrix4(const Matrix4& rhs);

    /**
     * Create a 4x4 translation matrix. A translation matrix looks like this:
     *
     *     [1 0 0 x]
     *     [0 1 0 y]
     *     [0 0 1 z]
     *     [0 0 0 1]
     *
     * @param [in] x    X translation
     * @param [in] y    Y translation
     * @param [in] z    Z translation
     * @returns The translation matrix
     */
    static Matrix4 Translation(Double x, Double y, Double z);

    /**
     * Create a 4x4 rotation matrix. A rotation matrices are quite complicated.
     *
     * @param [in] x    X rotation angle in radians
     * @param [in] y    Y rotation angle in radians
     * @param [in] z    Z rotation angle in radians
     * @returns The rotation matrix
     */
    static Matrix4 Rotation(Double x, Double y, Double z);

    /**
     * Get the value of the cell at (row, col).
     *
     * @param [in] row  The row, must be less than the matrix's width
     * @param [in] col  The column, must be less than the matrix's height
     * @returns The value of the cell at (row, col)
     */
    Double& operator()(const unsigned int row, const unsigned int col);

    /**
     * Scalar multiplication.
     *
     * @param [in] rhs  The scalar factor
     * @returns A copy of this matrix, multiplied by the scalar
     */
    Matrix4 operator*(const Double rhs) const;

    /**
     * Scalar multiplication. Multiplies this matrix by the given factor.
     *
     * @param [in] rhs  The scalar factor
     * @returns *this
     */
    Matrix4& operator*=(const Double rhs);

    Matrix4 operator*(const Matrix4& rhs) const;
    Matrix4& operator*=(const Matrix4& rhs);

    const Double* CArray() const;

private:
    Double mCells[16];
};


Matrix4 operator*(const Double lhs, const Matrix4& rhs);
#endif


struct Ray
{
    Ray();
    Ray(Vector3 o, Vector3 d);

    Vector3 parameterize(const Double& t) const;

    Vector3 origin, direction;
};

std::ostream &operator<<(std::ostream &os, const Ray &r);


struct Color
{
    Color();
    Color(const float &r, const float &g, const float &b);
    Color(const float &r, const float &g, const float &b, const float &a);

    Color &operator*=(const float &rhs);
    Color &operator/=(const float &rhs);
    Color &operator+=(const float &rhs);
    Color &operator-=(const float &rhs);
    Color operator*(const float &rhs) const;
    Color operator/(const float &rhs) const;
    Color operator+(const float &rhs) const;
    Color operator-(const float &rhs) const;

    Color &operator=(const Color &rhs);

    // These operators blend the two colors.
    Color &operator*=(const Color &rhs);
    Color &operator/=(const Color &rhs);
    Color &operator+=(const Color &rhs);
    Color &operator-=(const Color &rhs);
    Color operator*(const Color &rhs) const;
    Color operator/(const Color &rhs) const;
    Color operator+(const Color &rhs) const;
    Color operator-(const Color &rhs) const;

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;

    float red, green, blue, alpha;
};

const Color operator*(const float &lhs, const Color &rhs);
std::ostream &operator<<(std::ostream &os, const Color &c);

#endif
