/* basics.h
 *
 * Declaration of basic types: Vector.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __BASICS_H
#define __BASICS_H

struct Vector3
{
    Vector3();
    Vector3(float x, float y, float z);

    Vector3 operator+(Vector3 v);
    Vector3 operator*(float a);
    Vector3 operator-(Vector3 v);
    Vector3 operator-();

    float length2();
    float length();
    float dot(Vector3 v);

    void normalize();

    static const Vector3 Zero;
    float x, y, z;
};

Vector3 operator*(float a, Vector3 v);


struct Ray
{
    Ray();
    Ray(Vector3 o, Vector3 d);

    Vector3 parameterize(float t);

    Vector3 origin, direction;
};


struct Color
{
    Color();
    Color(float r, float g, float b, float a);

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;

    float red, green, blue, alpha;
};

#endif
