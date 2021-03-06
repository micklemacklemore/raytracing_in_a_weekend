#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
    sphere() {}
    sphere(point3 cen, double r) : center(cen), radius(r) {};

    virtual bool hit (
        const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
    point3 center;
    double radius;
};

bool sphere::hit(const ray&r, double t_min, double t_max, hit_record& rec) const {
    // Consider the quadratic equation here (sort of.. consult Ray Tracing in a Weekend)
    // (-half_b + sqrt(half_b*half_b - a*c))/a

    // what is ray? is that 0??

    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);
    //std::cout << r.origin() << " | " << r.direction() << " | " << t_min << " | " << t_max << std::endl;
    //std::cout << sqrtd << " " << a << " " << half_b << std::endl;

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;  // ?? plus or minus? Learn quadratic formulas!
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    //std::cout << rec.t << " " << rec.p << " " << center << " " << radius << std::endl;
    rec.set_face_normal(r, outward_normal);

    return true;
}

#endif