/* stats.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cstdio>
#include <string>

#include "stats.hh"


namespace charles{

Stats::Stats()
    : primaryRays(),
      shadowRays(),
      reflectionRays(),
      transmissionRays(),
      boxIntersections(),
      boxIntersectionTests(),
      planeIntersections(),
      planeIntersectionTests(),
      sphereIntersections(),
      sphereIntersectionTests()
{ }


unsigned long
Stats::TotalRays()
    const
{
    return primaryRays + shadowRays + reflectionRays + transmissionRays;
}


void
Stats::PrintRayTable()
    const
{
    printf("RAY TYPE              NUM      %%\n");
    printf("-------------- ---------- ------\n");
    PrintRayRow("primary", primaryRays);
    PrintRayRow("shadow", shadowRays);
    PrintRayRow("reflection", reflectionRays);
    PrintRayRow("transmission", transmissionRays);
    PrintRayRow("total", TotalRays());
}


void
Stats::PrintIntersectionsTable()
    const
{
    printf("SHAPE                INTS      TESTS  SUCC %%\n");
    printf("-------------- ---------- ---------- -------\n");
    if (boxIntersectionTests > 0) {
        PrintIntersectionsRow("boxes", boxIntersections, boxIntersectionTests);
    }
    if (planeIntersectionTests > 0) {
        PrintIntersectionsRow("planes", planeIntersections, planeIntersectionTests);
    }
    if (sphereIntersectionTests > 0) {
        PrintIntersectionsRow("spheres", sphereIntersections, sphereIntersectionTests);
    }
}


void
Stats::PrintRayRow(const std::string& title,
                   const unsigned long& value)
    const
{
    double totalRays = TotalRays();
    printf("%-14s %10ld %#6.1lf%%\n",
           title.c_str(),
           value,
           double(value) / totalRays * 100.0);
}


void
Stats::PrintIntersectionsRow(const std::string& title,
                             const unsigned long& num,
                             const unsigned long& total)
    const
{
    printf("%-14s %10ld %10ld %#5.1lf%%\n",
           title.c_str(),
           num, total, double(num) / double(total) * 100.0);
}

} /* namespace charles */
