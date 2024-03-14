#pragma once

#include "modules/module.hpp"
#include "modules/game-of-life/game_of_life_configuration.hpp"

namespace GameOfLife
{
  class GOLModule : public Module<GameOfLife::Configuration>
  {
  public:
    GOLModule(BetterCanvas *canvas);

    void setup() override;
    int render() override;
    void teardown() override;
  };
}