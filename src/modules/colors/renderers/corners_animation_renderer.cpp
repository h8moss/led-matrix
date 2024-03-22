#include "modules/colors/renderers/corners_animation_renderer.hpp"
#include "modules/colors/colors_configuration.hpp"

#include <cmath>

Colors::CornersAnimationRenderer::CornersAnimationRenderer(BetterCanvas *canvas)
    : Module(canvas, new Colors::Configuration()), currentColor{},
      totalDiagonals{}, loopCount{} {}

void Colors::CornersAnimationRenderer::setup() {
  canvas->clear();
  currentColor =
      static_cast<Colors::Configuration *>(configuration)->getColor();
  totalDiagonals = canvas->getWidth() * canvas->getHeight() - 1;
  loopCount = 0;
}

int Colors::CornersAnimationRenderer::render() {
  int animationProgress =
      loopCount %
      ((int)(static_cast<Colors::Configuration *>(configuration)
                 ->animationDuration +
             static_cast<Colors::Configuration *>(configuration)->duration));

  if (animationProgress == 0) {
    canvas->fill(currentColor);
    currentColor =
        static_cast<Colors::Configuration *>(configuration)->getColor();
  }

  if ((float)animationProgress >=
      static_cast<Colors::Configuration *>(configuration)->duration) {
    int delta{static_cast<int>(std::floor(
        totalDiagonals *
        ((float)animationProgress -
         static_cast<Colors::Configuration *>(configuration)->duration) /
        (static_cast<Colors::Configuration *>(configuration)
             ->animationDuration)))};
    for (int x{}; x <= delta; x++) {
      canvas->setPixel(x, delta - x - 1, currentColor);
    }
  }

  ++loopCount;
  return 1000;
}

void Colors::CornersAnimationRenderer::teardown() { canvas->clear(); }
