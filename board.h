#ifndef BOARD_H_
#define BOARD_H_
#include <memory>
#include <vector>
#include "squares.h"
#include "textdisplay.h"


class Board{
	std::vector<std::vector<Squares>> board;
	bool whiteCheck, blackCheck, whiteCheckmate, blackCheckmate, stalemate;
	TextDisplay *textDisplay;
	//chicken nugget
	public:
		void removePiece(int row, int col);
		void printMoves();
		void move(std::string from, std::string to, std::string turn);
		std::vector<Vec> possibleMoves(Piece piece, int row, int col, Board board);
		bool canMove(int row, int col);
		bool addPiece(int row, int col, std::shared_ptr<Piece>);
		std::string getState(int row, int col);
		int getSquare(int row, int col);
		Piece getPiece(int row, int col);
};
#endif
