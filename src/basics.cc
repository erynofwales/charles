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

#include <cmath>
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
Vector3::Vector3(float _x, float _y, float _z)
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
Vector3::operator*=(const float &rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

Vector3 &
Vector3::operator/=(const float &rhs)
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
Vector3::operator*(const float &rhs)
    const
{
    return Vector3(*this) *= rhs;
}

Vector3
Vector3::operator/(const float &rhs)
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
float
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
float
Vector3::length()
    const
{
    return sqrtf(length2());
}


/*
 * Vector3::dot --
 *
 * Compute and return the dot product of this and the given vectors.
 */
float
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
 *
 * Normalize this vector in place. That is, make this vector's magnitude (length) 1.0.
 */
Vector3 &
Vector3::normalize()
{
    // Use the overloaded /= compound operator to do this.
    return *this /= length();
}


/*
 * operator* --
 *
 * Multiply the given float by the given vector. Return a new vector.
 */
const Vector3
operator*(const float &lhs, const Vector3 &rhs)
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
Ray::parameterize(const float t)
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

const Color Color::Black  = Color();
const Color Color::White  = Color(1.0, 1.0, 1.0, 1.0);
const Color Color::Red    = Color(1.0, 0.0, 0.0, 1.0);
const Color Color::Green  = Color(0.0, 1.0, 0.0, 1.0);
const Color Color::Blue   = Color(0.0, 0.0, 1.0, 1.0);


/*
 * Color::Color --
 *
 * Default constructor. Create a new Color with zeros for all components (black).
 */
Color::Color()
    : Color(0.0, 0.0, 0.0, 0.0)
{ }


/*
 * Color::Color --
 *
 * Constructor. Create a new Color with the given RGB components. Alpha is 1.0.
 */
Color::Color(const float &r, const float &g, const float &b)
    : Color(r, g, b, 1.0)
{ }


/*
 * Color::Color --
 *
 * Constructor. Create a new Color with the given components.
 */
Color::Color(const float &r, const float &g, const float &b, const float &a)
    : red(r), green(g), blue(b), alpha(a)
{ }


/*
 * Color::operator*= --
 * Color::operator/= --
 * Color::operator+= --
 * Color::operator-= --
 *
 * Perform the corresponding arithmetic operation on this color and the given scalar. These methods are destructive and
 * a reference to this color is returned.
 */
Color &
Color::operator*=(const float &rhs)
{
    red *= rhs;
    green *= rhs;
    blue *= rhs;
    return *this;
}

Color &
Color::operator/=(const float &rhs)
{
    return *this *= (1.0 / rhs);
}

Color &
Color::operator+=(const float &rhs)
{
    red += rhs;
    green += rhs;
    blue += rhs;
    alpha += rhs;
    return *this;
}

Color &
Color::operator-=(const float &rhs)
{
    return *this += -rhs;
}


/*
 * Color::operator* --
 * Color::operator/ --
 * Color::operator+ --
 * Color::operator- --
 *
 * Perform the corresponding operation on a copy of this color and the given scalar. Return a new vector.
 */
Color
Color::operator*(const float &rhs)
    const
{
    return Color(*this) *= rhs;
}

Color
Color::operator/(const float &rhs)
    const
{
    return Color(*this) /= rhs;
}

Color
Color::operator+(const float &rhs)
    const
{
    return Color(*this) += rhs;
}

Color
Color::operator-(const float &rhs)
    const
{
    return Color(*this) -= rhs;
}


/*
 * Color::operator= --
 *
 * Copy the given color's values into this color. Return a reference to this color.
 */
Color &
Color::operator=(const Color &rhs)
{
    red = rhs.red;
    green = rhs.green;
    blue = rhs.blue;
    alpha = rhs.alpha;
    return *this;
}


Color &
Color::operator*=(const Color &rhs)
{
    red *= rhs.red;
    green *= rhs.green;
    blue *= rhs.blue;
    return *this;
}

Color &
Color::operator/=(const Color &rhs)
{
    red *= (1.0 / rhs.red);
    green *= (1.0 / rhs.green);
    blue *= (1.0 / rhs.blue);
    return *this;
}

Color &
Color::operator+=(const Color &rhs)
{
    red += rhs.red;
    green += rhs.green;
    blue += rhs.blue;
    alpha += rhs.alpha;
    return *this;
}

Color &
Color::operator-=(const Color &rhs)
{
    red -= rhs.red;
    green -= rhs.green;
    blue -= rhs.blue;
    alpha -= rhs.alpha;
    return *this;
}


Color
Color::operator*(const Color &rhs)
    const
{
    return Color(*this) *= rhs;
}

Color
Color::operator/(const Color &rhs)
    const
{
    return Color(*this) /= rhs;
}

Color
Color::operator+(const Color &rhs)
    const
{
    return Color(*this) += rhs;
}

Color
Color::operator-(const Color &rhs)
    const
{
    return Color(*this) -= rhs;
}


const Color
operator*(const float &lhs, const Color &rhs)
{
    return rhs * lhs;
}


std::ostream &
operator<<(std::ostream &os, const Color &c)
{
    // Stream colors like this: <r, g, b, a>
    os << "<" << c.red << ", " << c.green << ", " << c.blue << ", " << c.alpha << ">";
    return os;
}
