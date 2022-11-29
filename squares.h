#ifndef SQR_H_
#define SQR_H_

#include "piece.h"
#include <memory>
class Squares{
	//std::unique_ptr<Board> board;
	int col, row;
	std::shared_ptr<Piece> piece;
	public:
		//void setBoard(std::unique_ptr<Board> board);
		std::shared_ptr<Piece> getPiece() const;
		void removePiece();
		void addPiece(std::shared_ptr<Piece> p);
		Squares(int col, int row, std::shared_ptr<Piece> piece);
};
#endif
