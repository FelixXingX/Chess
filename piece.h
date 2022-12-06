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
	bool moved;
	public:
		std::string getColor();
		char getName();
		bool getMoved();
		void setMoved(bool);
		Piece(std::string color,char name, int col, int row, bool moved);
		virtual std::shared_ptr<Piece> clone() = 0; //We need to copy pieces with polymorhism so need a clone method
		virtual ~Piece() = default;
};

class Knight : public Piece{
	public:
         Knight(std::string color, char name, int col, int row, bool moved);
         std::shared_ptr<Piece> clone() override;
};

class Bishop : public Piece{
	public:
         Bishop(std::string color, char name, int col, int row, bool moved);
         std::shared_ptr<Piece> clone() override;
};

class Rook : public Piece{
	public:
         Rook(std::string color, char name, int col, int row, bool moved);
         std::shared_ptr<Piece> clone() override;
};

class King : public Piece{
	public:
         King(std::string color, char name, int col, int row, bool moved);
         std::shared_ptr<Piece> clone() override;
         friend class Piece;
};

class Queen : public Piece{
	public:
         Queen(std::string color, char name, int col, int row, bool moved);
         std::shared_ptr<Piece> clone() override;
};

class Pawn : public Piece{
	public:
		Pawn(std::string color,char name, int col, int row, bool moved);
		std::shared_ptr<Piece> clone() override;
};
#endif
