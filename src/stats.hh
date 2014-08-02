/* stats.hh
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#ifndef __STATS_HH__
#define __STATS_HH__

namespace charles {

struct Stats
{
    Stats();

    unsigned long TotalRays() const;

    void PrintRayTable() const;
    void PrintIntersectionsTable() const;

    /* Ray counts */
    unsigned long primaryRays;
    unsigned long shadowRays;
    unsigned long reflectionRays;
    unsigned long transmissionRays;

    /* Intersection counts */
    unsigned long boxIntersections;
    unsigned long boxIntersectionTests;
    unsigned long planeIntersections;
    unsigned long planeIntersectionTests;
    unsigned long sphereIntersections;
    unsigned long sphereIntersectionTests;

private:
    void PrintRayRow(const std::string& title,
                     const unsigned long& value) const;
    void PrintIntersectionsRow(const std::string& title,
                               const unsigned long& num,
                               const unsigned long& total) const;
};

} /* namespace charles */

#endif /* __STATS_HH__ */
