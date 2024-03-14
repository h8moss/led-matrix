#include "modules/colors/renderers/corners_animation_renderer.hpp"

#include <cmath>

Colors::CornersAnimationRenderer::CornersAnimationRenderer(BetterCanvas *canvas)
    : currentColor{},
      totalDiagonals{},
      loopCount{},
      Module(canvas) {}

void Colors::CornersAnimationRenderer::setup()
{
  canvas->clear();
  currentColor = configuration.getColor();
  totalDiagonals = canvas->getWidth() * canvas->getHeight() - 1;
  loopCount = 0;
}

int Colors::CornersAnimationRenderer::render()
{
  int animationProgress = loopCount % ((int)(configuration.animationDuration + configuration.duration));

  if (animationProgress == 0)
  {
    canvas->fill(currentColor);
    currentColor = configuration.getColor();
  }

  if (animationProgress >= configuration.duration)
  {
    int delta{std::floor(totalDiagonals * ((float)animationProgress - configuration.duration) / (configuration.animationDuration))};
    for (int x{}; x <= delta; x++)
    {
      canvas->setPixel(x, delta - x - 1, currentColor);
    }
  }

  ++loopCount;
  return 1000;
}