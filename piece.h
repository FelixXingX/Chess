#ifndef PIECE_H_
#define PIECE_H_
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Piece{
	string color;
	int col, row;
	std::string name;
	public:
		std::string getColor();
		std::string getName();
};

class Knight : public Piece{
	public:
		Knight(char color);
};

class Bishop : public Piece{
	public:
		Bishop(char color);
};

class Rook : public Piece{
	bool castled;
	public:
		Rook(char color);
		bool getCastle();
		void setCastle();
};

class King : public Piece{
	bool isChecked, castled;
	public:
		King(char color);
		bool getStatusCheck();
		bool getStatusCastle();
		void setCheck();
		void setCastle();
};

class Queen : public Piece{
	public:
		Queen(char color);
};

class Pawn : public Piece{
	bool firstStep;
	bool canPromote;
	public:
		Pawn(char color);
		bool getFirstStep();
		void setFirstStep();
		void setCanPromote();
};
#endif
