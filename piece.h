#ifndef PIECE_H_
#define PIECE_H_
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//Note that for pieces, captial are white, lower case are black
class Piece{
	std::string color;
	char name;
	int col, row;
	public:
		std::string getColor();
		char getName();
		Piece(std::string color,char name, int col, int row);
};

class Knight : public Piece{
	public:
		Knight(std::string color,char name, int col, int row);
};

class Bishop : public Piece{
	public:
		Bishop(std::string color,char name, int col, int row);
};

class Rook : public Piece{
	bool castled;
	public:
		Rook(std::string color,char name, int col, int row);
		bool getCastle();
		void setCastle();
};

class King : public Piece{
	bool isChecked, castled;
	public:
		King(std::string color,char name, int col, int row);
		bool getStatusCheck();
		bool getStatusCastle();
		void setCheck();
		void setCastle();
};

class Queen : public Piece{
	public:
		Queen(std::string color,char name, int col, int row);
};

class Pawn : public Piece{
	bool firstStep;
	bool canPromote;
	public:
		Pawn(std::string color,char name, int col, int row);
		bool getFirstStep();
		void setFirstStep();
		void setCanPromote();
};
#endif
