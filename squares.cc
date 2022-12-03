#include "squares.h"

//void Squares::setBoard(std::unique_ptr<Board> board){}
std::shared_ptr<Piece> Squares::getPiece() const{
    return piece;
}
//remove the piece by changing it nullptr
void Squares::removePiece(){
    if(piece) piece = nullptr;
}
//add piece by removing its piece first, then copying piece to the ptr
void Squares::addPiece(std::shared_ptr<Piece> p){
    removePiece();
    piece = p;
}
Squares::Squares(int col, int row, std::shared_ptr<Piece> piece) : col{col}, row{row}, piece{piece}{}

Squares::Squares(const Squares& other) : col{other.col}, row{other.row}, piece{other.piece != nullptr? other.piece->clone() : nullptr}{}

Squares &Squares::operator=(const Squares &other){
    if(this == &other) return *this;
    std::shared_ptr<Piece> tmp = piece;
    piece = (other.piece)? other.piece->clone(): nullptr;
    col = other.col;
    row = other.row;
    return *this;
}
