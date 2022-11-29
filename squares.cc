#include "squares.h"

//void Squares::setBoard(std::unique_ptr<Board> board){}
std::shared_ptr<Piece> Squares::getPiece() const{
    return piece;
}
//remove the piece by changing it nullptr
void Squares::removePiece(){
    piece = nullptr;
}
//add piece by removing its piece first, then copying piece to the ptr
void Squares::addPiece(std::shared_ptr<Piece> p){
    removePiece();
    piece = std::make_shared<Piece>(*p);
}
Squares::Squares(int col, int row, std::shared_ptr<Piece> piece) : col{col}, row{row}, piece{piece}{}
