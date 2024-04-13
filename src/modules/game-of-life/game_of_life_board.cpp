#include "modules/game-of-life/game_of_life_board.hpp"

#include <string>

GameOfLife::GOLBoard::GOLBoard(int _w, int _h) : w{_w}, h{_h} {
  board = std::vector<std::vector<bool>>(w);
  for (int i{}; i < w; i++) {
    board[i] = std::vector<bool>(h);
  }
}

bool GameOfLife::GOLBoard::get(int x, int y) { return board[x][y]; }

void GameOfLife::GOLBoard::set(int x, int y, bool value) {
  board[x][y] = value;
}

void GameOfLife::GOLBoard::toggle(int x, int y) { set(x, y, !get(x, y)); }

int GameOfLife::GOLBoard::countNeighbours(int x, int y) {
  int count{};

  for (int xDelta{-1}; xDelta <= 1; xDelta++) {
    for (int yDelta{-1}; yDelta <= 1; yDelta++) {
      if (xDelta == yDelta && xDelta == 0)
        continue;
      int currentX{x + xDelta};
      int currentY{y + yDelta};

      if (currentX < 0 || currentX >= w)
        continue;
      if (currentY < 0 || currentY >= h)
        continue;

      count += board[currentX][currentY];
    }
  }

  return count;
}

std::string GameOfLife::GOLBoard::getHash() const {
  std::string value{};

  for (int x{}; x < w; x++) {
    for (int y{}; x < h; x++) {
      value += board[x][y];
    }
  }

  return value;
}

GameOfLife::GOLBoard::~GOLBoard() {}
