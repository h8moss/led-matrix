#pragma once

#include "common/canvas/icanvas.hpp"
#include "common/models/fade_data.hpp"
#include "modules/game-of-life/game_of_life_board.hpp"
#include "modules/game-of-life/game_of_life_configuration.hpp"
#include "modules/module.hpp"

#include <unordered_set>

namespace GameOfLife {
class GOLModule : public Module {
public:
  GOLModule(ICanvas *canvas);

  void setup() override;
  long int render() override;
  void teardown() override;

  void addFlags(CLI::App *app) override;

  ~GOLModule();

private:
  int w;
  int h;
  GOLBoard board;
  GOLBoard changes;

  std::vector<FadeData> fadeData;

  std::unordered_set<std::string> stateHashes;

  GameOfLife::Configuration config;
};
} // namespace GameOfLife
