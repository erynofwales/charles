/* ray.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "basics/types.hh"
#include "basics/vector.hh"


namespace charles {
namespace basics {

struct Ray
{
    Ray(Vector4 o = Vector4(), Vector4 d = Vector4());

    Vector4 Parameterize(const Double& t) const;

    Vector4 origin;
    Vector4 direction;
};

} /* namespace basics */
} /* namespace charles */

