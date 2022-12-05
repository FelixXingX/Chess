#include "piece.h"
#include <string>
#include <memory>
using namespace std;
//Piece methods
string Piece::getColor(){ // something like this idk looool
    return color;
}

char Piece::getName() {  // something like this idk looool
    return name;
}
//king methods
bool King::getStatusMoved(){
    return moved;
}

void King::setMoved(bool set){
    moved = set;
}

//Pawn methods
bool Pawn::getFirstStep(){
    return firstStep;
}

bool Pawn::getCanPromote(){
    return canPromote;
}

void Pawn::setCanPromote(bool set){
    canPromote = set;
}

void Pawn::setFirstStep(bool set){
    firstStep = set;
}

//Rook methods
bool Rook::getMoved(){
    return moved;
}

void Rook::setMoved(bool set){
    moved = set;
}
//All the ctors
Piece::Piece(string color, char name, int col, int row) : color{color}, name{name}, col{col}, row{row} {}
Knight::Knight(string color, char name, int col, int row) : Piece{color, name, col, row} {}
King::King(string color, char name, int col, int row, bool castled) : Piece{color, name, col, row}, moved{moved} {}
Bishop::Bishop(string color, char name, int col, int row) : Piece{color, name, col, row} {}
Queen::Queen(string color, char name, int col, int row) : Piece{color, name, col, row} {}
Rook::Rook(string color, char name, int col, int row, bool castled) : Piece{color, name, col, row}, moved{moved} {}
Pawn::Pawn(string color, char name, int col, int row, bool firstStep, bool canPromote) : Piece{color, name, col, row}, firstStep{firstStep}, canPromote{canPromote} {}

//clone method to return copys
shared_ptr<Piece> Knight::clone(){return make_shared<Knight>(color, name, col, row);}
shared_ptr<Piece> King::clone(){return make_shared<King>(color, name, col, row,moved);}
shared_ptr<Piece> Bishop::clone(){return make_shared<Bishop>(color, name, col, row);}
shared_ptr<Piece> Queen::clone(){return make_shared<Queen>(color, name, col, row);}
shared_ptr<Piece> Rook::clone(){return make_shared<Rook>(color, name, col, row,moved);}
shared_ptr<Piece> Pawn::clone(){return make_shared<Pawn>(color, name, col, row,firstStep,canPromote);}
