/* ray.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "basics/ray.hh"


namespace charles {
namespace basics {

/*
 * charles::basics::Ray::Ray --
 */
Ray::Ray(Vector4 o,
         Vector4 d)
    : origin(o),
      direction(d)
{ }


/*
 * charles::basics::Ray::Parameterize --
 */
Vector4
Ray::Parameterize(const Double& t)
    const
{
    return origin + direction * t;
}


} /* namespace basics */
} /* namespace charles */

