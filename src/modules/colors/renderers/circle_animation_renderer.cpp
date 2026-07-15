#include "modules/colors/renderers/circle_animation_renderer.hpp"
#include "common/canvas/icanvas.hpp"
#include "common/util/debug_log.hpp"
#include "modules/colors/colors_configuration.hpp"

#include <algorithm>
#include <cmath>

Colors::CircleAnimationRenderer::CircleAnimationRenderer(
    ICanvas *canvas, Colors::Configuration config, bool _shrink)
    : Renderer(canvas, config), radius{}, currentRadius{}, centerX{}, centerY{},
      color{}, loopCount{}, shrink{_shrink} {}

void Colors::CircleAnimationRenderer::setup() {
  canvas->clear();
  radius = (int)std::sqrt(canvas->getHeight() * canvas->getHeight() +
                          canvas->getWidth() * canvas->getWidth()) +
           1;
  centerX = canvas->getWidth() / 2;
  centerY = canvas->getHeight() / 2;

  currentRadius = 0;
  loopCount = 0;

  color = config.getColor();
}

long int Colors::CircleAnimationRenderer::render() {
  int progress{loopCount % (int)(config.animationDuration + config.duration)};
  if (progress == 0) {
    canvas->fill(color);
    color = config.getColor();
  }

  if (config.runOnce &&
      progress == (int)(config.animationDuration + config.duration) - 1) {
    return -1;
  }

  if ((float)progress <= config.animationDuration) {
    float percent{(float)progress / config.animationDuration};
    if (shrink)
      percent = 1.0f - percent;
    int nextRadius{(int)(radius * percent)};
    if (nextRadius != currentRadius) {
      currentRadius = nextRadius;

      dLog(color);
      canvas->drawCircle(centerX, centerY, currentRadius, color,
                         !config.fading);
      if (config.fading) {
        dLog(color);
        for (int i = 1; i <= 10; i++) {
          int r = currentRadius + i;
          Color col = color * (1 - (float)i / 10);
          canvas->drawCircle(centerX, centerY, r, col, false);
        }
      }
    }
  }

  ++loopCount;
  return 1000;
}

void Colors::CircleAnimationRenderer::teardown() { canvas->clear(); }
