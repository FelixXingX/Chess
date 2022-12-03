#ifndef GRAPHIC_DIS_H
#define GRAPHIC_DIS_H
#include "observer.h"
#include <memory>
class Board;
class Xwindow;

class GraphicsDisplay : public Observer{
	Board *subject;
	std::shared_ptr<Xwindow> window;

	int rows, cols, scale;
	public:
		GraphicsDisplay(Board *sj, std::shared_ptr<Xwindow> window, int rows, int cols, int scale);//ctor
		void notify() override; //renders the whole state
		void notify(int row, int col) override; // rendres only specific portions of the state
		void match(char a,int x, int y, int scale);
		//~GraphicsDisplay();
};

#endif