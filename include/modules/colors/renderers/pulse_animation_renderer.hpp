#pragma once
#include <array>

#include "modules/module.hpp"

namespace Colors {

class PulseAnimationRenderer : public Module {
public:
  PulseAnimationRenderer(BetterCanvas *canvas);

  virtual int render() override;
  virtual void setup() override;
  virtual void teardown() override;

private:
  Color currentColor;
  std::array<int, 4> animationSplits;
  int loopCount;
};
} // namespace Colors
