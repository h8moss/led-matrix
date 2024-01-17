#include "image.hpp"

Image::Image(array<array<array<int, 3>, 64>, 64> p_values):
  values{p_values} { }
