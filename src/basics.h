/* basics.h
 *
 * Declaration of basic types.
 *
 *   - Vector3 is a three tuple vector of x, y, and z.
 *   - Ray is a vector plus a direction.
 *   - Color is a four tuple of red, green, blue, and alpha.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __BASICS_H__
#define __BASICS_H__

struct Vector3
{
    Vector3();
    Vector3(float x, float y, float z);

    Vector3 &operator=(const Vector3 &v);
    Vector3 &operator*=(const float &rhs);
    Vector3 &operator/=(const float &rhs);
    Vector3 &operator+=(const Vector3 &rhs);
    Vector3 &operator-=(const Vector3 &rhs);
    Vector3 operator*(const float &rhs) const;
    Vector3 operator/(const float &rhs) const;
    Vector3 operator+(const Vector3 &rhs) const;
    Vector3 operator-(const Vector3 &rhs) const;
    Vector3 operator-() const;

    float length2() const;
    float length() const;
    float dot(const Vector3 &v) const;

    Vector3 &normalize();

    static const Vector3 Zero;
    float x, y, z;
};

const Vector3 operator*(const float &lhs, const Vector3 &rhs);


struct Ray
{
    Ray();
    Ray(Vector3 o, Vector3 d);

    Vector3 parameterize(const float t) const;

    Vector3 origin, direction;
};


struct Color
{
    Color();
    Color(float r, float g, float b, float a);

    Color &operator*=(const float &rhs);
    Color &operator/=(const float &rhs);
    Color &operator+=(const float &rhs);
    Color &operator-=(const float &rhs);
    Color operator*(const float &rhs) const;
    Color operator/(const float &rhs) const;
    Color operator+(const float &rhs) const;
    Color operator-(const float &rhs) const;

    Color &operator=(const Color &rhs);

    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;

    float red, green, blue, alpha;
};

#endif
