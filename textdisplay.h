#ifndef TEXT_DIS_H
#define TEXT_DIS_H
#include "observer.h"
class Board;
class TextDisplay{
	Board* subject;
	int cols, rows;
	public:
		void notify();
};
#endif
