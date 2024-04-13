#pragma once
#include <string>
#include <vector>

namespace GameOfLife {
class GOLBoard {
public:
  GOLBoard(int _w, int _h);

  int w;
  int h;

  bool get(int x, int y);
  void set(int x, int y, bool value);
  void toggle(int x, int y);

  int countNeighbours(int x, int y);

  std::string getHash() const;

  ~GOLBoard();

private:
  std::vector<std::vector<bool>> board;
};
} // namespace GameOfLife
