#include "board.h"

#include <memory>
#include <string>
#include <vector>

#include "squares.h"
#include "textdisplay.h"

using namespace std;
bool Board::canMove(int row, int col){
    Piece piece = getPiece(col, col);
    string name = piece.getName();

}
struct Vec {
    int x, y;
    Vec(int x, int y) : x{x}, y{y} {}
};
// Important!! getSquare: 0 = false, 1 = true; 2 = out of bounds
int Board::getSquare(int row, int col){
    return 0;
}

Piece Board::getPiece(int row, int col){ // returns the piece on the square
    Piece piece;
    return piece;
}
// ALSO IMPORTANT (white pieces start at 0 and moves up the board) not sure if this is what we want
vector<Vec> Board::possibleMoves(Piece piece, int row, int col, Board board){ 
    vector<Vec> moves; // vector of pairs (x y)                                 
    string name = piece.getName();
    string color = piece.getColor();
    if (name == "pawn") {
        if (color == "white"){
            if (piece.firstStep == false){ // checks if its first step or not
                if (board.getSquare(col,row + 1) == 0) { // implement getSquare, returns if there is a piece at col col
                    moves.emplace_back(col, row + 1); // adds move to vector
                }
                if (board.getSquare(col + 1, row + 1) == 1 && board.getPiece(col + 1, row + 1).getColor() == "black") {  // checks if there is a capture available;
                    moves.emplace_back(col + 1, row + 1);
                }
                if (board.getSquare(col - 1, row + 1) == 1 && board.getPiece(col - 1, row + 1).getColor() == "black") {  // checks if there is a capture available;
                    moves.emplace_back(col - 1, row + 1);
                }
            } else if (piece.firstStep == 1){ // first move
                if (board.getSquare(col, row + 1) == 0) {
                    moves.emplace_back(col, row + 1);
                }
                if (board.getSquare(col, row + 2) == 0) {  //moves 2 steps if
                    moves.emplace_back(col, row + 2);
                }
            }
        } else if (color == "black") { // black pieces moves the other direction
            if (piece.firstStep == false) {                    
                if (board.getSquare(col, row - 1) == 0) {  
                    moves.emplace_back(col, row - 1);
                }
                if (board.getSquare(col + 1, row - 1) == 1 && board.getPiece(col + 1, row - 1).getColor() == "white") {  
                    moves.emplace_back(col + 1, row - 1);
                }
                if (board.getSquare(col - 1, row - 1) == 1 && board.getPiece(col - 1, row - 1).getColor() == "white") {  
                    moves.emplace_back(col - 1, row - 1);
                }
            } else if (piece.firstStep == true) {
                if (board.getSquare(col, row - 1) == 0) {
                    moves.emplace_back(col, row - 1);
                }
                if (board.getSquare(col, row - 2) == 0) {
                    moves.emplace_back(col, row - 2);
                }
            }
        }
    } else if (name == "knight") {
        if (board.getSquare(col + 1, row + 2) == 0) {  // i ordered the checks counter clockwise) hopefully i didnt fuck up lul
            moves.emplace_back(col + 1, row + 2);
        } else if (board.getSquare(col + 1, row + 2) == 1 && board.getPiece(col + 1, row + 2).getColor() != color) {  // checks if there is piece and not out of bounds + its capturable (enemy color)
            moves.emplace_back(col + 1, row + 2);
        }
        if (board.getSquare(col - 1, row + 2) == 0) {
            moves.emplace_back(col - 1, row + 2);
        } else if (board.getSquare(col + 1, row + 2) == 1 && board.getPiece(col - 1, row + 2).getColor() != color) {
            moves.emplace_back(col - 1, row + 2);
        }
        if (board.getSquare(col - 2, row + 1) == 0) {
            moves.emplace_back(col - 2, row + 1);
        } else if (board.getSquare(col + 1, row + 2) == 1 && board.getPiece(col - 2, row + 1).getColor() != color) {
            moves.emplace_back(col - 2, row + 1);
        }
        if (board.getSquare(col - 2, row - 1) == 0) {
            moves.emplace_back(col - 2, row - 1);
        } else if (board.getSquare(col + 1, row + 2) == 1 && board.getPiece(col - 2, row - 1).getColor() != color) {
            moves.emplace_back(col - 2, row - 1);
        }
        if (board.getSquare(col - 1, row - 2) == 0) {
            moves.emplace_back(col - 1, row - 2);
        } else if (board.getSquare(col + 1, row + 2) == 1 && board.getPiece(col - 1, row - 2).getColor() != color) {
            moves.emplace_back(col - 1, row - 2);
        }
        if (board.getSquare(col + 1, row - 2) == 0) {
            moves.emplace_back(col + 1, row - 2);
        } else if (board.getSquare(col + 1, row + 2) == 1 && board.getPiece(col + 1, row - 2).getColor() != color) {
            moves.emplace_back(col + 1, row - 2);
        }
        if (board.getSquare(col + 2, row - 1) == 0) {
            moves.emplace_back(col + 2, row - 1);
        } else if (board.getSquare(col + 1, row + 2) == 1 && board.getPiece(col + 2, row - 1).getColor() != color) {
            moves.emplace_back(col + 2, row - 1);
        }
        if (board.getSquare(col + 2, row + 1) == 0) {
            moves.emplace_back(col + 2, row + 1);
        } else if (board.getSquare(col + 1, row + 2) == 1 && board.getPiece(col + 2, row + 1).getColor() != color) {
            moves.emplace_back(col + 2, row + 1);
        }
    } else if (name == "rook") {
        for (int i = 1; i < 8 ; i++){ // moves up
            if (board.getSquare(col, row + i) == 2) {  // checks out of bounds
                break;
            }
            if (board.getSquare(col, row + i) == 0){ // empty square
                moves.emplace_back(col, row + i);
            } else if (board.getSquare(col, row + i) == 1 && board.getPiece(col, row + i).getColor() != color){ // capturable piece 
                moves.emplace_back(col, row + i);
                break;
            } else if (board.getSquare(col, row + i) == 1 && board.getPiece(col, row + i).getColor() == color) {  // uncapturable piece (ally)
                break;
            }
        }
        for (int i = 1; i < 8 ; i++) {   //moves down
            if (board.getSquare(col, row - i) == 2) { 
                break;
            }
            if (board.getSquare(col, row - i) == 0) { 
                moves.emplace_back(col, row - i);
            } else if (board.getSquare(col, row - i) == 1 && board.getPiece(col, row - i).getColor() != color) {  
                moves.emplace_back(col, row - i);
                break;
            } else if (board.getSquare(col, row - i) == 1 && board.getPiece(col, row - i).getColor() == color) {  
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves left
            if (board.getSquare(col - i, row) == 2) {
                break;
            }
            if (board.getSquare(col - i, row) == 0) {
                moves.emplace_back(col - i, row);
            } else if (board.getSquare(col - i, row) == 1 && board.getPiece(col - i, row).getColor() != color) {
                moves.emplace_back(col - i, row);
                break;
            } else if (board.getSquare(col - i, row) == 1 && board.getPiece(col - i, row).getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves right
            if (board.getSquare(col + i, row) == 2) {
                break;
            }
            if (board.getSquare(col + i, row) == 0) {
                moves.emplace_back(col + i, row);
            } else if (board.getSquare(col + i, row) == 1 && board.getPiece(col + i, row).getColor() != color) {
                moves.emplace_back(col + i, row);
                break;
            } else if (board.getSquare(col + i, row) == 1 && board.getPiece(col + i, row).getColor() == color) {
                break;
            }
        }
    } else if (name == "bishop") {
        for (int i = 1; i < 8; i++){ //moves top right
            if (board.getSquare(col + i, row + i) == 2) { // check out of bounds
                break;
            }
            if (board.getSquare(col + i, row + i) == 0) {
                moves.emplace_back(col + i, row + i); // empty square
            } else if (board.getSquare(col + i, row + i) == 1 && board.getPiece(col + i, row + i).getColor() != color) { //capturable piece
                moves.emplace_back(col + i, row + i);
                break;
            } else if (board.getSquare(col + i, row + i) == 1 && board.getPiece(col + i, row + i).getColor() == color) {  // uncapturable piece (ally)
                moves.emplace_back(col + i, row + i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {         // moves top left
            if (board.getSquare(col - i, row + i) == 2) {
                break;
            }
            if (board.getSquare(col - i, row + i) == 0) {
                moves.emplace_back(col - i, row + i);                                                                  
            } else if (board.getSquare(col - i, row + i) == 1 && board.getPiece(col - i, row + i).getColor() != color) { 
                moves.emplace_back(col - i, row + i);
                break;
            } else if (board.getSquare(col - i, row + i) == 1 && board.getPiece(col - i, row + i).getColor() == color) { 
                moves.emplace_back(col - i, row + i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves bottom left
            if (board.getSquare(col - i, row - i) == 2) {
                break;
            }
            if (board.getSquare(col - i, row - i) == 0) {
                moves.emplace_back(col - i, row - i);
            } else if (board.getSquare(col - i, row - i) == 1 && board.getPiece(col - i, row - i).getColor() != color) {
                moves.emplace_back(col - i, row - i);
                break;
            } else if (board.getSquare(col - i, row - i) == 1 && board.getPiece(col - i, row - i).getColor() == color) {
                moves.emplace_back(col - i, row - i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves bottom right
            if (board.getSquare(col + i, row - i) == 2) {
                break;
            }
            if (board.getSquare(col + i, row - i) == 0) {
                moves.emplace_back(col + i, row - i);
            } else if (board.getSquare(col + i, row - i) == 1 && board.getPiece(col + i, row - i).getColor() != color) {
                moves.emplace_back(col + i, row - i);
                break;
            } else if (board.getSquare(col + i, row - i) == 1 && board.getPiece(col + i, row - i).getColor() == color) {
                moves.emplace_back(col + i, row - i);
                break;
            }
        }
    } else if (name == "queen") { // ROOK + BISHOP
        for (int i = 1; i < 8; i++) {                      // moves top right
            if (board.getSquare(col + i, row + i) == 2) {  // check out of bounds
                break;
            }
            if (board.getSquare(col + i, row + i) == 0) {
                moves.emplace_back(col + i, row + i);                                                                   // empty square
            } else if (board.getSquare(col + i, row + i) == 1 && board.getPiece(col + i, row + i).getColor() != color) {  // capturable piece
                moves.emplace_back(col + i, row + i);
                break;
            } else if (board.getSquare(col + i, row + i) == 1 && board.getPiece(col + i, row + i).getColor() == color) {  // uncapturable piece (ally)
                moves.emplace_back(col + i, row + i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves top left
            if (board.getSquare(col - i, row + i) == 2) {
                break;
            }
            if (board.getSquare(col - i, row + i) == 0) {
                moves.emplace_back(col - i, row + i);
            } else if (board.getSquare(col - i, row + i) == 1 && board.getPiece(col - i, row + i).getColor() != color) {
                moves.emplace_back(col - i, row + i);
                break;
            } else if (board.getSquare(col - i, row + i) == 1 && board.getPiece(col - i, row + i).getColor() == color) {
                moves.emplace_back(col - i, row + i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves bottom left
            if (board.getSquare(col - i, row - i) == 2) {
                break;
            }
            if (board.getSquare(col - i, row - i) == 0) {
                moves.emplace_back(col - i, row - i);
            } else if (board.getSquare(col - i, row - i) == 1 && board.getPiece(col - i, row - i).getColor() != color) {
                moves.emplace_back(col - i, row - i);
                break;
            } else if (board.getSquare(col - i, row - i) == 1 && board.getPiece(col - i, row - i).getColor() == color) {
                moves.emplace_back(col - i, row - i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves bottom right
            if (board.getSquare(col + i, row - i) == 2) {
                break;
            }
            if (board.getSquare(col + i, row - i) == 0) {
                moves.emplace_back(col + i, row - i);
            } else if (board.getSquare(col + i, row - i) == 1 && board.getPiece(col + i, row - i).getColor() != color) {
                moves.emplace_back(col + i, row - i);
                break;
            } else if (board.getSquare(col + i, row - i) == 1 && board.getPiece(col + i, row - i).getColor() == color) {
                moves.emplace_back(col + i, row - i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {                  // moves up
            if (board.getSquare(col, row + i) == 2) {  // checks out of bounds
                break;
            }
            if (board.getSquare(col, row + i) == 0) {  // empty square
                moves.emplace_back(col, row + i);
            } else if (board.getSquare(col, row + i) == 1 && board.getPiece(col, row + i).getColor() != color) {  // capturable piece
                moves.emplace_back(col, row + i);
                break;
            } else if (board.getSquare(col, row + i) == 1 && board.getPiece(col, row + i).getColor() == color) {  // uncapturable piece (ally)
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves down
            if (board.getSquare(col, row - i) == 2) {
                break;
            }
            if (board.getSquare(col, row - i) == 0) {
                moves.emplace_back(col, row - i);
            } else if (board.getSquare(col, row - i) == 1 && board.getPiece(col, row - i).getColor() != color) {
                moves.emplace_back(col, row - i);
                break;
            } else if (board.getSquare(col, row - i) == 1 && board.getPiece(col, row - i).getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves left
            if (board.getSquare(col - i, row) == 2) {
                break;
            }
            if (board.getSquare(col - i, row) == 0) {
                moves.emplace_back(col - i, row);
            } else if (board.getSquare(col - i, row) == 1 && board.getPiece(col - i, row).getColor() != color) {
                moves.emplace_back(col - i, row);
                break;
            } else if (board.getSquare(col - i, row) == 1 && board.getPiece(col - i, row).getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves right
            if (board.getSquare(col + i, row) == 2) {
                break;
            }
            if (board.getSquare(col + i, row) == 0) {
                moves.emplace_back(col + i, row);
            } else if (board.getSquare(col + i, row) == 1 && board.getPiece(col + i, row).getColor() != color) {
                moves.emplace_back(col + i, row);
                break;
            } else if (board.getSquare(col + i, row) == 1 && board.getPiece(col + i, row).getColor() == color) {
                break;
            }
        }
    } else if (name == "king") { //checks in order of clockwise
        if (board.getSquare(col, row + 1) != 2 && ){ // in bounds and check if king will be checked or not
            if (board.getSquare(col, row + 1) == 0) {  // empty square
                moves.emplace_back(col, row + 1);
            } else if (board.getSquare(col, row + 1) == 1 && board.getPiece(col, row + 1).getColor() != color) {  // capturable piece
                moves.emplace_back(col, row + 1);
            }
        }
        if (board.getSquare(col + 1, row + 1) != 2 &&) {   //implement if king will be in check
            if (board.getSquare(col + 1, row + 1) == 0) { 
                moves.emplace_back(col + 1, row + 1);
            } else if (board.getSquare(col + 1, row + 1) == 1 && board.getPiece(col + 1, row + 1).getColor() != color) { 
                moves.emplace_back(col + 1, row + 1);
            }
        }
        if (board.getSquare(col + 1, row) != 2 &&) {  // implement if king will be in check
            if (board.getSquare(col + 1, row) == 0) {
                moves.emplace_back(col + 1, row);
            } else if (board.getSquare(col + 1, row ) == 1 && board.getPiece(col + 1, row).getColor() != color) {
                moves.emplace_back(col + 1, row);
            }
        }
        if (board.getSquare(col + 1, row - 1) != 2 &&) {  // implement if king will be in check
            if (board.getSquare(col + 1, row - 1) == 0) {
                moves.emplace_back(col + 1, row - 1);
            } else if (board.getSquare(col + 1, row - 1) == 1 && board.getPiece(col + 1, row - 1).getColor() != color) {
                moves.emplace_back(col + 1, row - 1);
            }
        }
        if (board.getSquare(col, row - 1) != 2 &&) {  // implement if king will be in check
            if (board.getSquare(col, row - 1) == 0) {
                moves.emplace_back(col, row - 1);
            } else if (board.getSquare(col, row - 1) == 1 && board.getPiece(col, row - 1).getColor() != color) {
                moves.emplace_back(col, row - 1);
            }
        }
        if (board.getSquare(col - 1, row - 1) != 2 &&) {  // implement if king will be in check
            if (board.getSquare(col - 1, row - 1) == 0) {
                moves.emplace_back(col - 1, row - 1);
            } else if (board.getSquare(col - 1, row - 1) == 1 && board.getPiece(col - 1, row - 1).getColor() != color) {
                moves.emplace_back(col - 1, row - 1);
            }
        }
        if (board.getSquare(col - 1, row) != 2 &&) {  // implement if king will be in check
            if (board.getSquare(col - 1, row) == 0) {
                moves.emplace_back(col - 1, row);
            } else if (board.getSquare(col - 1, row) == 1 && board.getPiece(col - 1, row).getColor() != color) {
                moves.emplace_back(col - 1, row);
            }
        }
        if (board.getSquare(col - 1, row + 1) != 2 &&) {  // implement if king will be in check
            if (board.getSquare(col - 1, row + 1) == 0) {
                moves.emplace_back(col - 1, row + 1);
            } else if (board.getSquare(col - 1, row + 1) == 1 && board.getPiece(col - 1, row + 1).getColor() != color) {
                moves.emplace_back(col - 1, row + 1);
            }
        }
    }
}