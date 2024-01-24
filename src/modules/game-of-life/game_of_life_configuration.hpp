#pragma once

#include "../../common/models/color.hpp"

namespace GameOfLifeModule {
  class GameOfLifeConfiguration {
    public:

    int duration;
    Color color;
    bool generateColor;
    bool showHelp;

    GameOfLifeConfiguration();
  };
}