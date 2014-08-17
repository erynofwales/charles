/* objectBox.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __OBJECTBOX_HH__
#define __OBJECTBOX_HH__

#include "object.hh"
#include "basics/basics.hh"


namespace charles {

struct Box
    : public Object
{
    Box();
    Box(const basics::Vector4& near, const basics::Vector4& far);

    basics::Vector4& GetNear();
    void SetNear(const basics::Vector4& near);

    basics::Vector4& GetFar();
    void SetFar(const basics::Vector4& far);

    /** @see charles::Object::Write */
    void Write(std::ostream& ost) const;

protected:
    bool DoIntersect(const basics::Ray& ray, TVector& t, Stats& stats) const;
    basics::Vector4 DoNormal(const basics::Vector4& p) const;

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
    basics::Vector4 mNear;

    /** The far, upper right corner. */
    basics::Vector4 mFar;
};

} /* namespace charles */

#endif /* __OBJECTBOX_HH__ */
