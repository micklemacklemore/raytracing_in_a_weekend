#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        // if front_face is true, assign outward_normal, else -outward_normal
        normal = front_face ? outward_normal :-outward_normal; // ternary operator
    }
};

// C++ abstract class????!
class hittable {
    public:
    // what does this mean? function is a virtual const and it equals 0!
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;  
};

#endif