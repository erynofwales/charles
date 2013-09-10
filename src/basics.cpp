/* basics.c
 *
 * Definition of basic types: Vector.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cmath>
#include "basics.h"


#pragma mark - Vectors

const Vector3 Vector3::Zero = Vector3();


Vector3::Vector3()
    : Vector3(0.0, 0.0, 0.0)
{ }


Vector3::Vector3(float _x, float _y, float _z)
    : x(_x), y(_y), z(_z)
{ }


inline Vector3
Vector3::operator+(Vector3 v)
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}


inline Vector3
Vector3::operator*(float a)
{
    return Vector3(a*x, a*y, a*z);
}


inline Vector3
Vector3::operator-(Vector3 v)
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}


inline Vector3
Vector3::operator-()
{
    return Vector3(-x, -y, -z);
}


inline float
Vector3::length2()
{
    return x*x + y*y + z*z;
}


inline float
Vector3::length()
{
    return sqrtf(length2());
}


inline float
Vector3::dot(Vector3 v)
{
    return x*v.x + y*v.x + z*v.z;
}


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


Vector3
operator*(float a, Vector3 v)
{
    return v * a;
}


#pragma mark - Rays

Ray::Ray()
    : Ray(Vector3::Zero, Vector3::Zero)
{ }


Ray::Ray(Vector3 o, Vector3 d)
    : origin(o), direction(d)
{ }


Vector3
Ray::parameterize(float t)
{
    return origin + t * direction;
}

#pragma mark - Colors

const Color Color::Black  = Color();
const Color Color::White  = Color(1.0, 1.0, 1.0, 1.0);
const Color Color::Red    = Color(1.0, 0.0, 0.0, 1.0);
const Color Color::Green  = Color(0.0, 1.0, 0.0, 1.0);
const Color Color::Blue   = Color(0.0, 0.0, 1.0, 1.0);


Color::Color()
    : Color(0.0, 0.0, 0.0, 0.0)
{ }


Color::Color(float r, float g, float b, float a)
    : red(r), green(g), blue(b), alpha(a)
{ }
