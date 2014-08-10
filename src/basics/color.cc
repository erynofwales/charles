/* color.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <ostream>

#include "basics/color.hh"

#include "basics/types.hh"


namespace charles {
namespace basics {

const Color Color::Black = Color();
const Color Color::White = Color(1, 1, 1);
const Color Color::Red = Color(1, 0, 0);
const Color Color::Green = Color(0, 1, 0);
const Color Color::Blue = Color(0, 0, 1);


/*
 * charles::basics::Color::Color --
 */
Color::Color()
    : Color(0.0, 0.0, 0.0, 0.0)
{ }


/*
 * charles::basics::Color::Color --
 */
Color::Color(const Double& r,
             const Double& g,
             const Double& b,
             const Double& a)
    : red(r),
      green(g),
      blue(b),
      alpha(a)
{ }


/*
 * charles::basics::Color::operator= --
 */
Color&
Color::operator=(const Color& rhs)
{
    red = rhs.red;
    green = rhs.green;
    blue = rhs.blue;
    alpha = rhs.alpha;
    return *this;
}


/*
 * charles::basics::Color::operator*= --
 */
Color&
Color::operator*=(const Double& rhs)
{
    red *= rhs;
    green *= rhs;
    blue *= rhs;
    return *this;
}


/*
 * charles::basics::Color::operator/= --
 */
Color&
Color::operator/=(const Double& rhs)
{
    return *this *= (1.0 / rhs);
}


/*
 * charles::basics::Color::operator+= --
 */
Color&
Color::operator+=(const Double& rhs)
{
    red += rhs;
    green += rhs;
    blue += rhs;
    alpha += rhs;
    return *this;
}


/*
 * charles::basics::Color::operator-= --
 */
Color&
Color::operator-=(const Double& rhs)
{
    return *this += -rhs;
}


/*
 * charles::basics::Color::operator* --
 */
Color
Color::operator*(const Double& rhs)
    const
{
    return Color(*this) *= rhs;
}


/*
 * charles::basics::Color::operator/ --
 */
Color
Color::operator/(const Double& rhs)
    const
{
    return Color(*this) /= rhs;
}


/*
 * charles::basics::Color::operator+ --
 */
Color
Color::operator+(const Double& rhs)
    const
{
    return Color(*this) += rhs;
}


/*
 * charles::basics::Color::operator- --
 */
Color
Color::operator-(const Double& rhs)
    const
{
    return Color(*this) -= rhs;
}


/*
 * charles::basics::Color::operator*= --
 */
Color&
Color::operator*=(const Color& rhs)
{
    red *= rhs.red;
    green *= rhs.green;
    blue *= rhs.blue;
    return *this;
}


/*
 * charles::basics::Color::operator/= --
 */
Color&
Color::operator/=(const Color& rhs)
{
    red /= rhs.red;
    green /= rhs.green;
    blue /= rhs.blue;
    return *this;
}


/*
 * charles::basics::Color::operator+= --
 */
Color&
Color::operator+=(const Color& rhs)
{
    red += rhs.red;
    green += rhs.green;
    blue += rhs.blue;
    alpha += rhs.alpha;
    return *this;
}


/*
 * charles::basics::Color::operator-= --
 */
Color&
Color::operator-=(const Color& rhs)
{
    red -= rhs.red;
    green -= rhs.green;
    blue -= rhs.blue;
    alpha -= rhs.alpha;
    return *this;
}


/*
 * charles::basics::Color::operator* --
 */
Color
Color::operator*(const Color& rhs)
    const
{
    return Color(*this) *= rhs;
}


/*
 * charles::basics::Color::operator/ --
 */
Color
Color::operator/(const Color& rhs)
    const
{
    return Color(*this) /= rhs;
}


/*
 * charles::basics::Color::operator+ --
 */
Color
Color::operator+(const Color& rhs)
    const
{
    return Color(*this) += rhs;
}


/*
 * charles::basics::Color::operator- --
 */
Color
Color::operator-(const Color& rhs)
    const
{
    return Color(*this) -= rhs;
}


/*
 * charles::basics::operator* --
 */
const Color
operator*(const Double& lhs,
          const Color& rhs)
{
    return rhs * lhs;
}


/*
 * charles::basics::operator<< --
 */
std::ostream &
operator<<(std::ostream& os,
           const Color& c)
{
    // Stream colors like this: <r, g, b, a>
    os << "<" << c.red << ", " << c.green << ", " << c.blue << ", " << c.alpha << ">";
    return os;
}

} /* namespace basics */
} /* namespace charles */
