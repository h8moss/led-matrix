#pragma once
#include <array>

using std::array;

class Image {
public:
  // TODO: As of right now, images can only be 64x64, if we want this to be usable on other boards, we will eventually change that
  array<array<array<int, 3>,64>, 64> values;

  Image(array<array<array<int, 3>,64>, 64> p_values);
};