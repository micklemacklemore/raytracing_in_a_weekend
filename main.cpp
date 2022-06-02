#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

color sky_blue(double t) {
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);  // lerp
}

inline color const black() {
    return color(0.0, 0.0, 0.0);
}

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y()) + 1.0;
    return sky_blue(t);
}

int main() {
    // Animation
    const int frames = 1;

    // Image
    const int image_width = 730;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // Render
    for (int time = 1; time <= frames; ++time) {
        std::vector<uint8_t> image_data;
        for (int j = image_height-1; j >= 0; --j) {
            for (int i = 0; i < image_width; ++i) {
                // color pixel_color(double(i) / (image_width-1), double(j) / (image_height-1), 0.25);
                auto u = double(i) / (image_width-1);
                auto v = double(j) / (image_height-1);
                ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
                color pixel_color = ray_color(r, world);
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

