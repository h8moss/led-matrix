#include "common/models/colored_text.hpp"
#include "common/util/better_canvas.hpp"

#include "graphics.h"

void BetterCanvas::drawText(std::vector<ColoredText> text) {
  rgb_matrix::Font *font{getFont()};
  Color c{};
  int x{2};
  int y{2 + font->height()};
  for (ColoredText t : text) {
    c = t.color;

    x += rgb_matrix::DrawText(canvas, *font, x, y, c.toRGBMatrixColor(),
                              nullptr, t.text.c_str());
  }
}
