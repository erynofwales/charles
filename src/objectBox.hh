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

    /** @see charles::Object::Write */
    void Write(std::ostream& ost) const;

private:
    /**
     * Perform the intersection test on a slab, defined by `slabHigh` and
     * `slabLow`.
     *
     * @param [in]     slabLow               The lower bound of the slab
     * @param [in]     slabHigh              The upper bound of the slab
     * @param [in]     rayOriginComponent    The ray's origin component
     * @param [in]     rayDirectionComponent The ray's direction component
     * @param [in,out] tNear                 The nearest intersection t value
     * @param [in,out] tFar                  The farthest intersection t value
     * @returns `true` if the box was hit on this slab
     */
    bool IntersectSlab(const Double& slabLow,
                       const Double& slabHigh,
                       const Double& rayOriginComponent,
                       const Double& rayDirectionComponent,
                       Double& tNear,
                       Double& tFar) const;

    /** The near, lower left corner. */
    Vector3 mNear;

    /** The far, upper right corner. */
    Vector3 mFar;
};

} /* namespace charles */
