#ifndef SQR_H_
#define SQR_H_
#include <memory>
class Squares{
	Board* board;
	int col, row;
	shared_ptr<Piece> piece;
	public:
		void setBoard(Board *board);
		shared_ptr<Piece> getPiece(int row, int col) const;
		void removePiece();
}
#endif
