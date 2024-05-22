#include "common/canvas/debug_canvas.hpp"

#include "common/util/debug_log.hpp"

void DebugCanvas::fill(Color c) { dLog("Canvas: fill " + c.string()); }
void DebugCanvas::clear() { dLog("Canvas: clear "); }

void DebugCanvas::setPixel(int x, int y, Color c) {
  dLog("Canvas: set pxl (" + std::to_string(x) + ", " + std::to_string(y) +
       ", " + c.string());
}

void DebugCanvas::drawLine(int x1, int y1, int x2, int y2, Color c) {
  dLog("Canvas: draw line " + c.string());
  dLog(std::to_string(x1) + "," + std::to_string(y1) + ":" +
       std::to_string(x2) + "," + std::to_string(y2));
}

void DebugCanvas::drawSquare(int x, int y, int w, int h, Color c, bool filled) {
  dLog("Canvas: draw square " + c.string() +
       " FILLED: " + std::to_string(filled));
  dLog(std::to_string(x) + "," + std::to_string(y) + ":" + std::to_string(w) +
       "," + std::to_string(h));
}

void DebugCanvas::drawCircle(int x, int y, int r, Color c, bool filled) {
  dLog("Canvas: draw circle " + c.string() +
       " FILLED: " + std::to_string(filled));
  dLog(std::to_string(x) + "," + std::to_string(y) + " " + std::to_string(r));
}

void DebugCanvas::drawText(std::vector<ColoredText> text, int x) {
  dLog("Canvas: draw text in " + std::to_string(x));
  for (auto c : text) {
    dLog(c.color.string());
    dLog(c.text);
  }
}

int DebugCanvas::getWidth() const { return 64; }

int DebugCanvas::getHeight() const { return 64; }
