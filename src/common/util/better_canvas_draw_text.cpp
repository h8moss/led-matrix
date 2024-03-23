#include "common/models/colored_text.hpp"
#include "common/util/better_canvas.hpp"

#include "graphics.h"

void BetterCanvas::drawText(std::vector<ColoredText> text, int x) {
  rgb_matrix::Font *font{getFont()};
  Color c{};
  int y{2 + font->height()};
  for (ColoredText t : text) {
    c = t.color;
    int len{x};
    for (char c : t.text) {
      len += font->CharacterWidth((unsigned int)c);
    }
    if (len > getWidth()) {
      y += 2 + font->height();
    }

    x += rgb_matrix::DrawText(canvas, *font, x, y, c.toRGBMatrixColor(),
                              nullptr, t.text.c_str());
  }
}
