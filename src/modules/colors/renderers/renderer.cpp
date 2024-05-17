#include "modules/colors/renderers/renderer.hpp"
#include "common/util/better_canvas.hpp"
#include "modules/colors/colors_configuration.hpp"

#include "CLI/CLI.hpp"

Colors::Renderer::Renderer(BetterCanvas *canvas, Colors::Configuration _config)
    : Module(canvas), config{_config} {}

void Colors::Renderer::addFlags(CLI::App *app) {}
