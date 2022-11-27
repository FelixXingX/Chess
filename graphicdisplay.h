#ifndef GRAPHIC_DIS_H
#define GRAPHIC_DIS_H
#include "observer.h"
class Board;
class Xwindow;

class GraphicsDisplay : public Observer{
	Board *subject;
	Xwindow *window;
	public:
		void notify();
}
