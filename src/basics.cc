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


Vector3 &
Vector3::operator=(const Vector3 &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}


/*
 * Vector3::operator+ --
 *
 * Add the given vector to this vector. Return a new vector.
 */
Vector3
Vector3::operator+(Vector3 v)
    const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}


/*
 * Vector3::operator* --
 *
 * Multiply the given scalar by this vector. Return a new vector.
 */
Vector3
Vector3::operator*(float a)
    const
{
    return Vector3(a*x, a*y, a*z);
}


/*
 * Vector3::operator- --
 *
 * Subtract the given vector from this vector. Return a new vector.
 */
Vector3
Vector3::operator-(Vector3 v)
    const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
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
Vector3::dot(Vector3 v)
    const
{
    return x*v.x + y*v.y + z*v.z;
}


/*
 * Vector3::normalize --
 *
 * Normalize this vector in place. That is, make this vector's magnitude (length) 1.0.
 */
void
Vector3::normalize()
{
    float len2 = length2();
    if (len2 <= 0.0) {
        return;
    }

    // Multiplying by the inverse of the length is more efficient than dividing by the length.
    float inverse_length = 1.0 / sqrtf(len2);
    x *= inverse_length;
    y *= inverse_length;
    z *= inverse_length;
}


/*
 * operator* --
 *
 * Multiply the given float by the given vector. Return a new vector.
 */
Vector3
operator*(float a, Vector3 v)
{
    return v * a;
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
 * Constructor. Create a new Color with the given components.
 */
Color::Color(float r, float g, float b, float a)
    : red(r), green(g), blue(b), alpha(a)
{ }


Color &
Color::operator=(const Color &c)
{
    red = c.red;
    green = c.green;
    blue = c.blue;
    alpha = c.alpha;
    return *this;
}


Color &
Color::operator*=(const float f)
{
    red *= f;
    green *= f;
    blue *= f;
    return *this;
}
