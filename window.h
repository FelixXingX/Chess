#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[11];

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;

  // Available colours.
  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Chocolate, Bisque};

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws an Arc
  void drawArc(int x, int y, int width, int height, int colour,int a1 ,int a2);
  
  // Draws a string
  void drawString(int x, int y, std::string msg);
	
  // Draws pieces
  void drawPawn(int x, int y, int colour, int scale);
  void drawKing(int x, int y, int colour, int scale);
  void drawBishop(int x, int y, int colour, int scale);
  void drawRook(int x, int y, int colour, int scale);
  void drawQueen(int x, int y, int colour, int scale);
  void drawKnight(int x, int y, int colour, int scale);

};

#endif
