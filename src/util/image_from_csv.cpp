#include "image_from_csv.hpp"

#include "hex_to_rgb.hpp"

Image imageFromCSV(std::string csv) {
  array<array<array<int, 3>, 64>, 64> imageValues{};
  while (csv[csv.length()-1] == '\n') {
    csv = csv.substr(0, csv.length()-1);
  }

  size_t pos{0};
  int count{};

  while ((pos = csv.find(',')) != std::string::npos) {
    std::string token = csv.substr(0, pos);
    
    imageValues[(count/64)][count % 64] = hexToRGB(token);
    csv.erase(0, pos + 1);
    count++;
  }

  imageValues[(count/64)][count % 64] = hexToRGB(csv);

  return Image{imageValues};
}