#include "modules/colors/renderers/corners_animation_renderer.hpp"
#include "modules/colors/colors_configuration.hpp"

#include "common/util/debug_log.hpp"

#include <algorithm>
#include <cmath>

Colors::CornersAnimationRenderer::CornersAnimationRenderer(BetterCanvas *canvas)
    : Renderer(canvas), currentColor{}, totalDiagonals{}, loopCount{},
      fadeData{} {}

void Colors::CornersAnimationRenderer::setup() {
  canvas->clear();
  currentColor = getConfig()->getColor();
  totalDiagonals = canvas->getWidth() + canvas->getHeight() - 1;
  loopCount = 0;
  fadeData = {};
}

long int Colors::CornersAnimationRenderer::render() {
  int animationProgress =
      loopCount %
      ((int)(getConfig()->animationDuration + getConfig()->duration));
  if (getConfig()->runOnce &&
      animationProgress ==
          ((int)(getConfig()->animationDuration + getConfig()->duration))) {
    return -1;
  }

  if (animationProgress == 0) {
    if (!getConfig()->fading)
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
    if (getConfig()->fading) {
      fadeData.push_back({.x = delta, .y = 0, .fade = 1.0f});
    }
  }
  if (getConfig()->fading) {
    dLog("SIZE: " + std::to_string(fadeData.size()));

    for (size_t i{}; i < fadeData.size(); i++) {
      // fadeData[i].fade -= 1.0f / getConfig()->duration;
      fadeData[i].fade -= 0.01f;
      // fadeData[i].x is where we stored delta, y is useless
      for (int x{}; x <= fadeData[i].x; x++) {
        if (fadeData[i].fade <= 0.12f) {
          canvas->setPixel(x, fadeData[i].x - x - 1, Color::black);
        } else {
          canvas->setPixel(x, fadeData[i].x - x - 1,
                           currentColor * fadeData[i].fade);
        }
      }
    }

    fadeData.erase(
        std::remove_if(fadeData.begin(), fadeData.end(),
                       [](const FadeData &d) { return d.fade < 0.12f; }),
        fadeData.end());
  }

  ++loopCount;
  return 1000;
}

void Colors::CornersAnimationRenderer::teardown() { canvas->clear(); }
