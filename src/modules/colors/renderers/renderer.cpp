#include "modules/colors/renderers/renderer.hpp"
#include "common/canvas/icanvas.hpp"
#include "modules/colors/colors_configuration.hpp"

#include "CLI/CLI.hpp"

Colors::Renderer::Renderer(ICanvas *canvas, Colors::Configuration _config)
    : Module(canvas, "renderer",
             "A renderer, this text is not meant to be seen"),
      config{_config} {}

void Colors::Renderer::addFlags(CLI::App *app) {}
