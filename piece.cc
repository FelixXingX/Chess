#include "piece.h"
#include <string>
#include <memory>
using namespace std;
//Piece methods
string Piece::getColor(){ 
    return color;
}

char Piece::getName() {  
    return name;
}

bool Piece::getMoved() {  
    return moved;
}

void Piece::setMoved(bool move) {  // something like this idk looool
    moved = move;
}

//All the ctors
Piece::Piece(string color, char name, int col, int row, bool moved) : color{color}, name{name}, col{col}, row{row}, moved{moved} {}
Knight::Knight(string color, char name, int col, int row, bool moved) : Piece{color, name, col, row, moved} {}
King::King(string color, char name, int col, int row, bool moved) : Piece{color, name, col, row, moved} {}
Bishop::Bishop(string color, char name, int col, int row, bool moved) : Piece{color, name, col, row, moved} {}
Queen::Queen(string color, char name, int col, int row, bool moved) : Piece{color, name, col, row, moved} {}
Rook::Rook(string color, char name, int col, int row, bool moved) : Piece{color, name, col, row, moved} {}
Pawn::Pawn(string color, char name, int col, int row, bool moved) : Piece{color, name, col, row, moved} {}

//clone method to return copys
shared_ptr<Piece> Knight::clone(){return make_shared<Knight>(color, name, col, row, moved);}
shared_ptr<Piece> King::clone() { return make_shared<King>(color, name, col, row, moved); }
shared_ptr<Piece> Bishop::clone() { return make_shared<Bishop>(color, name, col, row, moved); }
shared_ptr<Piece> Queen::clone() { return make_shared<Queen>(color, name, col, row, moved); }
shared_ptr<Piece> Rook::clone() { return make_shared<Rook>(color, name, col, row, moved); }
shared_ptr<Piece> Pawn::clone() { return make_shared<Pawn>(color, name, col, row, moved); }
