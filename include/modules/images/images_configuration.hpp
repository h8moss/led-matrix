#pragma once

#include <string>
#include <vector>

namespace Images {

enum ImageFit {
  stretch, // Ignores aspect ratio, stretches to fit
  crop, // Grows the image until it fills the screen, even if it crops part of
        // it
  box,  // Grows the image until it fits the screen, not cropping anything
  place // Places the image in it's original dimensions, does not resize at all
};
enum Alignment { leading, trailing, center };

struct Configuration {
  std::vector<std::string> images;
  std::vector<int> durations;
  ImageFit fit;
  Alignment xAlignment;
  Alignment yAlignment;
  bool exitOnEnd;
  bool shuffleImages;

  static Configuration defaults;
};
} // namespace Images
