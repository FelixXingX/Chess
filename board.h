#ifndef BOARD_H_
#define BOARD_H_
#include <memory>
#include <vector>
#include <string>
#include "squares.h"
#include "textdisplay.h"
#include "subject.h"
class Player;
struct Vec {
    int row, col;
    Vec(int row, int col) : row{row}, col{col} {}
	bool operator <(const Vec &rhs) const{
		if(row == rhs.row){
			return col < rhs.col;
		}else{
			return row < rhs.row;
		}
	}
};
class Board : public Subject{
	std::vector<std::vector<Squares>> board;
	bool whiteCheck, blackCheck;
	std::string Won;
	//chicken nugget
	public:
		bool move(int fromX, int fromY, int toX, int toY, std::string turn, Player * player);
        bool Castle(int fromRow, int fromCol, int toRow, int toCol, std::string turn);
		bool isLegalMove(int fromX, int fromY, int toX, int toY, std::string turn);
        void addPiece(int row, int col, char name);
		void removePiece(int row, int col);
		char getState(int row, int col) const override;
		int getSquare(int row, int col);
		std::vector<std::vector<Squares>> getBoard();
		std::shared_ptr<Piece> getPiece(int row, int col);
		std::vector <Vec> possibleMoves(std::shared_ptr<Piece> piece, int row, int col);
		void render();
		void render(char type, int x, int y);
		Board(std::vector<std::vector<Squares>> board, bool whiteCheck,bool blackCheck,std::string Won);
		bool amIChecked(std::string turn);
		bool checked(std::string turn);
		bool botChecked(int x, int y, std::string turn);
		bool checkmate(std::string turn);
		//copy ctor
		Board(const Board &other);
		Board &operator = (const Board& other);
		std::string getWon();
};
#endif
