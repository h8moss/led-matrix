#pragma once

#include "common/models/color.hpp"
#include "common/util/better_canvas.hpp"
#include "modules/colors/renderers/renderer.hpp"

namespace Colors {

class CircleAnimationRenderer : public Renderer {
public:
  CircleAnimationRenderer(BetterCanvas *canvas, bool _shrink = false);
  virtual ~CircleAnimationRenderer();

  virtual long int render() override;
  virtual void setup() override;
  virtual void teardown() override;

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
