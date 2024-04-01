#include "modules/colors/renderers/renderer.hpp"
#include "common/util/better_canvas.hpp"
#include "modules/colors/colors_configuration.hpp"

Colors::Renderer::Renderer(BetterCanvas *canvas)
    : Module(canvas, new Colors::Configuration()) {}

Colors::Configuration *Colors::Renderer::getConfig() const {
  return static_cast<Colors::Configuration *>(configuration);
}
