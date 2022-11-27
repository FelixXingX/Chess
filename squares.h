#ifndef SQR_H_
#define SQR_H_

#include "board.h"
#include "piece.h"


class Squares{
	Board* board;
	int col, row;
	std::shared_ptr<Piece> piece;
	public:
		void setBoard(Board *board);
		std::shared_ptr<Piece> getPiece(int row, int col) const;
		void removePiece();
};
#endif
