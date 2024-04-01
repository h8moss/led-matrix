#include "modules/colors/renderers/corners_animation_renderer.hpp"
#include "common/util/debug_log.hpp"
#include "modules/colors/colors_configuration.hpp"

#include <cmath>

Colors::CornersAnimationRenderer::CornersAnimationRenderer(BetterCanvas *canvas)
    : Renderer(canvas), currentColor{}, totalDiagonals{}, loopCount{} {}

void Colors::CornersAnimationRenderer::setup() {
  canvas->clear();
  currentColor = getConfig()->getColor();
  totalDiagonals = canvas->getWidth() + canvas->getHeight() - 1;
  loopCount = 0;
}

long int Colors::CornersAnimationRenderer::render() {
  int animationProgress =
      loopCount %
      ((int)(getConfig()->animationDuration + getConfig()->duration));

  if (animationProgress == 0) {
    canvas->fill(currentColor);
    currentColor = getConfig()->getColor();
  }

  if ((float)animationProgress >= getConfig()->duration) {
    int delta{static_cast<int>(std::floor(
        totalDiagonals * ((float)animationProgress - getConfig()->duration) /
        (getConfig()->animationDuration)))};
    for (int x{}; x <= delta; x++) {
      canvas->setPixel(x, delta - x - 1, currentColor);
    }
  }

  ++loopCount;
  return 1000;
}

void Colors::CornersAnimationRenderer::teardown() { canvas->clear(); }
