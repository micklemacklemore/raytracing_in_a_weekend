#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "rtweekend.h"

#include <iostream>
#include <vector>

void add_pixel(std::vector<uint8_t> &image_data, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // std::cout << pixel_color << std::endl;

    // Divide the color by the number of samples
    auto scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    //std::cout << "nothing: " << static_cast<uint8_t>(256 * clamp(r, 0.0, 0.999)) << '\n';

    image_data.push_back(static_cast<uint8_t>(256 * clamp(r, 0.0, 0.999)));  // what is static cast?
    image_data.push_back(static_cast<uint8_t>(256 * clamp(g, 0.0, 0.999)));
    image_data.push_back(static_cast<uint8_t>(256 * clamp(b, 0.0, 0.999)));
}

#endif