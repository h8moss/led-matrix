#pragma once

#include "common/canvas/icanvas.hpp"
#include "common/models/color.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/colors/renderers/renderer.hpp"

namespace Colors {

class CircleAnimationRenderer : public Renderer {
public:
  CircleAnimationRenderer(ICanvas *canvas, Colors::Configuration config,
                          bool _shrink = false);

  long int render() override;
  void setup() override;
  void teardown() override;

private:
  int radius;
  int currentRadius;
  int centerX;
  int centerY;
  Color color;
  int loopCount;

  bool shrink;
};
} // namespace Colors
