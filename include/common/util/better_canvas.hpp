#pragma once

#include "led-matrix.h"
#include "common/models/color.hpp"

class BetterCanvas {
public:
	BetterCanvas(int argc, char** argv, rgb_matrix::RGBMatrix::Options options);

	void fill(Color c);
	void clear();
	void setPixel(int x, int y, Color c);
	void drawLine(int x1, int y1, int x2, int y2, Color c);
	void drawSquare(int x, int y, int w, int h, Color c, bool filled=false);
	void drawCircle(int x, int y, int r, Color c, bool filled=false);

	int getWidth() const;
	int getHeight() const;

	~BetterCanvas();

private:
	rgb_matrix::Canvas* canvas;
};