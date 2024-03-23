#include "modules/game-of-life/game_of_life_module.hpp"
#include "common/util/better_canvas.hpp"
#include "modules/game-of-life/game_of_life_board.hpp"
#include "modules/game-of-life/game_of_life_configuration.hpp"

#include <ctime>
#include <random>

GameOfLife::GOLModule::GOLModule(BetterCanvas *canvas)
    : Module(canvas, new GameOfLife::Configuration()), w{}, h{}, board{0, 0},
      changes{0, 0} {
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

int GameOfLife::GOLModule::render() {
  for (int x{}; x < w; x++) {
    for (int y{}; y < h; y++) {
      bool value{board.get(x, y)};

      int aliveNeighbors{board.countNeighbours(x, y)};

      if (value && (aliveNeighbors < 2 || aliveNeighbors > 3)) {
        changes.set(x, y, true);
      } else if (!value && aliveNeighbors == 3) {
        changes.set(x, y, true);
      }
    }
  }

  for (int x{}; x < w; x++) {
    for (int y{}; y < h; y++) {
      if (changes.get(x, y)) {
        board.toggle(x, y);
        Color c{board.get(x, y) ? getConfig()->color : Color::black};
        canvas->setPixel(x, y, c);
        changes.set(x, y, false);
      }
    }
  }

  return getConfig()->duration * 1000;
}

void GameOfLife::GOLModule::teardown() {}

GameOfLife::GOLModule::~GOLModule() { teardown(); }

GameOfLife::Configuration *GameOfLife::GOLModule::getConfig() const {
  return static_cast<GameOfLife::Configuration *>(configuration);
}
