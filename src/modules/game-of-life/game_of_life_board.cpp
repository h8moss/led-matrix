#include "modules/game-of-life/game_of_life_board.hpp"

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

int GameOfLife::GOLBoard::countNeighbours(int x, int y) {}
