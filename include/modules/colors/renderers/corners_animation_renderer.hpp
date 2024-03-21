#pragma once

#include "common/models/color.hpp"
#include "common/util/better_canvas.hpp"
#include "modules/module.hpp"

namespace Colors {

class CornersAnimationRenderer : public Module {
public:
  CornersAnimationRenderer(BetterCanvas *canvas);

  virtual int render() override;
  virtual void setup() override;
  virtual void teardown() override;

private:
  Color currentColor;
  int totalDiagonals;
  int loopCount;
};
} // namespace Colors
