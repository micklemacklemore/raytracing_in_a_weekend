#include <iostream>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "vec3.h"
#include "color.h"



int main() {

    // Image
    const int image_width = 256;
    const int image_height = 256;

    // Render
    std::vector<uint8_t> image_data;

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(double(i) / (image_width-1), double(j) / (image_height-1), 0.25);
            add_pixel(image_data, pixel_color);
        }
    }

    if (stbi_write_png("image.png", image_width, image_height, 3, image_data.data(), sizeof(uint8_t)*3*image_width)) {
        std::cout << "image.png saved successfully!" << std::endl;
    }
    else {
        std::cout << "image.png failed to save." << std::endl;
    }

    return 0;
}

