#include "drawText.hpp"

int drawZero(rgb_matrix::Canvas *canvas, int x, int y, Color color) {
  canvas->SetPixel(x+1, y, color.r, color.g, color.b);
  canvas->SetPixel(x+2, y, color.r, color.g, color.b);
  canvas->SetPixel(x+1, y+6, color.r, color.g, color.b);
  canvas->SetPixel(x+2, y+6, color.r, color.g, color.b);
  
  for (int i{1}; i<6; i++) {
    canvas->SetPixel(x, y+i, color.r, color.g, color.b);
    canvas->SetPixel(x+3, y+i, color.r, color.g, color.b);
  }

  return 5;
}

int drawOne(rgb_matrix::Canvas *canvas, int x, int y, Color color) {
  canvas->SetPixel(x+1, y, color.r, color.g, color.b);
  canvas->SetPixel(x, y+1, color.r, color.g, color.b);

  for (int i{}; i<7; i++) {
    canvas->SetPixel(x+2, y+i, color.r, color.g, color.b);
  }

  return 5;
}

int drawTwo(rgb_matrix::Canvas *canvas, int x, int y, Color color) {
  for (int i{}; i<3; i++) {
    canvas->SetPixel(x+i, y, color.r, color.g, color.b);
    canvas->SetPixel(x+3, y+1+i, color.r, color.g, color.b);
    canvas->SetPixel(x, y+3+i, color.r, color.g, color.b);
    canvas->SetPixel(x+1+i, y+6, color.r, color.g, color.b);
  }
  
  canvas->SetPixel(x+1, y+3, color.r, color.g, color.b);
  canvas->SetPixel(x+2, y+3, color.r, color.g, color.b);

  return 5;
}

int drawThree(rgb_matrix::Canvas *canvas, int x, int y, Color color) {
  for (int i{}; i<2; i++)  {
    canvas->SetPixel(x+1+i, y, color.r, color.g, color.b);
    canvas->SetPixel(x+1+i, y+3, color.r, color.g, color.b);
    canvas->SetPixel(x+1+i, y+6, color.r, color.g, color.b);

    canvas->SetPixel(x+3, y+1+i, color.r, color.g, color.b);
    canvas->SetPixel(x+3, y+4+i, color.r, color.g, color.b);
  }

  canvas->SetPixel(x, y+1, color.r, color.g, color.b);
  canvas->SetPixel(x, y+5, color.r, color.g, color.b);

  return 5;
}

int drawFour(rgb_matrix::Canvas *canvas, int x, int y, Color color) {

  for (int i{}; i<3; i++) 
    canvas->SetPixel(x, y+i, color.r, color.g, color.b);
  
  for (int i{}; i<2; i++)
    canvas->SetPixel(x+1+i, y+3, color.r, color.g, color.b);

  for (int i{}; i<7; i++)
    canvas->SetPixel(x+3, y+i, color.r, color.g, color.b);

  return 5;
}

int drawFive(rgb_matrix::Canvas *canvas, int x, int y, Color color) {
  for (int i{}; i<3; i++) {
    canvas->SetPixel(x+1+i, y, color.r, color.g, color.b);
    canvas->SetPixel(x, y+1+i, color.r, color.g, color.b);
    canvas->SetPixel(x+3, y+3+i, color.r, color.g, color.b);
    canvas->SetPixel(x+i, y+6, color.r, color.g, color.b);
  }
  
  canvas->SetPixel(x+1, y+3, color.r, color.g, color.b);
  canvas->SetPixel(x+2, y+3, color.r, color.g, color.b);

  return 5;
}

int drawSix(rgb_matrix::Canvas *canvas, int x, int y, Color color) {

  for (int i{}; i<2; i++) {
    canvas->SetPixel(x+1+i, y, color.r, color.g, color.b);
    canvas->SetPixel(x, y+1+i, color.r, color.g, color.b);
    canvas->SetPixel(x+1+i, y+3, color.r, color.g, color.b);
    canvas->SetPixel(x, y+4+i, color.r, color.g, color.b);
    canvas->SetPixel(x+3, y+4+i, color.r, color.g, color.b);
    canvas->SetPixel(x+1+i, y+6, color.r, color.g, color.b);
  }
  canvas->SetPixel(x, y+3, color.r, color.g, color.b);
  canvas->SetPixel(x+3, y+1, color.r, color.g, color.b);

  return 5;
}

int drawSeven(rgb_matrix::Canvas *canvas, int x, int y, Color color) {
  for (int i{}; i<3; i++)
    canvas->SetPixel(x+i, y, color.r, color.g, color.b);

  for (int i{}; i<3; i++) {
    canvas->SetPixel(x+3, y+1+i, color.r, color.g, color.b);
    canvas->SetPixel(x+2, y+3+i, color.r, color.g, color.b);
    canvas->SetPixel(x+1, y+5+i, color.r, color.g, color.b);
  }

  return 5;
}

int drawEight(rgb_matrix::Canvas *canvas, int x, int y, Color color) {
  drawThree(canvas, x, y, color);
  canvas->SetPixel(x, y+2, color.r, color.g, color.b);
  canvas->SetPixel(x, y+4, color.r, color.g, color.b);
  return 5;
}

int drawNine(rgb_matrix::Canvas *canvas, int x, int y, Color color) {
  for (int i{}; i<2; i++) {
    canvas->SetPixel(x+1+i, y, color.r, color.g, color.b);
    canvas->SetPixel(x, y+1+i, color.r, color.g, color.b);
    canvas->SetPixel(x+1+i, y+3, color.r, color.g, color.b);
  }

  for (int i{}; i<6; i++) 
    canvas->SetPixel(x+3, y+1+i, color.r, color.g, color.b);
  

  return 5;
}

int drawColon(rgb_matrix::Canvas *canvas, int x, int y, Color color) {

  canvas->SetPixel(x+1, y+2, color.r, color.g, color.b);
  canvas->SetPixel(x+1, y+4, color.r, color.g, color.b);

  return 3;
}

/// @brief WIP Draw text on screen, each character is 4x7 pixels, currently only digits are possible
/// @param canvas The canvas to draw on
/// @param x Starting x position
/// @param y Starting y position
/// @param text The text to draw
/// @param color Color of the text
void drawText(rgb_matrix::Canvas *canvas, int x, int y, std::string text, Color color) {
  for (char c : text) {
    if (c == '0') x+= drawZero(canvas, x, y, color);
    else if (c=='1') x+= drawOne(canvas, x, y, color);
    else if (c=='2') x+= drawTwo(canvas, x, y, color);
    else if (c=='3') x+= drawThree(canvas, x, y, color);
    else if (c=='4') x+= drawFour(canvas, x, y, color);
    else if (c=='5') x+= drawFive(canvas, x, y, color);
    else if (c=='6') x+= drawSix(canvas, x, y, color);
    else if (c=='7') x+= drawSeven(canvas, x, y, color);
    else if (c=='8') x+= drawEight(canvas, x, y, color);
    else if (c=='9') x+= drawNine(canvas, x, y, color);
    else if (c==':') x+= drawColon(canvas, x, y, color);
  }
}