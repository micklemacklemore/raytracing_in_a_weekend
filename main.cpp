#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"

double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;

    // Consider the quadratic equation here (sort of.. consult Ray Tracing in a Weekend)
    // (-half_b + sqrt(half_b*half_b - a*c))/a
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

color sky_blue(double t) {
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);  // lerp
}

inline color const black() {
    return color(0.0, 0.0, 0.0);
}

color ray_color(const ray& r, const point3& spherePos) {
    auto t = hit_sphere(spherePos, 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return sky_blue(t);
}

int main() {
    // Animation
    const int frames = 1;

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 730;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);

    // 0, 0, 0 - 0, 0, 1 - width/2, 0, 0 - horizontal/2, 0, 0
    auto lower_left_corner = origin - vec3(0, 0, focal_length) - vertical/2 - horizontal/2;

    
    //render
    for (int time = 1; time <= frames; ++time) {
        std::vector<uint8_t> image_data;
        for (int j = image_height-1; j >= 0; --j) {
            for (int i = 0; i < image_width; ++i) {
                // color pixel_color(double(i) / (image_width-1), double(j) / (image_height-1), 0.25);
                auto u = double(i) / (image_width-1);
                auto v = double(j) / (image_height-1);
                ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
                color pixel_color = ray_color(r, point3(0, 0, -1));
                add_pixel(image_data, pixel_color);
            }
        }

        std::ostringstream imagePathStream;
        imagePathStream << "images/image" << std::setw(3) << std::setfill('0') << time << ".png";

        if (stbi_write_png(imagePathStream.str().c_str(), image_width, image_height, 3, image_data.data(), sizeof(uint8_t)*3*image_width)) {
            std::cerr << "\rImage saved: " << time << ' ' << std::flush;
        }
        else {
            std::cerr << ' ' << imagePathStream.str() <<" failed to save." << ' ' << std::endl;
            break;
        }
    }
    std::cout << "Done." << std::endl;

    return 0;
}

