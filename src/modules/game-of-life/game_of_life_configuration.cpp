#include "modules/game-of-life/game_of_life_configuration.hpp"

GameOfLife::Configuration GameOfLife::Configuration::defaults = {
    .duration = 10,
    .color = {},
    .generateColor = true,
    .fade = false,
    .fadeSpeed = 0.1f,
    .onStagnation = StagnationBehaviour::reset};
