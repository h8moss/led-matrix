#include "drawLine.hpp"

void drawLine(rgb_matrix::Canvas *canvas, int x, int y, int length, Color c, bool horizontal) {
  bool vertical{!horizontal};
  for (int i{}; i<length; i++) 
    c.setCanvasPixel(x+i*horizontal, y+i*vertical, canvas);
}
