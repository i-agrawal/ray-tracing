#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const 
{
    vec3 color;
    // TODO: determine the color

    // declare basic variables
    Hit hit;
    vec3 v = (ray.endpoint - intersection_point).normalized();
    vec3 n = same_side_normal;
    if (is_exiting) n = -n;

    // calculate ambient color
    color = color_ambient * world.ambient_color * world.ambient_intensity;
    for (Light* light : world.lights) {

        // calculate light
        double dist = (light->position - intersection_point).magnitude_squared();
        vec3 l = (light->position - intersection_point).normalized();

        // calculate shadows
        if (world.enable_shadows && world.Closest_Intersection(Ray(intersection_point, l), hit) && hit.t*hit.t <= dist)
            continue;

        // calculate diffuse
        double diffuse = dot(l,n);
        if (diffuse < 0)
            continue;
        color += color_diffuse * diffuse * light->Emitted_Light(ray) / dist;

        // calculate specular
        vec3 r = 2 * diffuse * n - l;
        double specular = dot(r,v);
        if (specular < 0)
            continue;
        color += color_specular * pow(specular, specular_power) * light->Emitted_Light(ray) / dist;
    }

    return color;
}
