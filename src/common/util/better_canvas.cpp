#include "common/util/better_canvas.hpp"
#include "led-matrix.h"

BetterCanvas::BetterCanvas(int argc, char** argv, rgb_matrix::RGBMatrix::Options options):
  canvas{nullptr}
{
  canvas = rgb_matrix::RGBMatrix::CreateFromFlags(&argc, &argv, &options);
}

void BetterCanvas::setPixel(int x, int y, Color c) {
    canvas->SetPixel(x, x, c.r, c.g, c.b);
}

void BetterCanvas::fill(Color c) {
  canvas->Fill(c.r, c.g, c.b);
}

void BetterCanvas::clear() {
  canvas->Clear();
}

void BetterCanvas::drawLine(int x1, int y1, int x2, int y2, Color c) {
    if (x1 > x2) {
        int temp{x2};
        x2 = x1;
        x1 = temp;
    }

    float m{(float)(y2-y1)/(float)(x2-x1)};
    for (int x{x1}; x<=x2; x++) {
        int y{(int)(m * (x-x1)+y1)};
        setPixel(x, y, c);
    }
}

void BetterCanvas::drawSquare(int x, int y, int w, int h, Color c, bool filled) {
    if (filled) {
        for (int deltaY{}; deltaY<h; deltaY++) {
            int currentY{y+deltaY};
            drawLine(x, currentY, x+w, currentY, c);
        }
    } else {
        drawLine(x, y, x+w, y, c);
        drawLine(x, y+h, x+w, y+h, c);
        drawLine(x, y, x, y+h, c);
        drawLine(x+w, y, x+w, y+h, c);
    }
}

void BetterCanvas::drawCircle(int x, int y, int r, Color c, bool filled) {
    for (int y0{-r}; y0<=r; y++) {
        for (int x0{-r}; x<=r; x++) {
            int distanceSqrd{x0*x0+y0*y0};
            if (filled && distanceSqrd < r*r+r ||
                !filled && distanceSqrd < r*r+r && distanceSqrd > r*r-r)
            {
                setPixel(x0, y0, c);    
            }
        }
    }
}

int BetterCanvas::getWidth() const { return canvas->width(); }
int BetterCanvas::getHeight() const { return canvas->height(); }