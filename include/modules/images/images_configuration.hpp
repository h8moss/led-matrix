#pragma once

#include <map>
#include <string>
#include <vector>

namespace Images {

enum ImageFit { stretch, crop, box };
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
  static std::map<std::string, Alignment> alignmentMap;
  static std::map<std::string, ImageFit> imageFitMap;
};
} // namespace Images
