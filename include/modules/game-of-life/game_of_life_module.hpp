#pragma once

#include "modules/game-of-life/game_of_life_board.hpp"
#include "modules/game-of-life/game_of_life_configuration.hpp"
#include "modules/module.hpp"

#include "common/models/fade_data.hpp"

#include <map>

namespace GameOfLife {
class GOLModule : public Module {
public:
  GOLModule(BetterCanvas *canvas);

  void setup() override;
  long int render() override;
  void teardown() override;

  GameOfLife::Configuration *getConfig() const;

  ~GOLModule();

private:
  int w;
  int h;
  GOLBoard board;
  GOLBoard changes;

  std::vector<FadeData> fadeData;

  std::map<long int, int> stateHashes;
};
} // namespace GameOfLife
