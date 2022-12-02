#include "piece.h"

#include <string>
using namespace std;
//Piece methods
string Piece::getColor(){ // something like this idk looool
    return color;
}

char Piece::getName() {  // something like this idk looool
    return name;
}
//king methods
bool King::getStatusCastle(){
    return castled;
}

void King::setCastle(bool set){
    castled = set;
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
bool Rook::getCastle(){
    return castled;
}

void Rook::setCastle(bool set){
    castled = set;
}
//All the ctors
Piece::Piece(string color, char name, int col, int row) : color{color}, name{name}, col{col}, row{row} {}
Knight::Knight(string color, char name, int col, int row) : Piece{color, name, col, row} {}
King::King(string color, char name, int col, int row, bool castled) : Piece{color, name, col, row}, castled{castled} {}
Bishop::Bishop(string color, char name, int col, int row) : Piece{color, name, col, row} {}
Queen::Queen(string color, char name, int col, int row) : Piece{color, name, col, row} {}
Rook::Rook(string color, char name, int col, int row, bool castled) : Piece{color, name, col, row}, castled{castled} {}
Pawn::Pawn(string color, char name, int col, int row, bool firstStep, bool canPromote) : Piece{color, name, col, row}, firstStep{firstStep}, canPromote{canPromote} {}
