#include "modules/game-of-life/game_of_life_module.hpp"
#include "common/models/fade_data.hpp"
#include "common/util/better_canvas.hpp"
#include "common/util/debug_log.hpp"
#include "modules/game-of-life/game_of_life_board.hpp"
#include "modules/game-of-life/game_of_life_configuration.hpp"

#include <algorithm>
#include <ctime>

GameOfLife::GOLModule::GOLModule(BetterCanvas *canvas)
    : Module(canvas, new GameOfLife::Configuration()), w{}, h{}, board{0, 0},
      changes{0, 0}, fadeData{} {
  this->name = "game-of-life";
  this->description = "Plays Connway's game of life on the screen";
}

void GameOfLife::GOLModule::setup() {
  srand((unsigned int)time(nullptr));

  canvas->clear();
  w = canvas->getWidth();
  h = canvas->getHeight();
  board = GOLBoard(w, h);
  changes = GOLBoard(w, h);
  fadeData = std::vector<FadeData>(w * h);

  if (getConfig()->generateColor) {
    srand(time(nullptr));
    int h{rand() % 360};
    Color c{Color::fromHSL(h, 1.0f, 0.5f)};
    getConfig()->color = c;
  }

  for (int x{}; x < w; x++) {
    for (int y{}; y < h; y++) {
      bool value{static_cast<bool>(rand() & 1)};
      board.set(x, y, value);

      canvas->setPixel(x, y, getConfig()->color);
    }
  }
}

long int GameOfLife::GOLModule::render() {
  GOLBoard next{w, h};
  for (int x{}; x < w; x++) {
    for (int y{}; y < h; y++) {
      bool value{board.get(x, y)};
      dLog(value, ' ');

      int aliveNeighbors{board.countNeighbours(x, y)};

      if (value && (aliveNeighbors < 2 || aliveNeighbors > 3)) {
        next.set(x, y, false);
      } else if (!value && aliveNeighbors == 3) {
        next.set(x, y, true);
      } else {
        next.set(x, y, value);
      }
    }
    dLog(' ');
  }
  dLog(' ');
  for (int x{}; x < w; x++) {
    for (int y{}; y < h; y++) {
      bool newVal{next.get(x, y)};
      if (newVal != board.get(x, y)) {
        board.set(x, y, newVal);
        if (!newVal) {
          fadeData.push_back({.x{x}, .y{y}, .fade{1.0f}});
        } else {
          canvas->setPixel(x, y, getConfig()->color);
        }
      }
    }
  }

  for (size_t i{}; i < fadeData.size(); i++) {
    if (getConfig()->fade) {
      fadeData[i].fade -= getConfig()->fadeSpeed;
    } else {
      fadeData[i].fade = 0.0f;
    }

    canvas->setPixel(fadeData[i].x, fadeData[i].y,
                     fadeData[i].fade < 0.05f
                         ? Color::black
                         : getConfig()->color * fadeData[i].fade);
  }

  // Remove fadeData
  fadeData.erase(
      std::remove_if(fadeData.begin(), fadeData.end(),
                     [](const FadeData &d) { return d.fade < 0.12f; }),
      fadeData.end());

  return getConfig()->duration * 1000;
}

void GameOfLife::GOLModule::teardown() {}

GameOfLife::GOLModule::~GOLModule() { teardown(); }

GameOfLife::Configuration *GameOfLife::GOLModule::getConfig() const {
  return static_cast<GameOfLife::Configuration *>(configuration);
}
