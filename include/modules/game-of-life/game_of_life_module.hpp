#pragma once

#include "modules/game-of-life/game_of_life_board.hpp"
#include "modules/game-of-life/game_of_life_configuration.hpp"
#include "modules/module.hpp"

#include "common/models/fade_data.hpp"

#include <unordered_set>

namespace GameOfLife {
class GOLModule : public Module {
public:
  GOLModule(BetterCanvas *canvas);

  void setup() override;
  long int render() override;
  void teardown() override;

  GameOfLife::Configuration *getConfig() const;

  virtual void createConfiguration() override;

  ~GOLModule();

private:
  int w;
  int h;
  GOLBoard board;
  GOLBoard changes;

  std::vector<FadeData> fadeData;

  std::unordered_set<std::string> stateHashes;
};
} // namespace GameOfLife
