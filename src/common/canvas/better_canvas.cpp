#include "common/canvas/better_canvas.hpp"
#include "common/models/colored_text.hpp"

#include "graphics.h"
#include "led-matrix.h"

BetterCanvas::BetterCanvas(int argc, char **argv,
                           rgb_matrix::RGBMatrix::Options options)
    : canvas{nullptr} {
  canvas = rgb_matrix::RGBMatrix::CreateFromFlags(&argc, &argv, &options);
  if (canvas == nullptr) {
    throw "Error creating canvas!";
  }
}

BetterCanvas::BetterCanvas(const BetterCanvas &canvas) {
  this->canvas = canvas.canvas;
}

BetterCanvas BetterCanvas::operator=(const BetterCanvas &canvas1) {
  this->canvas = canvas1.canvas;
  this->fontName = canvas1.fontName;
}

BetterCanvas::~BetterCanvas() {
  if (this->canvas != nullptr) {
    delete this->canvas;
    this->canvas = nullptr;
  }

  if (font != nullptr) {
    delete font;
    font = nullptr;
  }
}

void BetterCanvas::setPixel(int x, int y, Color c) {
  canvas->SetPixel(x, y, (unsigned char)c.r, (unsigned char)c.g,
                   (unsigned char)c.b);
}

void BetterCanvas::fill(Color c) {
  canvas->Fill((unsigned char)c.r, (unsigned char)c.g, (unsigned char)c.b);
}

void BetterCanvas::clear() { canvas->Clear(); }

void BetterCanvas::drawLine(int x1, int y1, int x2, int y2, Color c) {
  if (x1 > x2) {
    int temp{x2};
    x2 = x1;
    x1 = temp;
  }

  float m{(float)(y2 - y1) / (float)(x2 - x1)};
  for (int x{x1}; x <= x2; x++) {
    int y{(int)(m * (x - x1) + y1)};
    setPixel(x, y, c);
  }
}

void BetterCanvas::drawSquare(int x, int y, int w, int h, Color c,
                              bool filled) {
  if (filled) {
    for (int deltaY{}; deltaY < h; deltaY++) {
      int currentY{y + deltaY};
      drawLine(x, currentY, x + w, currentY, c);
    }
  } else {
    drawLine(x, y, x + w, y, c);
    drawLine(x, y + h, x + w, y + h, c);
    drawLine(x, y, x, y + h, c);
    drawLine(x + w, y, x + w, y + h, c);
  }
}

void BetterCanvas::drawCircle(int x, int y, int r, Color c, bool filled) {
  for (int y0{-r}; y0 <= r; y0++) {
    for (int x0{-r}; x0 <= r; x0++) {
      int distanceSqrd{x0 * x0 + y0 * y0};
      if ((filled && distanceSqrd < r * r + r) ||
          (!filled && distanceSqrd < r * r + r && distanceSqrd > r * r - r)) {
        setPixel(x0 + x, y0 + y, c);
      }
    }
  }
}

rgb_matrix::Canvas *BetterCanvas::getCanvas() { return canvas; }

int BetterCanvas::getWidth() const { return canvas->width(); }
int BetterCanvas::getHeight() const { return canvas->height(); }

rgb_matrix::Font *BetterCanvas::getFont() {
  if (this->font == nullptr) {
#ifndef FONT_DIR

    throw "Missing font directory declaration, this should not happen, please "
          "contact developer!";
#endif

    if (fontName == "")
      throw "Missing font name";

    std::string fontLocation{FONT_DIR + fontName + ".bdf"};

    font = new rgb_matrix::Font();
    font->LoadFont(fontLocation.c_str());
  }

  return font;
}

void BetterCanvas::drawText(std::vector<ColoredText> text, int initialX) {
  rgb_matrix::Font *font{getFont()};
  Color c{};
  int x{initialX};
  int y{2 + font->height()};
  for (ColoredText t : text) {
    c = t.color;
    int len{x};
    for (char c : t.text) {
      len += font->CharacterWidth((unsigned int)c);
    }
    if (len > getWidth()) {
      y += 2 + font->height();
      x = initialX;
    }

    x += rgb_matrix::DrawText(canvas, *font, x, y, c.toRGBMatrixColor(),
                              nullptr, t.text.c_str());
  }
}
