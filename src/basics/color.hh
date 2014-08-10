/* color.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "basics/types.hh"


namespace charles {
namespace basics {

struct Color
{
    Color();
    Color(const Double& r, const Double& g, const Double& b, const Double& a = 1.0);

    Color &operator*=(const Double &rhs);
    Color &operator/=(const Double &rhs);
    Color &operator+=(const Double &rhs);
    Color &operator-=(const Double &rhs);
    Color operator*(const Double &rhs) const;
    Color operator/(const Double &rhs) const;
    Color operator+(const Double &rhs) const;
    Color operator-(const Double &rhs) const;

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

    Double red, green, blue, alpha;
};


const Color operator*(const Double &lhs, const Color &rhs);

std::ostream &operator<<(std::ostream &os, const Color &c);

} /* namespace basics */
} /* namespace charles */

