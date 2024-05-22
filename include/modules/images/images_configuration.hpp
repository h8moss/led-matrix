#pragma once

#include <string>
#include <vector>

#include "modules/module_configuration.hpp"
namespace Images {

enum ImageFit { stretch, crop, box };
enum Alignment { leading, trailing, center };

struct ImageData {
public:
  std::string path;
  int duration;
};

class Configuration : public ModuleConfiguration {
public:
  Configuration();

  virtual const char *getHelp() const override;
  virtual void parseArguments(char **argv, int argc) override;
  virtual void parseData(std::string data) override;

  std::vector<ImageData> imageData;
  ImageFit fit;
  Alignment xAlignment;
  Alignment yAlignment;
  bool exitOnEnd;
  bool shuffleImages;
};
} // namespace Images
