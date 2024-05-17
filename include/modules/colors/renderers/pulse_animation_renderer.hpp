#pragma once
#include <array>

#include "modules/colors/colors_configuration.hpp"
#include "modules/colors/renderers/renderer.hpp"

namespace Colors {

class PulseAnimationRenderer : public Renderer {
public:
  PulseAnimationRenderer(BetterCanvas *canvas, Colors::Configuration config);

  long int render() override;
  void setup() override;
  void teardown() override;

private:
  Color currentColor;
  std::array<int, 4> animationSplits;
  int loopCount;
};
} // namespace Colors
