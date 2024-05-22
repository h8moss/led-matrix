#pragma once

#include "common/canvas/icanvas.hpp"

class DebugCanvas : public ICanvas {

  void fill(Color c) override;
  void clear() override;
  void setPixel(int x, int y, Color c) override;
  void drawLine(int x1, int y1, int x2, int y2, Color c) override;
  void drawSquare(int x, int y, int w, int h, Color c,
                  bool filled = false) override;
  void drawCircle(int x, int y, int r, Color c, bool filled = false) override;

  void drawText(std::vector<ColoredText> text, int x = 2) override;

  int getWidth() const override;
  int getHeight() const override;
};
