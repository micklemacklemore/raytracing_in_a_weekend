#ifndef CAMERA_H
#define CAMERA_H
#define LOG(x, y) std::cout << x << " " << y << std::endl

#include "rtweekend.h"

class camera {
    public:
    camera() {
        const auto aspect_ratio = 16.0 / 9.0;
        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;
        auto focal_length = 1.0;

        origin = point3(0, 0, 0);
        horizontal = vec3(viewport_width, 0.0, 0.0);
        vertical = vec3(0.0, viewport_height, 0.0);
        // 0, 0, 0 - 0, 0, 1 - width/2, 0, 0 - horizontal/2, 0, 0
        lower_left_corner = origin - vertical/2 - horizontal/2 - vec3(0, 0, focal_length);
    }

    ray get_ray(double u, double v) const {
        ray thing(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        //std::cout << "ray " << thing.direction() << " | " << thing.origin() << std::endl;
        return thing;
    }

    vec3 getHorizontal() { return horizontal; }

    private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};
#endif