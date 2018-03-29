#include "sphere.h"
#include "ray.h"


// Determine if the ray intersects with the sphere
bool Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO

    // declare basic variables
    vec3 u = ray.direction;
    vec3 p = ray.endpoint - center;

    // declare quadratic variables
    double a = dot(u,u);
    double b = 2 * dot(u,p);
    double c = dot(p,p) - radius*radius;

    // find determinant
    double det = b*b - 4*a*c;
    if (det <= 0)
        return false;

    // find further intersection
    double t1 = (-b + sqrt(det)) / (2*a);
    if (t1 < 0)
        return false;
    Hit hit = {.object = this, .t = t1, .ray_exiting = true};
    hits.push_back(hit);
    
    // find closer intersection
    double t2 = (-b - sqrt(det)) / (2*a);
    if (t2 < 0)
        return true;
    hit = {.object = this, .t = t2, .ray_exiting = false};
    hits.push_back(hit);

    return true;
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    normal = (point - center).normalized();
    return normal;
}
