#include "textDrawer.hpp"

#include "drawLine.hpp"

TextDrawer::TextDrawer(Canvas *_canvas): canvas{_canvas} {};

int TextDrawer::drawChar(char c, int x, int y, Color color) const {
  switch (c) {
    case ' ':
    return 3;
    case 'a':
    return this->drawALower(x, y, color);
    case 'b':
    return this->drawBLower(x, y, color);
    case 'c':
    return this->drawCLower(x, y, color);
    case 'd':
    return this->drawDLower(x, y, color);
    case 'e':
    return this->drawELower(x, y, color);
    case 'f':
    return this->drawFLower(x, y, color);
    case 'g':
    return this->drawGLower(x, y, color);
    case 'h':
    return this->drawHLower(x, y, color);
    case 'i':
    return this->drawILower(x, y, color);
    case 'j':
    return this->drawJLower(x, y, color);
    case 'k':
    return this->drawKLower(x, y, color);
    case 'l':
    return this->drawLLower(x, y, color);
    case 'm':
    return this->drawMLower(x, y, color);
    case 'n':
    return this->drawNLower(x, y, color);
    case 'o':
    return this->drawOLower(x, y, color);
    case 'p':
    return this->drawPLower(x, y, color);
    case 'q':
    return this->drawQLower(x, y, color);
    case 'r':
    return this->drawRLower(x, y, color);
    case 's':
    return this->drawSLower(x, y, color);
    case 't':
    return this->drawTLower(x, y, color);
    case 'u':
    return this->drawULower(x, y, color);
    case 'v':
    return this->drawVLower(x, y, color);
    case 'w':
    return this->drawWLower(x, y, color);
    case 'x':
    return this->drawXLower(x, y, color);
    case 'y':
    return this->drawYLower(x, y, color);
    case 'z':
    return this->drawZLower(x, y, color);
    case 'A':
    return this->drawAUpper(x, y, color);
    case 'B':
    return this->drawBUpper(x, y, color);
    case 'C':
    return this->drawCUpper(x, y, color);
    case 'D':
    return this->drawDUpper(x, y, color);
    case 'E':
    return this->drawEUpper(x, y, color);
    case 'F':
    return this->drawFUpper(x, y, color);
    case 'G':
    return this->drawGUpper(x, y, color);
    case 'H':
    return this->drawHUpper(x, y, color);
    case 'I':
    return this->drawIUpper(x, y, color);
    case 'J':
    return this->drawJUpper(x, y, color);
    case 'K':
    return this->drawKUpper(x, y, color);
    case 'L':
    return this->drawLUpper(x, y, color);
    case 'M':
    return this->drawMUpper(x, y, color);
    case 'N':
    return this->drawNUpper(x, y, color);
    case 'O':
    return this->drawOUpper(x, y, color);
    case 'P':
    return this->drawPUpper(x, y, color);
    case 'Q':
    return this->drawQUpper(x, y, color);
    case 'R':
    return this->drawRUpper(x, y, color);
    case 'S':
    return this->drawSUpper(x, y, color);
    case 'T':
    return this->drawTUpper(x, y, color);
    case 'U':
    return this->drawUUpper(x, y, color);
    case 'V':
    return this->drawVUpper(x, y, color);
    case 'W':
    return this->drawWUpper(x, y, color);
    case 'X':
    return this->drawXUpper(x, y, color);
    case 'Y':
    return this->drawYUpper(x, y, color);
    case 'Z':
    return this->drawZUpper(x, y, color);
    case '0':
    return this->draw0(x, y, color);
    case '1':
    return this->draw1(x, y, color);
    case '2':
    return this->draw2(x, y, color);
    case '3':
    return this->draw3(x, y, color);
    case '4':
    return this->draw4(x, y, color);
    case '5':
    return this->draw5(x, y, color);
    case '6':
    return this->draw6(x, y, color);
    case '7':
    return this->draw7(x, y, color);
    case '8':
    return this->draw8(x, y, color);
    case '9':
    return this->draw9(x, y, color);
    case ':':
    return this->drawColon(x, y, color);
    case '?':
    return this->drawQuestion(x, y, color);
    case '.':
    return this->drawDot(x, y, color);
    case ',':
    return this->drawComma(x, y, color);
    case '+':
    return this->drawPlus(x,y,color);
    case '-':
    return this->drawMinus(x,y,color);
    case '=':
    return this->drawEquals(x,y,color);
    case '/':
    return this->drawSlash(x,y,color);
    case '(':
    return this->drawParenthesisLeft(x, y, color);
    case ')':
    return this->drawParenthesisRight(x, y, color);
    case '!':
    return this->drawExclamation(x, y, color);
  }
}

void TextDrawer::drawText(std::string text, int x, int y, Color c) const {
  for (char ch : text) {
    x+= drawChar(ch, x, y, c);
  }
}

int TextDrawer::draw0(int x, int y, Color c) const {
  drawLine(canvas, x, y, 2, c);
  drawLine(canvas, x, y+6, 2, c);
  
  drawLine(canvas, x, y, 5, c, false);
  drawLine(canvas, x+3, y, 5, c, false);

  return 5;
}

int TextDrawer::draw1(int x, int y, Color c) const {
  c.setCanvasPixel(x+1, y, canvas);
  c.setCanvasPixel(x+1, y+1, canvas);

  drawLine(canvas, x+2, y, 7, c, false);

  return 5;
}

int TextDrawer::draw2(int x, int y, Color c) const {
  drawLine(canvas, x, y, 3, c);
  drawLine(canvas, x+3, y+1, 3, c, false);
  drawLine(canvas, x, y+3, 3, c, false);
  drawLine(canvas, x+1, y+6, 3, c);
  
  c.setCanvasPixel(x+1, y+3, canvas);
  c.setCanvasPixel(x+2, y+3, canvas);

  return 5;
}

int TextDrawer::draw3(int x, int y, Color c) const {
  drawLine(canvas, x+1, y, 2, c);
  drawLine(canvas, x+1, y+3, 2, c);
  drawLine(canvas, x+1, y+6, 2, c);

  drawLine(canvas, x+3, y+1, 2, c, false);
  drawLine(canvas, x+3, y+4, 2, c, false);

  c.setCanvasPixel(x, y+1, canvas);
  c.setCanvasPixel(x, y+5, canvas);

  return 5;
}

int TextDrawer::draw4(int x, int y, Color c) const {
  drawLine(canvas, x, y, 3, c, false);
  drawLine(canvas, x+1, y+3, 2, c);
  drawLine(canvas, x+3, y, 7, c, false);

  return 5;
}

int TextDrawer::draw5(int x, int y, Color c) const {
  for (int i{}; i<3; i++) {
    c.setCanvasPixel(x+1+i, y, canvas);
    c.setCanvasPixel(x, y+1+i, canvas);
    c.setCanvasPixel(x+3, y+3+i, canvas);
    c.setCanvasPixel(x+i, y+6, canvas);
  }
  
  c.setCanvasPixel(x+1, y+3, canvas);
  c.setCanvasPixel(x+2, y+3, canvas);

  return 5;
}

int TextDrawer::draw6(int x, int y, Color c) const {

  for (int i{}; i<2; i++) {
    c.setCanvasPixel(x+1+i, y, canvas);
    c.setCanvasPixel(x, y+1+i, canvas);
    c.setCanvasPixel(x+1+i, y+3, canvas);
    c.setCanvasPixel(x, y+4+i, canvas);
    c.setCanvasPixel(x+3, y+4+i, canvas);
    c.setCanvasPixel(x+1+i, y+6, canvas);
  }
  c.setCanvasPixel(x, y+3, canvas);
  c.setCanvasPixel(x+3, y+1, canvas);

  return 5;
}

int TextDrawer::draw7(int x, int y, Color c) const {
  for (int i{}; i<3; i++)
    c.setCanvasPixel(x+i, y, canvas);

  for (int i{}; i<3; i++) {
    c.setCanvasPixel(x+3, y+1+i, canvas);
    c.setCanvasPixel(x+2, y+3+i, canvas);
    c.setCanvasPixel(x+1, y+5+i, canvas);
  }

  return 5;
}

int TextDrawer::draw8(int x, int y, Color c) const {
  draw3(x, y, c);
  c.setCanvasPixel(x, y+2, canvas);
  c.setCanvasPixel(x, y+4, canvas);
  return 5;
}

int TextDrawer::draw9(int x, int y, Color c) const {
  for (int i{}; i<2; i++) {
    c.setCanvasPixel(x+1+i, y, canvas);
    c.setCanvasPixel(x, y+1+i, canvas);
    c.setCanvasPixel(x+1+i, y+3, canvas);
  }

  for (int i{}; i<6; i++) 
    c.setCanvasPixel(x+3, y+1+i, canvas);
  

  return 5;
}

int TextDrawer::drawColon(int x, int y, Color c)  const {

  c.setCanvasPixel(x+1, y+2, canvas);
  c.setCanvasPixel(x+1, y+4, canvas);

  return 3;
}

int TextDrawer::drawALower(int x, int y, Color c) const  {
  for (int i{}; i<3; i++) {
    c.setCanvasPixel(x, y+3+i, canvas);
    c.setCanvasPixel(x+1+i, y+2, canvas);
    c.setCanvasPixel(x+4, y+3+i, canvas);
    c.setCanvasPixel(x+1+i, y+6, canvas);
  }
  c.setCanvasPixel(x+5, y+6, canvas);

  return 7;
}

int TextDrawer::drawBLower(int x, int y, Color c) const  {
  for (int i{}; i<3; i++) {
    c.setCanvasPixel(x, y+3+i, canvas);
    c.setCanvasPixel(x+1+i, y+2, canvas);
    c.setCanvasPixel(x+4, y+3+i, canvas);
    c.setCanvasPixel(x+1+i, y+6, canvas);
    c.setCanvasPixel(x, y+i, canvas);
  }

  return 6;
}

int TextDrawer::drawCLower(int x, int y, Color c) const  {
  for (int i{}; i<3; i++) {
    c.setCanvasPixel(x, y+3+i, canvas);
    c.setCanvasPixel(x+1+i, y+2, canvas);
    c.setCanvasPixel(x+1+i, y+6, canvas);
  }
  c.setCanvasPixel(x+4, y+3, canvas);
  c.setCanvasPixel(x+4, y+5, canvas);
}

int TextDrawer::drawDLower(int x, int y, Color c) const  {
  for (int i{}; i<3; i++) {
    c.setCanvasPixel(x, y+3+i, canvas);
    c.setCanvasPixel(x+1+i, y+2, canvas);
    c.setCanvasPixel(x+4, y+3+i, canvas);
    c.setCanvasPixel(x+1+i, y+6, canvas);
    c.setCanvasPixel(x+4, y+i, canvas);
  }
  return 6;
}

int TextDrawer::drawELower(int x, int y, Color c) const  {
  c.setCanvasPixel(x+1, y+6, canvas);
  c.setCanvasPixel(x+2, y+6, canvas);

  return drawCLower(x, y, c);
}

int TextDrawer::drawFLower(int x, int y, Color c) const  {
  for (int i{}; i<3; i++) {
    c.setCanvasPixel(x+1+i, y, canvas);
    c.setCanvasPixel(x, y+1+i, canvas);
    c.setCanvasPixel(x, y+4+i, canvas);
  }

  drawLine(canvas, x+1, y+3, 2, c);

  c.setCanvasPixel(x+4, y+1, canvas);

  return 6;
}

int TextDrawer::drawGLower(int x, int y, Color c) const  {
  drawLine(canvas, x, y+1, 2, c, false);
  drawLine(canvas, x+1, y, 3, c);
  drawLine(canvas, x+1, y+3, 3, c);
  drawLine(canvas, x+1, y+6, 3, c);
  drawLine(canvas, x+4, y+1, 5, c, false);
  c.setCanvasPixel(x, y+5, canvas);

  return 6;
}

int TextDrawer::drawHLower(int x, int y, Color c) const {
  drawLine(canvas, x, y, 7, c, false);
  drawLine(canvas, x+2, y+2, 2, c);
  drawLine(canvas, x+4, y+3, 4, c, false);

  c.setCanvasPixel(x+1, y+3, canvas);

  return 6;
}

int TextDrawer::drawILower(int x, int y, Color c) const {
  drawLine(canvas, x, y+2, 5, c, false);
  c.setCanvasPixel(x,y, canvas);
  
  return 2;
}

int TextDrawer::drawJLower(int x, int y, Color c) const {
  c.setCanvasPixel(x, y+5, canvas);
  drawLine(canvas, x+1, y+6, 2, c);
  drawLine(canvas, x+3, y+2, 4, c, false);

  return 5;
}

int TextDrawer::drawKLower(int x, int y, Color c) const {
  drawLine(canvas, x, y, 7, c, false);
  drawLine(canvas, x+2, y+3, 2, c);
  drawLine(canvas, x+2, y+5, 2, c);

  c.setCanvasPixel(x+1, y+4, canvas);
  c.setCanvasPixel(x+4, y+2, canvas);
  c.setCanvasPixel(x+4, y+6, canvas);

  return 6;
}

int TextDrawer::drawLLower(int x, int y, Color c) const {
  drawLine(canvas, x, y, 7, c, false);

  return 2;
}

int TextDrawer::drawMLower(int x, int y, Color c) const {
  drawLine(canvas, x, y+2, 5, c, false);
  drawLine(canvas, x+3, y+3, 4, c, false);
  drawLine(canvas, x+6, y+3, 4, c, false);

  drawLine(canvas, x+1, y+2, 2, c);
  drawLine(canvas, x+5, y+2, 2, c);

  return 8;
}

int TextDrawer::drawNLower(int x, int y, Color c) const {
  drawLine(canvas, x, y+2, 5, c, false);
  drawLine(canvas, x+4, y+3, 4, c, false);

  drawLine(canvas, x+1, y+2, 3, c);

  return 6;
}

int TextDrawer::drawOLower(int x, int y, Color c) const {
  drawLine(canvas, x+1, y+2, 3, c);
  drawLine(canvas, x+1, y+6, 3, c);

  drawLine(canvas, x, y+3, 3, c, false);
  drawLine(canvas, x+4, y+3, 3, c, false);

  return 6;
}

int TextDrawer::drawPLower(int x, int y, Color c) const {
  drawOLower(x, y-2, c);
  drawLine(canvas, x, y+4, 3, c, false);

  return 6;
}

int TextDrawer::drawQLower(int x, int y, Color c) const {
  drawOLower(x, y-2, c);
  drawLine(canvas, x+4, y+4, 3, c, false);

  return 6;
}

int TextDrawer::drawRLower(int x, int y, Color c) const {
  drawLine(canvas, x, y+3, 4, c, false);
  drawLine(canvas, x+1, y+2, 3, c);
  c.setCanvasPixel(x+4, y+3, canvas);

  return 6;
}

int TextDrawer::drawSLower(int x, int y, Color c) const {
  drawLine(canvas, x, y+6, 4, c);
  drawLine(canvas, x+1, y+2, 4, c);
  drawLine(canvas, x+1, y+4, 3, c);

  c.setCanvasPixel(x, y+3, canvas);
  c.setCanvasPixel(x+4, y+5, canvas);

  return 6;
}

int TextDrawer::drawTLower(int x, int y, Color c) const {
  drawLine(canvas, x+1, y, 6, c, false);
  drawLine(canvas, x, y+2, 5, c);
  drawLine(canvas, x+2, y+6, 3, c);

  c.setCanvasPixel(x+5, y+5, canvas);

  return 7;
}

int TextDrawer::drawULower(int x, int y, Color c) const {
  drawLine(canvas, x, y+2, 4, c, false);
  drawLine(canvas, x+4, y+2, 4, c, false);
  drawLine(canvas, x+1, y+6, 3, c);

  return 6;
}

int TextDrawer::drawVLower(int x, int y, Color c) const {
  drawLine(canvas, x, y+2, 2, c, false);
  drawLine(canvas, x+1, y+4, 2, c, false);
  drawLine(canvas, x+3, y+2, 2, c, false);
  drawLine(canvas, x+4, y+4, 2, c, false);

  c.setCanvasPixel(x+2, y+6, canvas);

  return 6;
}

int TextDrawer::drawWLower(int x, int y, Color c) const {
  drawLine(canvas, x, y+2, 4, c, false);
  drawLine(canvas, x+3, y+2, 4, c, false);
  drawLine(canvas, x+6, y+2, 4, c, false);
  drawLine(canvas, x+1, y+6, 2, c);
  drawLine(canvas, x+4, y+6, 2, c);

  return 8;
}

int TextDrawer::drawXLower(int x, int y, Color c) const {
  c.setCanvasPixel(x, y+2, canvas);
  c.setCanvasPixel(x+1, y+3, canvas);
  c.setCanvasPixel(x+2, y+4, canvas);
  c.setCanvasPixel(x+3, y+5, canvas);
  c.setCanvasPixel(x+4, y+6, canvas);

  c.setCanvasPixel(x, y+6, canvas);
  c.setCanvasPixel(x+1, y+5, canvas);
  c.setCanvasPixel(x+3, y+3, canvas);
  c.setCanvasPixel(x+4, y+2, canvas);

  return 6;
}

int TextDrawer::drawYLower(int x, int y, Color c) const {
  drawLine(canvas, x, y, 3, c, false);
  drawLine(canvas, x+1, y+3, 3, c);
  drawLine(canvas, x+1, y+6, 3, c);
  drawLine(canvas, x+4, y, 6, c, false);

  c.setCanvasPixel(x, y+5, canvas);

  return 6;
}

int TextDrawer::drawZLower(int x, int y, Color c) const {
  drawLine(canvas, x, y, 5, c);
  drawLine(canvas, x, y+4, 5, c);

  c.setCanvasPixel(x+3, y+1, canvas);
  c.setCanvasPixel(x+2, y+2, canvas);
  c.setCanvasPixel(x+1, y+3, canvas);

  return 6;
}

int TextDrawer::drawAUpper(int x, int y, Color c) const {
  return 0;
}

int TextDrawer::drawBUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawCUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawDUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawEUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawFUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawGUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawHUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawIUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawJUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawKUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawLUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawMUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawNUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawOUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawPUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawQUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawRUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawSUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawTUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawUUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawVUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawWUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawXUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawYUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawZUpper(int x, int y, Color c) const {
  
  return 0;
}

int TextDrawer::drawQuestion(int x, int y, Color c) const {return 0;}
int TextDrawer::drawDot(int x, int y, Color c) const {return 0;}
int TextDrawer::drawComma(int x, int y, Color c) const {return 0;}
int TextDrawer::drawPlus(int x, int y, Color c) const {return 0;}
int TextDrawer::drawMinus(int x, int y, Color c) const {return 0;}
int TextDrawer::drawEquals(int x, int y, Color c) const {return 0;}
int TextDrawer::drawSlash(int x, int y, Color c) const {return 0;}
int TextDrawer::drawParenthesisLeft(int x, int y, Color c) const {return 0;}
int TextDrawer::drawParenthesisRight(int x, int y, Color c) const {return 0;}
int TextDrawer::drawExclamation(int x, int y, Color c) const {return 0;}
