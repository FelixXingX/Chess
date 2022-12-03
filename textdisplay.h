#ifndef TEXT_DIS_H
#define TEXT_DIS_H
#include "observer.h"
class Board;
class TextDisplay : public Observer{
	Board* subject; //raw pointer to subject
	int cols, rows;
	std::string msg;
	public:
		void notify() override;
		void notify(int row, int col) override;
		void remove();
		TextDisplay(Board* subject, std::string msg);
		void changeMsg(std::string m);
};
#endif
