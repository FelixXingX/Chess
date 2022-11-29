#include "piece.h"

#include <string>
using namespace std;
string Piece::getColor(){ // something like this idk looool
    return color;
}

char Piece::getName() {  // something like this idk looool
    return name;
}

bool Pawn::getFirstStep(){
    return firstStep;
}

Piece::Piece(string color,char name, int col, int row): color{color}, name{name}, col{col}, row{row}{}
Knight::Knight(string color,char name, int col, int row): Piece{color, name, col, row}{}
King::King(string color,char name, int col, int row): Piece{color, name, col, row}{}
Bishop::Bishop(string color,char name, int col, int row): Piece{color, name, col, row}{}
Queen::Queen(string color,char name, int col, int row): Piece{color, name, col, row}{}
Rook::Rook(string color,char name, int col, int row): Piece{color, name, col, row}{}
