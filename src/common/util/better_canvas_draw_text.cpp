#include "common/models/colored_text.hpp"
#include "common/util/better_canvas.hpp"

#include "graphics.h"

void BetterCanvas::drawChar(char ch, Color c) {}

void BetterCanvas::drawText(std::vector<ColoredText> text) {
  rgb_matrix::Font font{};
  font.LoadFont("/usr/fonts");
  Color c{};
  for (ColoredText t : text) {
    c = t.color;
    for (char ch : t.text) {
    }
  }
}
