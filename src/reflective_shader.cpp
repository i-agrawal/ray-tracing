#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"
#include <cstdlib>

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const
{
    vec3 color;
    // TODO: determine the color

    // declare basic variables
    vec3 v = (ray.endpoint - intersection_point).normalized();
    vec3 n = same_side_normal;
    if (is_exiting) n = -n;

    // calculate reflection
    vec3 r = 2*dot(v,n)*n - v;
    Ray reflect(intersection_point, r);
    color = reflectivity * world.Cast_Ray(reflect, recursion_depth) +
            (1 - reflectivity) * shader->Shade_Surface(ray,intersection_point,same_side_normal,recursion_depth,is_exiting);

    return color;
}
