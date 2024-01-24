#pragma once

#include "led-matrix.h"
#include "../models/color.hpp"

void drawLine(rgb_matrix::Canvas *canvas, int x, int y, int length, Color c, bool horizontal=true);