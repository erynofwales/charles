/* objectBox.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include "basics.h"
#include "object.h"
#include "types.hh"


namespace charles {

struct Box
    : public Object
{
    Box();
    Box(const Vector3& near, const Vector3& far);

    Vector3& GetNear();
    void SetNear(const Vector3& near);
    Vector3& GetFar();
    void SetFar(const Vector3& far);

    bool DoesIntersect(const Ray& ray, TVector& t, Stats& stats) const;
    bool point_is_on_surface(const Vector3 &p) const;
    Vector3 compute_normal(const Vector3 &p) const;

private:
    /** The near, lower left corner. */
    Vector3 mNear;

    /** The far, upper right corner. */
    Vector3 mFar;
};

} /* namespace charles */
