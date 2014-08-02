/* object_plane.h
 *
 * Planes are Shapes defined by a point and two direction vectors.
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>

#include "basics.h"
#include "object.h"
#include "object_plane.h"


/*
 * Plane::Plane --
 *
 * Default constructor. Create a Plane with a point at the origin and normal vector in the Y direction.
 */
Plane::Plane()
    : Plane(Vector3::Y)
{ }


/*
 * Plane::Plane --
 *
 * Constructor. Create a Plane with a point at the origin, and a given normal.
 */
Plane::Plane(Vector3 n)
    : Plane(Vector3::Zero, n)
{ }


/*
 * Plane::Plane --
 *
 * Constructor. Create a Plane with the given origin and normal vectors.
 */
Plane::Plane(Vector3 o, Vector3 n)
    : Shape(o),
      normal(n.normalize())
{ }


/*
 * Plane::does_intersect --
 *
 * Compute the intersection of a ray with this Plane. All intersection t values are returned in the **t argument. The
 * number of values returned therein is indicated by the return value. Memory is allocated at *t. It is the caller's
 * responsibility to free it when it is no longer needed. If 0 is returned, no memory needs to be freed.
 */
int
Plane::does_intersect(const Ray &ray, float **t)
    const
{
    /*
     * The algebraic form of a plane is the following:
     *
     *     (p - p0) . n = 0
     *
     * where p is a point in the plane, p0 is another point in the plane (the origin point in our case), and n is the
     * normal vector. (Periods [.] indicate dot products.) We can plug in the parametric equation for a Ray and solve
     * for t to get the intersection point.
     *
     *     ((ro + t*rd) - p0) . n = 0
     *
     * Simplifying, distributing, and solving for t:
     *
     *     t = ((p0 - ro) . n) / (ld . n)
     *
     * Note that if the denominator is 0, the ray runs parallel to the plane and there are no intersections. If both the
     * numerator and denominator are 0, the ray is in the plane and intersects everywhere.
     *
     * See: http://en.wikipedia.org/wiki/Line-plane_intersection
     */
    Vector3 o = get_origin();
    int nints = 1;
    float numer = (o - ray.origin).dot(normal);
    float denom = ray.direction.dot(normal);

    if (denom == 0.0) {
        nints = 0;
        if (numer == 0.0) {
            // Ray is in plane.
            nints = 1;
        }
    }

    // No intersections.
    if (nints == 0) {
        return nints;
    }

    // TODO: denom could still be 0 here!
    float t0 = numer / denom;

    // If the t value is negative, it's "behind" the origin of the ray, which we don't care about.
    if (t0 < 0.0) {
        return 0;
    }

    // Allocate memory, at most one float.
    if (t != NULL) {
        *t = new float(t0);
    }

    return nints;
}


/*
 * Plane::point_is_on_surface --
 *
 * Determine if a point lies on the surface of this Sphere.
 */
bool
Plane::point_is_on_surface(const Vector3 &p)
    const
{
    /*
     * Plug point p into the equation for a plane:
     *
     *     a(x - ox) + b(y - oy) + c(z - oz) = 0
     *
     * where (a, b, c) are the coordinates of the normal vector, and (ox, oy, oz) are the coordinates of the origin
     * vector.
     *
     * I found this page most helpful:
     * http://www.math.oregonstate.edu/home/programs/undergrad/CalculusQuestStudyGuides/vcalc/lineplane/lineplane.html
     */
    Vector3 o = get_origin();
    float x = normal.x * (p.x - o.x);
    float y = normal.y * (p.y - o.y);
    float z = normal.z * (p.z - o.z);
    return (x + y + z) == 0.0;
}


/*
 * Plane::compute_normal --
 *
 * Compute the normal for this Plane at the given point. If the point does not lie on the surface of the plane, a zero
 * vector is returned.
 */
Vector3
Plane::compute_normal(const Vector3 &p)
    const
{
    if (!point_is_on_surface(p)) {
        return Vector3::Zero;
    }

    // This one's easy since planes are defined by their normals. :)
    return normal;
}
