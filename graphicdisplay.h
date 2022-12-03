#ifndef GRAPHIC_DIS_H
#define GRAPHIC_DIS_H
#include "observer.h"
class Board;
class Xwindow;

class GraphicsDisplay : public Observer{
	Board *subject;
	Xwindow *window;

	int rows, cols, scale;
	public:
		GraphicsDisplay(Board *sj, Xwindow *window, int rows, int cols, int scale);//ctor
		void notify() override; //renders the whole state
		void notify(int row, int col) override; // rendres only specific portions of the state
		//~GraphicsDisplay();
};

#endif