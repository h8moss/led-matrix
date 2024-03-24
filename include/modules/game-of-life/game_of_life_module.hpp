#pragma once

#include "modules/game-of-life/game_of_life_board.hpp"
#include "modules/game-of-life/game_of_life_configuration.hpp"
#include "modules/module.hpp"

#include "common/models/fade_data.hpp"

namespace GameOfLife {
class GOLModule : public Module {
public:
  GOLModule(BetterCanvas *canvas);

  void setup() override;
  int render() override;
  void teardown() override;

  GameOfLife::Configuration *getConfig() const;

  ~GOLModule();

private:
  int w;
  int h;
  GOLBoard board;
  GOLBoard changes;

  std::vector<FadeData> fadeData;
};
} // namespace GameOfLife
