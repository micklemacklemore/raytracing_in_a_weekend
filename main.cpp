#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "vec3.h"

int main() {

    // Image

    const int image_width = 256;
    const int image_height = 256;

    // Render

    // std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    uint8_t image_data[image_width*image_height*3];
    int image_data_index = 0;

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = double(i) / (image_width-1);  // 0 / 255   = 0
            auto g = double(j) / (image_height-1); // 255 / 255 = 1
            auto b = 0.25;

            int ir = static_cast<uint8_t>(255.999 * r);  //  static cast??
            int ig = static_cast<uint8_t>(255.999 * g);
            int ib = static_cast<uint8_t>(255.999 * b);

            // std::cout << ir << ' ' << ig << ' ' << ib << '\n';

            image_data[image_data_index++] = ir;
            image_data[image_data_index++] = ig;
            image_data[image_data_index++] = ib;
        }
    }

    if (stbi_write_png("image.png", image_width, image_height, 3, &image_data, sizeof(unsigned char)*3*image_width)) {
        std::cout << "image.png saved successfully!" << std::endl;
    }
    else {
        std::cout << "image.png failed to save." << std::endl;
    }

    return 0;
}

