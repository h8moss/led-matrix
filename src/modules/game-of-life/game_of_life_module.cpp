#include "modules/game-of-life/game_of_life_module.hpp"
#include "common/util/better_canvas.hpp"
#include "modules/game-of-life/game_of_life_board.hpp"

#include <ctime>

GameOfLife::GOLModule::GOLModule(BetterCanvas *canvas)
    : Module(canvas), w{}, h{}, board{0, 0}, changes{0, 0} {}

void GameOfLife::GOLModule::setup() {
  srand((unsigned int)time(nullptr));

  canvas->clear();
  w = canvas->getWidth();
  h = canvas->getHeight();
  board = GOLBoard(w, h);
  changes = GOLBoard(w, h);

  for (int x{}; x < w; x++) {
    for (int y{}; y < h; y++) {
      bool value{static_cast<bool>(rand() & 1)};
      board.set(x, y, value);

      canvas->setPixel(x, y, configuration.color);
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
        Color c{board.get(x, y) ? configuration.color : Color::black};
        canvas->setPixel(x, y, c);
        changes.set(x, y, false);
      }
    }
  }

  return configuration.duration * 1000;
}

void GameOfLife::GOLModule::teardown() {
  // for (int x{}; x < w; x++) {
  //   delete[] board[x];
  //   delete[] boardChanges[x];
  // }
  //
  // delete[] board;
  // delete[] boardChanges;
  //
  // board = nullptr;
  // boardChanges = nullptr;
}

GameOfLife::GOLModule::~GOLModule() { teardown(); }
