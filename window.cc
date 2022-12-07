#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[11][11]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "chocolate","tan"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 11; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);

  // Make sure we don't race against the Window being shown
  XEvent ev;
  while(1) {
    XNextEvent(d, &ev);
    if(ev.type == Expose) break;
  }
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}
void Xwindow::drawArc(int x, int y, int width, int height, int colour,int a1 ,int a2) {
  XSetForeground(d, gc, colours[colour]);
  XDrawArc(d, w, gc, x, y, width, height, a1, a2);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::drawPawn(int x, int y, int colour, int scale){
  int align = scale/6;

  //middle stick
  fillRectangle(x*scale + scale/2 - scale/12, y*scale + 2 * align, scale/6, scale/2, colour);
  //base colour
  fillRectangle(x*scale + 1.5 * align, y*scale + scale - scale /3, scale/2, scale/6, colour);
}
void Xwindow::drawKing(int x, int y, int colour, int scale){
  int align = scale/6;
  //cross part
  fillRectangle(x*scale + 1.5 * align, y*scale + scale/4, scale/2, scale/10, colour);
  //middle stick
  fillRectangle(x*scale + scale/2 - scale/12, y*scale +  align, scale/6, scale/1.8, colour);
  //base colour
  fillRectangle(x*scale + 1.5 * align, y*scale + scale - scale /3, 3 * align, scale/6, colour);
}
void Xwindow::drawBishop(int x, int y, int colour, int scale){
  int align = scale/6;
  //like the crown or smth
  fillRectangle(x*scale + 1.5 * align, y*scale +  align, scale/5, scale/6, colour);
  fillRectangle(x*scale + scale - 3 * align,   y*scale + align, scale/5, scale/6, colour);
  //head
  fillRectangle(x*scale + 1.5 * align, y*scale + 2 * align, scale/5, scale/6, colour);
  fillRectangle(x*scale + scale - 3 * align, y*scale +  2 * align, scale/5, scale/6, colour);
  //middle stick
  fillRectangle(x*scale + scale/2 - scale/12, y*scale + 2 * align, scale/6, scale/2, colour);
  //base colour
  fillRectangle(x*scale + 1.5 * align, y*scale + scale - scale /3, scale/2, scale/6, colour);
}
void Xwindow::drawRook(int x, int y, int colour, int scale){
  int align = scale/6;
  //middle stick
  fillRectangle(x*scale + align, y*scale + align, scale/6, scale/2, colour);
  fillRectangle(x*scale + scale/2 - scale/12, y*scale + align, scale/6, scale/2, colour);
  fillRectangle(x*scale + scale - 2* align, y*scale + align, scale/6, scale/2, colour);
  //base colour
  fillRectangle(x*scale + align , y*scale + 2 * align, scale/1.47, scale/2, colour);
}
void Xwindow::drawQueen(int x, int y, int colour, int scale){
  int align = scale/6;
  //spikes
  fillRectangle(x*scale + align, y*scale + 2 * align, scale/17, 3 * align, colour);
  fillRectangle(x*scale + 1.5 * align, y*scale + 1.8 * align, scale/17, 3.2 * align, colour);
  fillRectangle(x*scale + 2 * align, y*scale + 1.6 * align, scale/17, 3.4 * align, colour);
  fillRectangle(x*scale + 2.5 * align, y*scale + 1.4 * align, scale/17, 3.6 * align, colour);
  fillRectangle(x*scale + 3 *align, y*scale + 1 * align, scale/17, 4 * align, colour);
  fillRectangle(x*scale + 3.5 * align,y*scale + 1.4 * align, scale/17, 3.6 * align, colour);
  fillRectangle(x*scale + 4 * align, y*scale + 1.6 * align, scale/17, 3.4 * align, colour);
  fillRectangle(x*scale + 4.5 * align, y*scale + 1.8 * align, scale/17, 3.2 * align, colour);
  fillRectangle(x*scale + 5 * align, y*scale + 2 * align, scale/17, 3 * align, colour);
  //base
  fillRectangle(x*scale + align , y*scale + scale - 3* align, scale - 2 * align, 2 * align, colour);
}
void Xwindow::drawKnight(int x, int y, int colour, int scale){
  int align = scale/6;
  //base colour
  fillRectangle(x*scale + 1.5 * align, y*scale + scale - scale /3, scale/2, scale/6, colour);
  //torso part
  fillRectangle(x*scale + 2 *align, y*scale + scale /3, scale/3, scale/3, colour);
  //head?
  fillRectangle(x*scale + 2 *align, y*scale + scale /5, scale/4, scale/6, colour);
  
  //nose
  fillRectangle(x*scale + align, y*scale + scale /4, scale/2, scale/6, colour);
}