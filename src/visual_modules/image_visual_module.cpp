#include "image_visual_module.hpp"

#include <iostream>

ImageVisualModule::ImageVisualModule(Image p_image): image{p_image} { }

void ImageVisualModule::draw(Canvas *canvas) const {
  for (int x=0; x<64; x++) {
    for (int y=0; y<64; y++) {
      std::cout << "(" << image.values[y][x][0] << ", " << image.values[y][x][1] << ", " << image.values[y][x][2] << ")\n";
      canvas->SetPixel(x, y, this->image.values[y][x][0],this->image.values[y][x][1],this->image.values[y][x][2]);
    }
  }
}