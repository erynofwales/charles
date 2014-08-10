/* color.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <ostream>


namespace charles {
namespace basics {

/*
 * Color::Color --
 */
Color::Color()
    : Color(0.0, 0.0, 0.0, 0.0)
{ }


/*
 * Color::Color --
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
 * Color::operator*= --
 * Color::operator/= --
 * Color::operator+= --
 * Color::operator-= --
 *
 * Perform the corresponding arithmetic operation on this color and the given scalar. These methods are destructive and
 * a reference to this color is returned.
 */
Color &
Color::operator*=(const Double &rhs)
{
    red *= rhs;
    green *= rhs;
    blue *= rhs;
    return *this;
}

Color &
Color::operator/=(const Double &rhs)
{
    return *this *= (1.0 / rhs);
}

Color &
Color::operator+=(const Double &rhs)
{
    red += rhs;
    green += rhs;
    blue += rhs;
    alpha += rhs;
    return *this;
}

Color &
Color::operator-=(const Double &rhs)
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
Color::operator*(const Double &rhs)
    const
{
    return Color(*this) *= rhs;
}

Color
Color::operator/(const Double &rhs)
    const
{
    return Color(*this) /= rhs;
}

Color
Color::operator+(const Double &rhs)
    const
{
    return Color(*this) += rhs;
}

Color
Color::operator-(const Double &rhs)
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
operator*(const Double& lhs,
          const Color& rhs)
{
    return rhs * lhs;
}


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
