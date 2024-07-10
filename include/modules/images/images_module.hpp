#pragma once

#include "common/canvas/icanvas.hpp"
#include "modules/images/images_configuration.hpp"
#include "modules/module.hpp"

#include <Magick++.h>
#include <Magick++/Image.h>

namespace Images {
class ImagesModule : public Module {
public:
  ImagesModule(ICanvas *canvas);

  void setup() override;
  long int render() override;
  void teardown() override;

  void addFlags(CLI::App *app) override;
  void
  readArguments(std::map<std::string, std::vector<std::string>> args) override;

  ~ImagesModule();

private:
  Images::Configuration config;

  int loopCount;
  std::vector<Magick::Image> images;
  std::vector<std::vector<Color>> pixels;
};
} // namespace Images
