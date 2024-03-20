#include "modules/game-of-life/game_of_life_module.hpp"
#include "common/util/better_canvas.hpp"
#include "modules/game-of-life/game_of_life_board.hpp"

#include <ctime>
#include <random>

GameOfLife::GOLModule::GOLModule(BetterCanvas *canvas)
    : w{}, h{}, board{}, boardChanges{}, Module(canvas) {}

void GameOfLife::GOLModule::setup() {
  srand(time(nullptr));

  canvas->clear();
  w = canvas->getWidth();
  h = canvas->getHeight();
  board = GOLBoard();
  changes = GOLBoard();

  for (int x{}; x < w; x++) {
    for (int y{}; y < h; y++) {
      bool value{rand() & 1};
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

// TODO: I've been told that vectors can be used instead of pointers if we
// allocate the space beforehand

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
