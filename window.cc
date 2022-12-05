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

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::drawPawn(int x, int y, int colour, int scale){
  int op;
  if(colour == 1){op = 0;}
  else{op = 1;}
  int align = scale/30;
  fillRectangle(x*scale + align ,y*scale + align , scale/6 + 3 * align ,scale - scale/8 + 3 * align ,op);
  fillRectangle(x*scale + align ,y*scale + align , scale/1.4 + 3 * align ,scale - scale/2.2 + 3 * align,op);
  fillRectangle(x*scale + 2 * align , y*scale + 2 * align, scale/6, scale - scale/8, colour);
  fillRectangle(x*scale + 2 * align , y*scale + 2 * align, scale/1.4,scale - scale/2.2,colour);
  fillRectangle(x*scale + scale/3.75 ,y*scale + scale/6 , scale/3, scale - scale/1.4 + 5 ,op);
}
void Xwindow::drawKing(int x, int y, int colour, int scale){}
void Xwindow::drawBishop(int x, int y, int colour, int scale){
  int op;
  if(colour == 1){op = 0;}
  else{op = 1;}
  int align = scale/30;
  fillRectangle(x*scale + align ,y*scale + align , scale/1.5 + 3 * align ,scale - scale/8 + 3 * align,op);
  fillRectangle(x*scale + 2 * align , y*scale + 2 * align, scale/1.5, scale - scale/8, colour);
  fillRectangle(x*scale + align ,y*scale + align , scale/1.5 + 5 ,scale - scale/8 + 5 ,op);
  fillRectangle(x*scale + align ,y*scale + align , scale/1.5 + 5 ,scale - scale/8 + 5 ,op);
}
void Xwindow::drawRook(int x, int y, int colour, int scale){

}
void Xwindow::drawQueen(int x, int y, int colour, int scale){}
void Xwindow::drawKnight(int x, int y, int colour, int scale){}