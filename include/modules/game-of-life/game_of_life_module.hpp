#pragma once

#include "modules/game-of-life/game_of_life_board.hpp"
#include "modules/module.hpp"

namespace GameOfLife {
class GOLModule : public Module {
public:
  GOLModule(BetterCanvas *canvas);

  void setup() override;
  int render() override;
  void teardown() override;

  ~GOLModule();

private:
  int w;
  int h;
  GOLBoard board;
  GOLBoard changes;
};
} // namespace GameOfLife
