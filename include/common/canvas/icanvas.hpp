#pragma once

#include "common/models/color.hpp"
#include "common/models/colored_text.hpp"

#include <vector>

struct ICanvas {
  virtual void fill(Color c) = 0;
  virtual void clear() = 0;
  virtual void setPixel(int x, int y, Color c) = 0;
  virtual void drawLine(int x1, int y1, int x2, int y2, Color c) = 0;
  virtual void drawSquare(int x, int y, int w, int h, Color c,
                          bool filled = false) = 0;
  virtual void drawCircle(int x, int y, int r, Color c,
                          bool filled = false) = 0;

  virtual void drawText(std::vector<ColoredText> text, int x = 2) = 0;

  virtual int getWidth() const = 0;
  virtual int getHeight() const = 0;

  virtual rgb_matrix::Canvas *getCanvas() = 0;

  virtual ~ICanvas() {}

  std::string fontName{};
};
