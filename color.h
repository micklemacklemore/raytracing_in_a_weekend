#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>
#include <vector>

void add_pixel(std::vector<uint8_t> &image_data, color pixel_color) {
    int ir = static_cast<uint8_t>(255.999 * pixel_color.x());  //  static cast??
    int ig = static_cast<uint8_t>(255.999 * pixel_color.y());
    int ib = static_cast<uint8_t>(255.999 * pixel_color.z());
    image_data.push_back(ir);
    image_data.push_back(ig);
    image_data.push_back(ib);
}

#endif