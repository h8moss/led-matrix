#pragma once

#include "common/models/color.hpp"
#include "common/models/colored_text.hpp"

#include "graphics.h"
#include "led-matrix.h"

class BetterCanvas {
public:
  BetterCanvas(int argc, char **argv, rgb_matrix::RGBMatrix::Options options);
  BetterCanvas(const BetterCanvas &canvas);

  BetterCanvas operator=(const BetterCanvas &canvas);

  void fill(Color c);
  void clear();
  void setPixel(int x, int y, Color c);
  void drawLine(int x1, int y1, int x2, int y2, Color c);
  void drawSquare(int x, int y, int w, int h, Color c, bool filled = false);
  void drawCircle(int x, int y, int r, Color c, bool filled = false);

  void drawText(std::vector<ColoredText> text);
  void drawChar(char ch, Color c);

  int getWidth() const;
  int getHeight() const;

  ~BetterCanvas();

private:
  rgb_matrix::Canvas *canvas;

  rgb_matrix::Font *font;

  rgb_matrix::Font *getFont();
};
