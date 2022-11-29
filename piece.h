#ifndef PIECE_H_
#define PIECE_H_
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Piece{
	std::string color;
	char name;
	int col, row;
	public:
		std::string getColor();
		char getName();
};

class Knight : public Piece{
	public:
		Knight(char color,char name);
};

class Bishop : public Piece{
	public:
		Bishop(char color,char name);
};

class Rook : public Piece{
	bool castled;
	public:
		Rook(char color,char name);
		bool getCastle();
		void setCastle();
};

class King : public Piece{
	bool isChecked, castled;
	public:
		King(char color,char name);
		bool getStatusCheck();
		bool getStatusCastle();
		void setCheck();
		void setCastle();
};

class Queen : public Piece{
	public:
		Queen(char color,char name);
};

class Pawn : public Piece{
	bool firstStep;
	bool canPromote;
	public:
		Pawn(char color,char name);
		bool getFirstStep();
		void setFirstStep();
		void setCanPromote();
};
#endif
