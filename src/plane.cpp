#include "plane.h"
#include "ray.h"
#include <cfloat>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
bool Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO ✓

    // calculate dot between normal and ray
    double bot = dot(normal, ray.direction);
    if (bot == 0)
        return false;

    // calculate dot between normal and distance
    double top = dot(normal, x1 - ray.endpoint);
    double t = top / bot;
    if (t < 0)
        return false;

    // calculate hit
    Hit h = {.object = this, .t = t, .ray_exiting = (top > 0)};
    hits.push_back(h);
    return true;
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}
