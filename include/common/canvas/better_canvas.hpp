#pragma once

#include "common/canvas/icanvas.hpp"
#include "common/models/color.hpp"
#include "common/models/colored_text.hpp"

#include "graphics.h"
#include "led-matrix.h"

class BetterCanvas : public ICanvas
{
public:
  BetterCanvas(int argc, char **argv, rgb_matrix::RGBMatrix::Options options);
  BetterCanvas(const BetterCanvas &canvas);

  BetterCanvas operator=(const BetterCanvas &canvas);

  void fill(Color c) override;
  void clear() override;
  void setPixel(int x, int y, Color c) override;
  void drawLine(int x1, int y1, int x2, int y2, Color c) override;
  void drawSquare(int x, int y, int w, int h, Color c,
                  bool filled = false) override;
  void drawCircle(int x, int y, int r, Color c, bool filled = false) override;

  void drawText(std::vector<ColoredText> text, int x = 2) override;

  rgb_matrix::Canvas *getCanvas() override;

  int getWidth() const override;
  int getHeight() const override;

  ~BetterCanvas();

private:
  rgb_matrix::RGBMatrix *canvas;

  rgb_matrix::Font *font;
  rgb_matrix::Font *getFont();
};
