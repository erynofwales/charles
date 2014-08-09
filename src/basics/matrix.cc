/* matrix.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "matrix.hh"


namespace charles {
namespace basics {

/*
 * charles::basics::TranslationMatrix --
 */
Matrix4
TranslationMatrix(const Double& x,
                  const Double& y,
                  const Double& z)
{
    Matrix4 m = Matrix4::Identity();
    m(0, 3) = x;
    m(1, 3) = y;
    m(2, 3) = z;
    return m;
}

} /* namespace mespace  */
} /* namespace charles */

