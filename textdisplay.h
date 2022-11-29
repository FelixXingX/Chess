#ifndef TEXT_DIS_H
#define TEXT_DIS_H
#include "observer.h"
class Board;
class TextDisplay : public Observer{
	Board* subject;
	int cols, rows;
	std::string msg;
	public:
		void notify() override;
		TextDisplay(Board* subject, std::string msg);
		void changeMsg(std::string m);
};
#endif
