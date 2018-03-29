#include "refractive_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Refractive_Shader::
Shade_Surface(const Ray& ray, const vec3& intersection_point,
        const vec3& same_side_normal, int recursion_depth,bool is_exiting) const
{

    vec3 v = (ray.endpoint - intersection_point).normalized();
    vec3 n = same_side_normal;
    if (is_exiting) n = -n;

    //Hints: Use REFRACTIVE_INDICES::AIR for air refractive_index
    //       Use is_exiting to decide the refractive indices on the ray and transmission sides
    vec3 reflection_color;
    vec3 refraction_color;
    double reflectance_ratio=-1;
    if(!world.disable_fresnel_refraction)
    {
        //TODO (Test 27+): Compute the refraction_color:
        // - Check if it is total internal reflection. 
        //      If so update the reflectance_ratio for total internal refraction
        //
        //      else, follow the instructions below
        //
        //        (Test 28+): Update the reflectance_ratio 
        //
        //        (Test 27+): Cast the refraction ray and compute the refraction_color
        //

        // calculate refraction
        double ni = (is_exiting) ? refractive_index : 1.0f;
        double nr = (is_exiting) ? 1.0f : refractive_index;
        double eta = ni / nr;
        double cosi = dot(v,n);
        double cosr = 1 - eta * eta * (1 - cosi * cosi);
        if (cosr < 0)
            reflectance_ratio = 1;
        else {
            cosr = sqrt(cosr);
            vec3 t = eta*(dot(v,n)*n - v) - cosr*n;
            refraction_color = world.Cast_Ray(Ray(intersection_point, t), recursion_depth);

            // calculate reflectance ratio
            double rperp = ((ni*cosi - nr*cosr)/(ni*cosi + nr*cosr));
            rperp *= rperp;
            double rpara = ((nr*cosi - ni*cosr)/(nr*cosi + ni*cosr));
            rpara *= rpara;
            reflectance_ratio = (rperp + rpara) / 2;
        }
    }

    if(!world.disable_fresnel_reflection){
        //TODO:(Test 26+): Compute reflection_color:
        // - Cast Reflection Ray andd get color
        //

        vec3 r = 2*dot(v,n)*n - v;
        reflection_color = world.Cast_Ray(Ray(intersection_point, r), recursion_depth);
    }

    Enforce_Refractance_Ratio(reflectance_ratio);
    vec3 color;
    // TODO: (Test 26+) Compute final 'color' by blending reflection_color and refraction_color using 
    //                  reflectance_ratio
    //
    color = reflectance_ratio * reflection_color + (1 - reflectance_ratio) * refraction_color;
    return color;
}

void Refractive_Shader::
Enforce_Refractance_Ratio(double& reflectance_ratio) const
{
    if(world.disable_fresnel_reflection) reflectance_ratio=0;
    else if(world.disable_fresnel_refraction) reflectance_ratio=1;
}

