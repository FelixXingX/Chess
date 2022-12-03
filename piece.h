#ifndef PIECE_H_
#define PIECE_H_
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
//Low coupling. Piece
//Note that for pieces, captial are white, lower case are black
class Piece{
	protected:
	std::string color;
	char name;
	int col, row;
	public:
		std::string getColor();
		char getName();
		Piece(std::string color,char name, int col, int row);
		virtual std::shared_ptr<Piece> clone() = 0; //We need to copy pieces with polymorhism so need a clone method
		virtual ~Piece() = default;
};

class Knight : public Piece{
	public:
		Knight(std::string color,char name, int col, int row);
		std::shared_ptr<Piece> clone() override;
};

class Bishop : public Piece{
	public:
		Bishop(std::string color,char name, int col, int row);
		std::shared_ptr<Piece> clone() override;
};

class Rook : public Piece{
	bool castled;
	public:
		Rook(std::string color,char name, int col, int row, bool castled);
		bool getCastle();
		void setCastle(bool set);
		std::shared_ptr<Piece> clone() override;
};

class King : public Piece{
	bool castled;
	public:
		King(std::string color,char name, int col, int row, bool castled);
		bool getStatusCheck();
		bool getStatusCastle();
		void setCheck(bool set);
		void setCastle(bool set);
		std::shared_ptr<Piece> clone() override;
};

class Queen : public Piece{
	public:
		Queen(std::string color,char name, int col, int row);
		std::shared_ptr<Piece> clone() override;
};

class Pawn : public Piece{
	bool firstStep;
	bool canPromote;
	public:
		Pawn(std::string color,char name, int col, int row, bool firstStep, bool canPromote);
		bool getFirstStep();
		bool getCanPromote();
		void setFirstStep(bool set);
		void setCanPromote(bool set);
		std::shared_ptr<Piece> clone() override;
};
#endif
