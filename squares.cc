#include "squares.h"

void Squares::setBoard(std::unique_ptr<Board> board){}
std::shared_ptr<Piece> Squares::getPiece(int row, int col) const{}
//piece will be null ptr. Since piece is a unique ptr, it should automatically delete the piece object before
void Squares::removePiece(){
    piece = nullptr;
}