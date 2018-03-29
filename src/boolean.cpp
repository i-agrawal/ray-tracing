#include "boolean.h"
#include <unordered_map>

// Determine if the ray intersects with the boolean of A and B.
bool Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    // TODO
    A->material_shader = material_shader;
    B->material_shader = material_shader;

    // calculate boolean logic
    std::vector<Hit> ha, hb;
    bool ret = false;
    switch(type) {
        case type_intersection:
            if (A->Intersection(ray, ha) && B->Intersection(ray, hb)) {
                hits.insert(hits.end(), ha.begin(), ha.end());
                hits.insert(hits.end(), hb.begin(), hb.end());
                ret = true;
            }
            break;
        case type_difference:
            if (A->Intersection(ray, ha) || B->Intersection(ray, hb)) {
                hits.insert(hits.end(), ha.begin(), ha.end());
                hits.insert(hits.end(), hb.begin(), hb.end());
                ret = true;
            }
            break;
        case type_union:
            if (A->Intersection(ray, ha) || B->Intersection(ray, hb)) {
                hits.insert(hits.end(), ha.begin(), ha.end());
                hits.insert(hits.end(), hb.begin(), hb.end());
                ret = true;
            }
            break;
        default:
            break;
    }
    return ret;
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}
