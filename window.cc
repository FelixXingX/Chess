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
  char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 5; ++i) {
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
  int op;
  if(colour == 1){op = 0;}
  else{op = 1;}
  int align = scale/6;
  //top part
  //drawArc(x*scale + scale/2 - align + 5, y*scale + align+ 5, scale/2- 5, scale/2- 5, colour, 0 , 0);
  //drawArc(x*scale + scale/2 - align, y*scale + align, scale/2, scale/2, op, 0 , 0);
  //middle stick
  fillRectangle(x*scale + scale/2 - align + 10, y*scale + align+ 10 , scale/6 - 10, scale/2 - 10,colour);
  fillRectangle(x*scale + scale/2 - align , y*scale + align , scale/6 , scale/2 ,op);
  //base colour
  fillRectangle(x*scale + align + 10 ,y*scale + scale - scale /3 + 10 , scale/2 - 10, scale/6 - 10, colour);
  fillRectangle(x*scale + align,      y*scale + scale - scale /3      , scale/2,      scale/6, op);
}
void Xwindow::drawKing(int x, int y, int colour, int scale){}
void Xwindow::drawBishop(int x, int y, int colour, int scale){
  int op;
  if(colour == 1){op = 0;}
  else{op = 1;}
  int align = scale/30;
  //middle stick
  fillRectangle(x*scale + scale/2 - align , y*scale + align , scale/16 , scale/4 ,colour);
  fillRectangle(x*scale + scale/2 - align , y*scale + align , scale/16 , scale/4 ,op);
  //base colour
  fillRectangle(x*scale + align + 3 ,y*scale + scale - scale / 7 + 3 , scale/4 - 3, scale/16 - 3, colour);
  fillRectangle(x*scale + align , y*scale + scale - scale / 7, scale/4, scale/16, op);
}
void Xwindow::drawRook(int x, int y, int colour, int scale){

}
void Xwindow::drawQueen(int x, int y, int colour, int scale){}
void Xwindow::drawKnight(int x, int y, int colour, int scale){}