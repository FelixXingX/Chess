#ifndef BOARD_H_
#define BOARD_H_
#include <memory>
#include <vector>
#include <string>
#include "squares.h"
#include "textdisplay.h"
#include "subject.h"
class Vec;
class Board : public Subject{
	std::vector<std::vector<Squares>> board;
	bool whiteCheck, blackCheck, whiteCheckmate, blackCheckmate, stalemate;
	//chicken nugget
	public:
		void removePiece(int row, int col);
		void printMoves();
		void move(std::string from, std::string to, std::string turn);
        	//std::vector<Vec> possibleMoves(Piece piece, int row, int col, Board board);
        	bool canMove(int fromX, int fromY, int toX, int toY, std::string turn, Board board);
        	bool addPiece(int row, int col, std::shared_ptr<Piece>);
		char getState(int row, int col) const override;
		int getSquare(int row, int col);
		std::shared_ptr<Piece> getPiece(int row, int col);
		std::vector<Vec> possibleMoves(Piece piece, int row, int col, Board board);
		void render();
		Board(std::vector<std::vector<Squares>> board, bool whiteCheck,bool blackCheck,bool whiteCheckmate,bool blackCheckmate, bool stalemate);
};
#endif
