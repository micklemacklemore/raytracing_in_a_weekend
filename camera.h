#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
    public:
    camera() {
        const auto aspect_ratio = 16.0 / 9.0;
        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;
        auto focal_length = 1.0;

        auto origin = point3(0, 0, 0);
        auto horizontal = vec3(viewport_width, 0, 0);
        auto vertical = vec3(0, viewport_height, 0);
        // 0, 0, 0 - 0, 0, 1 - width/2, 0, 0 - horizontal/2, 0, 0
        auto lower_left_corner = origin - vec3(0, 0, focal_length) - vertical/2 - horizontal/2;
    }

    ray get_ray(double u, double v) const {
        return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }

    private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};
#endif