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
		void move(int fromX, int fromY, int toX, int toY, std::string turn);
        //std::vector<Vec> possibleMoves(shared_ptr<Piece> piece, int row, int col, Board board);
        bool isLegalMove(int fromX, int fromY, int toX, int toY, std::string turn, bool inCheck);
        void addPiece(int row, int col, char name);
		char getState(int row, int col) const override;
		int getSquare(int row, int col);
		std::shared_ptr<Piece> getPiece(int row, int col);
		std::vector <Vec> possibleMoves(std::shared_ptr<Piece> piece, int row, int col);
		void render();
		Board(std::vector<std::vector<Squares>> board, bool whiteCheck,bool blackCheck,bool whiteCheckmate,bool blackCheckmate, bool stalemate);
		bool checked(string turn);
		bool checkmate(string turn);
		std::vector<Vec> possibleMoves2(std::shared_ptr<Piece> piece, int row, int col, std::vector<Vec> moves);
};
#endif
