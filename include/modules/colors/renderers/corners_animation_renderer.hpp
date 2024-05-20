#pragma once

#include "common/canvas/icanvas.hpp"
#include "common/models/color.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/colors/renderers/renderer.hpp"

namespace Colors {

class CornersAnimationRenderer : public Renderer {
public:
  CornersAnimationRenderer(ICanvas *canvas, Colors::Configuration config);

  long int render() override;
  void setup() override;
  void teardown() override;

private:
  Color currentColor;
  int totalDiagonals;
  int loopCount;
  float fullDuration;
};
} // namespace Colors
