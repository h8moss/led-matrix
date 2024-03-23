#include "modules/colors/renderers/circle_animation_renderer.hpp"
#include "common/util/better_canvas.hpp"
#include "modules/colors/colors_configuration.hpp"

#include <cmath>

Colors::CircleAnimationRenderer::CircleAnimationRenderer(BetterCanvas *canvas,
                                                         bool _shrink)
    : Renderer(canvas), radius{}, currentRadius{}, centerX{}, centerY{},
      color{}, loopCount{}, shrink{_shrink} {}

Colors::CircleAnimationRenderer::~CircleAnimationRenderer() {}

void Colors::CircleAnimationRenderer::setup() {
  canvas->clear();
  radius = (int)std::sqrt(canvas->getHeight() * canvas->getHeight() +
                          canvas->getWidth() * canvas->getWidth()) +
           1;
  centerX = canvas->getWidth() / 2;
  centerY = canvas->getHeight() / 2;

  currentRadius = 0;
  loopCount = 0;

  color = getConfig()->getColor();
}

int Colors::CircleAnimationRenderer::render() {
  int animationProgress{loopCount % (int)(getConfig()->animationDuration +
                                          getConfig()->duration)};
  if (animationProgress == 0) {
    canvas->fill(color);
    color = getConfig()->getColor();
  }

  if ((float)animationProgress >= getConfig()->duration) {
    float percent{(((float)animationProgress - getConfig()->duration) /
                   getConfig()->animationDuration)};
    if (this->shrink)
      percent = 1.0f - percent;
    int nextRadius{(int)(radius * percent)};
    if (nextRadius != currentRadius) {
      currentRadius = nextRadius;
      for (int x{}; x < canvas->getWidth(); x++) {
        for (int y{}; y < canvas->getHeight(); y++) {
          int xCentered{x - centerX};
          int yCentered{y - centerY};
          int distanceSquared{xCentered * xCentered + yCentered * yCentered};
          int squaredRadius{currentRadius * currentRadius};
          if ((distanceSquared > squaredRadius && this->shrink) ||
              (distanceSquared < squaredRadius && !this->shrink)) {
            canvas->setPixel(x, y, color);
          }
        }
      }
    }
  }
  ++loopCount;
  return 1000;
}

void Colors::CircleAnimationRenderer::teardown() { canvas->clear(); }
