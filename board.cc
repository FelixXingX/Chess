#include "board.h"

#include <string>

#include "squares.h"
#include "textdisplay.h"
using namespace std;
//note: col = x, row = y
struct Vec {
    int x, y;
    Vec(int x, int y) : x{x}, y{y} {}
};
//ctor
Board::Board(vector<vector<Squares>> board, bool whiteCheck, bool blackCheck,bool whiteCheckmate,bool blackCheckmate, bool stalemate):
board{board},whiteCheck{whiteCheck},blackCheck{blackCheck},whiteCheckmate{whiteCheckmate},blackCheckmate{blackCheckmate},stalemate{stalemate}{}

// Important!! getSquare: 0 = no piece, 1 = theres a piece; 2 = out of bounds
int Board::getSquare(int col, int row){
    if (col > 7 || row > 7) {
        return 2;
    }
    for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            auto p = board[col][row].getPiece();
            if (p != nullptr) {
                return 1;
            }
        }
    }
    return 0;
}
//GetState get the char or string of the name of the piece
//Observer pattern just ignore frfr
char Board::getState(int row, int col) const{
    auto p = board[row][col].getPiece();
    if(p == nullptr){
        if(row % 2 == 0){
            if(col % 2 == 0){
                return '_';
            }else{
                return ' ';
            }
        }else{
            if(col % 2 == 0){
                return ' ';
            }else {
                return '_';
            }
        }
    }else{
        return p->getName();
    }
}
//invariant we are assuming board goes from 8 to 1
shared_ptr<Piece> Board::getPiece(int row, int col){ // returns the piece on the square 
	for(int i = 8; i > 1; --i){
        	for(int j = 1; j < 8; ++j){
            		if(i == row && j == col){
                		return board[i][j].getPiece();
            		}
        	}
    }
    return nullptr;
}

void Board::addPiece(int row, int col, char name){
    switch(name){
        case 'p':
            {shared_ptr<Piece> p = make_shared<Pawn>("black", name, row,col, true, false);
            board[row][col].addPiece(p);
            break;}
        case 'P':
            {shared_ptr<Piece> p = make_shared<Pawn>("white", name, row,col,true, false);
            board[row][col].addPiece(p);
            break;}
        case 'r':
            {shared_ptr<Piece> p = make_shared<Rook>("black", name, row,col,false);
            board[row][col].addPiece(p);
            break;}
        case 'R':
            {shared_ptr<Piece> p = make_shared<Rook>("white", name, row,col,false);
            board[row][col].addPiece(p);
            break;}
        case 'n':
            {shared_ptr<Piece> p = make_shared<Knight>("black", name, row,col);
            board[row][col].addPiece(p);
            break;}
        case 'N':
            {shared_ptr<Piece> p = make_shared<Knight>("white", name, row,col);
            board[row][col].addPiece(p);
            break;}
        case 'b':
            {shared_ptr<Piece> p = make_shared<Bishop>("black", name, row,col);
            board[row][col].addPiece(p);
            break;}
        case 'B':
            {shared_ptr<Piece> p = make_shared<Bishop>("white", name, row,col);
            board[row][col].addPiece(p);
            break;}
        case 'q':
            {shared_ptr<Piece> p = make_shared<Queen>("black", name, row,col);
            board[row][col].addPiece(p);
            break;}
        case 'Q':
            {shared_ptr<Piece> p = make_shared<Queen>("white", name, row,col);
            board[row][col].addPiece(p);
            break;}
        case 'k':
            {shared_ptr<Piece>p = make_shared<King>("black", name, row,col,false,false);
            board[row][col].addPiece(p);
            break;}
        case 'K':
            {shared_ptr<Piece> p = make_shared<King>("white", name, row,col,false,false);
            board[row][col].addPiece(p);
            break;}
    }
}

//renders the graphic and text observers
void Board::render(){
    this->notifyObservers();
}

void Board::move(int fromX, int fromY, int toX, int toY, string turn) {  // instead of string from, string to etc, i made it into an int cuz seems easier for me :P
    if (this->isLegalMove(fromX, fromY, toX, toY, turn, false) == true) {
        //move
        shared_ptr<Piece> p = board[fromX][fromY].getPiece();//copy the piece
        board[toX][toY].addPiece(p);//removes to piece and adds from piece
        board[fromX][fromY].removePiece();
        //is enemy king in check -> is he checkmated
        if (this->checked(turn) == true){
            cout << "checked" << endl;
            //if (this->checkmate(turn) == true){
                //game over
            //}
            //set enemy inCheck to true
        }
        //if its a pawn, check if first step or not and set it to false...
        //if its king check if it can castle or not and set it to false etc...
    } else {
        //error
    }
}
bool Board::isLegalMove(int fromX, int fromY, int toX, int toY, string turn, bool inCheck) {
    vector<Vec> moves;
    return true;
    if (this->getSquare(fromX, fromY) == 1 && this->getPiece(fromX, fromY)->getColor() == turn) {  // if theyre moving a piece thats theirs
        moves = possibleMoves(this->getPiece(fromX, fromY), fromX, fromY);
        if (moves.size() == 0){
            return false;
        }
        for (size_t i = 0; i < moves.size(); i++) {  // if their piece is in the list produced by possibleMoves
            if (moves[i].x == toX && moves[i].y == toY) {
                //check if you are in check -> does moving prevent you from being in check
                if(inCheck == true){
                    // I think for this you would need to create a temp board and check lol.
                }
                //check if moving will put your king in check
                else{
                    // again create a temp board and check
                }
            }
        }
    }
    return false;
}

bool Board::checked(string turn){ //checks if you can capture enemy king.
    int kingX;
    int kingY;
    for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            auto p = board[col][row].getPiece();
            if (p->getColor() != turn && p->getName() == 'k') {
                kingX = col; // get enemy location
                kingY = row;
            }
        }
    }
    for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++){
            auto p = board[col][row].getPiece();
            if (p != nullptr){
                vector<Vec> moves = possibleMoves(p, row, col);
                for (size_t i = 0; i < moves.size(); i++) { // checks every piece to see if they can capture enemy king.
                    if (moves[i].x == kingX && moves[i].y == kingY){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::checkmate(string turn){ //checks all moves and sees if its a legal move.
    //if possible moves return empty for every single opponents piece. theyre checkmated
    for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            auto p = board[col][row].getPiece();
            if (p != nullptr) {
                if (p->getColor() != turn){ //checks opponents pieces
                    vector<Vec> moves = possibleMoves(p, row, col);
                    if (moves.size() != 0){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
//maybe just copy paste possibleMoves2 to the bottom of possibleMoves.
vector<Vec> Board ::possibleMoves2(shared_ptr<Piece> piece, int row, int col,vector<Vec> moves) {  // takes the possible moves below, and shaves it to only legal moves 
    int pieceX = col; // pieces location
    int pieceY = row;
    string turn;
    bool inCheck;
    for (size_t i = 0; i < moves.size(); i++) {  // checks every piece to see if they can capture enemy king.
        if (this->isLegalMove(pieceX, pieceY, moves[i].x, moves[i].y, turn, inCheck) == false) {
            moves[i].x = -1;
            moves[i].y = -1;
        }
    }
    return moves;
}
// I have yet to implement checking if the king can castle or not
vector<Vec> Board::possibleMoves(shared_ptr<Piece> piece, int row, int col) {
    vector<Vec> moves; // vector of pairs (x y)                                 
    char name = piece->getName();
    string color = piece->getColor();
    if (name == 'p') {
        /*
        if (color == "white"){
            if (piece.getFirstStep() == false){ // checks if its first step or not
                if (this->getSquare(col,row + 1) == 0) { // empty square
                    moves.emplace_back(col, row + 1); // adds move to vector
                }
                if (this->getSquare(col + 1, row + 1) == 1 && this->getPiece(col + 1, row + 1)->getColor() == "black") {  // checks if there is a capture available;
                    moves.emplace_back(col + 1, row + 1);
                }
                if (this->getSquare(col - 1, row + 1) == 1 && this->getPiece(col - 1, row + 1)->getColor() == "black") {  // checks if there is a capture available;
                    moves.emplace_back(col - 1, row + 1);
                }
            } else if (piece.getFirstStep() == 1) {  // first move
                if (this->getSquare(col, row + 1) == 0) {
                    moves.emplace_back(col, row + 1);
                }
                if (this->getSquare(col, row + 2) == 0) {  // moves 2 steps if
                    moves.emplace_back(col, row + 2);
                }
            }
        } else if (color == "black") { // black pieces moves the other direction
            if (piece.getFirstStep() == false) {
                if (this->getSquare(col, row - 1) == 0) {
                    moves.emplace_back(col, row - 1);
                }
                if (this->getSquare(col + 1, row - 1) == 1 && this->getPiece(col + 1, row - 1)->getColor() == "white") {
                    moves.emplace_back(col + 1, row - 1);
                }
                if (this->getSquare(col - 1, row - 1) == 1 && this->getPiece(col - 1, row - 1)->getColor() == "white") {
                    moves.emplace_back(col - 1, row - 1);
                }
            } else if (piece.getFirstStep() == true) {
                if (this->getSquare(col, row - 1) == 0) {
                    moves.emplace_back(col, row - 1);
                }
                if (this->getSquare(col, row - 2) == 0) {
                    moves.emplace_back(col, row - 2);
                }
            }
        }
    */} else if (name == 'n') {
        if (this->getSquare(col + 1, row + 2) == 0) {  // i ordered the checks counter clockwise) hopefully i didnt fuck up lul
            moves.emplace_back(col + 1, row + 2);
        } else if (this->getSquare(col + 1, row + 2) == 1 && this->getPiece(col + 1, row + 2)->getColor() != color) {  // checks if there is piece and not out of bounds + its capturable (enemy color)
            moves.emplace_back(col + 1, row + 2);
        }
        if (this->getSquare(col - 1, row + 2) == 0) {
            moves.emplace_back(col - 1, row + 2);
        } else if (this->getSquare(col + 1, row + 2) == 1 && this->getPiece(col - 1, row + 2)->getColor() != color) {
            moves.emplace_back(col - 1, row + 2);
        }
        if (this->getSquare(col - 2, row + 1) == 0) {
            moves.emplace_back(col - 2, row + 1);
        } else if (this->getSquare(col + 1, row + 2) == 1 && this->getPiece(col - 2, row + 1)->getColor() != color) {
            moves.emplace_back(col - 2, row + 1);
        }
        if (this->getSquare(col - 2, row - 1) == 0) {
            moves.emplace_back(col - 2, row - 1);
        } else if (this->getSquare(col + 1, row + 2) == 1 && this->getPiece(col - 2, row - 1)->getColor() != color) {
            moves.emplace_back(col - 2, row - 1);
        }
        if (this->getSquare(col - 1, row - 2) == 0) {
            moves.emplace_back(col - 1, row - 2);
        } else if (this->getSquare(col + 1, row + 2) == 1 && this->getPiece(col - 1, row - 2)->getColor() != color) {
            moves.emplace_back(col - 1, row - 2);
        }
        if (this->getSquare(col + 1, row - 2) == 0) {
            moves.emplace_back(col + 1, row - 2);
        } else if (this->getSquare(col + 1, row + 2) == 1 && this->getPiece(col + 1, row - 2)->getColor() != color) {
            moves.emplace_back(col + 1, row - 2);
        }
        if (this->getSquare(col + 2, row - 1) == 0) {
            moves.emplace_back(col + 2, row - 1);
        } else if (this->getSquare(col + 1, row + 2) == 1 && this->getPiece(col + 2, row - 1)->getColor() != color) {
            moves.emplace_back(col + 2, row - 1);
        }
        if (this->getSquare(col + 2, row + 1) == 0) {
            moves.emplace_back(col + 2, row + 1);
        } else if (this->getSquare(col + 1, row + 2) == 1 && this->getPiece(col + 2, row + 1)->getColor() != color) {
            moves.emplace_back(col + 2, row + 1);
        }
    } else if (name == 'r') {
        for (int i = 1; i < 8 ; i++){ // moves up
            if (this->getSquare(col, row + i) == 2) {  // checks out of bounds
                break;
            }
            if (this->getSquare(col, row + i) == 0){ // empty square
                moves.emplace_back(col, row + i);
            } else if (this->getSquare(col, row + i) == 1 && this->getPiece(col, row + i)->getColor() != color){ // capturable piece 
                moves.emplace_back(col, row + i);
                break;
            } else if (this->getSquare(col, row + i) == 1 && this->getPiece(col, row + i)->getColor() == color) {  // uncapturable piece (ally)
                break;
            }
        }
        for (int i = 1; i < 8 ; i++) {   //moves down
            if (this->getSquare(col, row - i) == 2) { 
                break;
            }
            if (this->getSquare(col, row - i) == 0) { 
                moves.emplace_back(col, row - i);
            } else if (this->getSquare(col, row - i) == 1 && this->getPiece(col, row - i)->getColor() != color) {  
                moves.emplace_back(col, row - i);
                break;
            } else if (this->getSquare(col, row - i) == 1 && this->getPiece(col, row - i)->getColor() == color) {  
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves left
            if (this->getSquare(col - i, row) == 2) {
                break;
            }
            if (this->getSquare(col - i, row) == 0) {
                moves.emplace_back(col - i, row);
            } else if (this->getSquare(col - i, row) == 1 && this->getPiece(col - i, row)->getColor() != color) {
                moves.emplace_back(col - i, row);
                break;
            } else if (this->getSquare(col - i, row) == 1 && this->getPiece(col - i, row)->getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves right
            if (this->getSquare(col + i, row) == 2) {
                break;
            }
            if (this->getSquare(col + i, row) == 0) {
                moves.emplace_back(col + i, row);
            } else if (this->getSquare(col + i, row) == 1 && this->getPiece(col + i, row)->getColor() != color) {
                moves.emplace_back(col + i, row);
                break;
            } else if (this->getSquare(col + i, row) == 1 && this->getPiece(col + i, row)->getColor() == color) {
                break;
            }
        }
    } else if (name == 'b') {
        for (int i = 1; i < 8; i++){ //moves top right
            if (this->getSquare(col + i, row + i) == 2) { // check out of bounds
                break;
            }
            if (this->getSquare(col + i, row + i) == 0) {
                moves.emplace_back(col + i, row + i); // empty square
            } else if (this->getSquare(col + i, row + i) == 1 && this->getPiece(col + i, row + i)->getColor() != color) { //capturable piece
                moves.emplace_back(col + i, row + i);
                break;
            } else if (this->getSquare(col + i, row + i) == 1 && this->getPiece(col + i, row + i)->getColor() == color) {  // uncapturable piece (ally)
                moves.emplace_back(col + i, row + i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {         // moves top left
            if (this->getSquare(col - i, row + i) == 2) {
                break;
            }
            if (this->getSquare(col - i, row + i) == 0) {
                moves.emplace_back(col - i, row + i);                                                                  
            } else if (this->getSquare(col - i, row + i) == 1 && this->getPiece(col - i, row + i)->getColor() != color) { 
                moves.emplace_back(col - i, row + i);
                break;
            } else if (this->getSquare(col - i, row + i) == 1 && this->getPiece(col - i, row + i)->getColor() == color) { 
                moves.emplace_back(col - i, row + i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves bottom left
            if (this->getSquare(col - i, row - i) == 2) {
                break;
            }
            if (this->getSquare(col - i, row - i) == 0) {
                moves.emplace_back(col - i, row - i);
            } else if (this->getSquare(col - i, row - i) == 1 && this->getPiece(col - i, row - i)->getColor() != color) {
                moves.emplace_back(col - i, row - i);
                break;
            } else if (this->getSquare(col - i, row - i) == 1 && this->getPiece(col - i, row - i)->getColor() == color) {
                moves.emplace_back(col - i, row - i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves bottom right
            if (this->getSquare(col + i, row - i) == 2) {
                break;
            }
            if (this->getSquare(col + i, row - i) == 0) {
                moves.emplace_back(col + i, row - i);
            } else if (this->getSquare(col + i, row - i) == 1 && this->getPiece(col + i, row - i)->getColor() != color) {
                moves.emplace_back(col + i, row - i);
                break;
            } else if (this->getSquare(col + i, row - i) == 1 && this->getPiece(col + i, row - i)->getColor() == color) {
                moves.emplace_back(col + i, row - i);
                break;
            }
        }
    } else if (name == 'q') { // ROOK + BISHOP
        for (int i = 1; i < 8; i++) {                      // moves top right
            if (this->getSquare(col + i, row + i) == 2) {  // check out of bounds
                break;
            }
            if (this->getSquare(col + i, row + i) == 0) {
                moves.emplace_back(col + i, row + i);                                                                   // empty square
            } else if (this->getSquare(col + i, row + i) == 1 && this->getPiece(col + i, row + i)->getColor() != color) {  // capturable piece
                moves.emplace_back(col + i, row + i);
                break;
            } else if (this->getSquare(col + i, row + i) == 1 && this->getPiece(col + i, row + i)->getColor() == color) {  // uncapturable piece (ally)
                moves.emplace_back(col + i, row + i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves top left
            if (this->getSquare(col - i, row + i) == 2) {
                break;
            }
            if (this->getSquare(col - i, row + i) == 0) {
                moves.emplace_back(col - i, row + i);
            } else if (this->getSquare(col - i, row + i) == 1 && this->getPiece(col - i, row + i)->getColor() != color) {
                moves.emplace_back(col - i, row + i);
                break;
            } else if (this->getSquare(col - i, row + i) == 1 && this->getPiece(col - i, row + i)->getColor() == color) {
                moves.emplace_back(col - i, row + i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves bottom left
            if (this->getSquare(col - i, row - i) == 2) {
                break;
            }
            if (this->getSquare(col - i, row - i) == 0) {
                moves.emplace_back(col - i, row - i);
            } else if (this->getSquare(col - i, row - i) == 1 && this->getPiece(col - i, row - i)->getColor() != color) {
                moves.emplace_back(col - i, row - i);
                break;
            } else if (this->getSquare(col - i, row - i) == 1 && this->getPiece(col - i, row - i)->getColor() == color) {
                moves.emplace_back(col - i, row - i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves bottom right
            if (this->getSquare(col + i, row - i) == 2) {
                break;
            }
            if (this->getSquare(col + i, row - i) == 0) {
                moves.emplace_back(col + i, row - i);
            } else if (this->getSquare(col + i, row - i) == 1 && this->getPiece(col + i, row - i)->getColor() != color) {
                moves.emplace_back(col + i, row - i);
                break;
            } else if (this->getSquare(col + i, row - i) == 1 && this->getPiece(col + i, row - i)->getColor() == color) {
                moves.emplace_back(col + i, row - i);
                break;
            }
        }
        for (int i = 1; i < 8; i++) {                  // moves up
            if (this->getSquare(col, row + i) == 2) {  // checks out of bounds
                break;
            }
            if (this->getSquare(col, row + i) == 0) {  // empty square
                moves.emplace_back(col, row + i);
            } else if (this->getSquare(col, row + i) == 1 && this->getPiece(col, row + i)->getColor() != color) {  // capturable piece
                moves.emplace_back(col, row + i);
                break;
            } else if (this->getSquare(col, row + i) == 1 && this->getPiece(col, row + i)->getColor() == color) {  // uncapturable piece (ally)
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves down
            if (this->getSquare(col, row - i) == 2) {
                break;
            }
            if (this->getSquare(col, row - i) == 0) {
                moves.emplace_back(col, row - i);
            } else if (this->getSquare(col, row - i) == 1 && this->getPiece(col, row - i)->getColor() != color) {
                moves.emplace_back(col, row - i);
                break;
            } else if (this->getSquare(col, row - i) == 1 && this->getPiece(col, row - i)->getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves left
            if (this->getSquare(col - i, row) == 2) {
                break;
            }
            if (this->getSquare(col - i, row) == 0) {
                moves.emplace_back(col - i, row);
            } else if (this->getSquare(col - i, row) == 1 && this->getPiece(col - i, row)->getColor() != color) {
                moves.emplace_back(col - i, row);
                break;
            } else if (this->getSquare(col - i, row) == 1 && this->getPiece(col - i, row)->getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves right
            if (this->getSquare(col + i, row) == 2) {
                break;
            }
            if (this->getSquare(col + i, row) == 0) {
                moves.emplace_back(col + i, row);
            } else if (this->getSquare(col + i, row) == 1 && this->getPiece(col + i, row)->getColor() != color) {
                moves.emplace_back(col + i, row);
                break;
            } else if (this->getSquare(col + i, row) == 1 && this->getPiece(col + i, row)->getColor() == color) {
                break;
            }
        }
    } 
    /*else if (name == "king") { //checks in order of clockwise
        if (this->getSquare(col, row + 1) != 2 && ){ // in bounds and check if king will be checked or not
            if (this->getSquare(col, row + 1) == 0) {  // empty square
                moves.emplace_back(col, row + 1);
            } else if (this->getSquare(col, row + 1) == 1 && this->getPiece(col, row + 1)->getColor() != color) {  // capturable piece
                moves.emplace_back(col, row + 1);
            }
        }
        if (this->getSquare(col + 1, row + 1) != 2 &&) {   //implement if king will be in check
            if (this->getSquare(col + 1, row + 1) == 0) { 
                moves.emplace_back(col + 1, row + 1);
            } else if (this->getSquare(col + 1, row + 1) == 1 && this->getPiece(col + 1, row + 1)->getColor() != color) { 
                moves.emplace_back(col + 1, row + 1);
            }
        }
        if (this->getSquare(col + 1, row) != 2 &&) {  // implement if king will be in check
            if (this->getSquare(col + 1, row) == 0) {
                moves.emplace_back(col + 1, row);
            } else if (this->getSquare(col + 1, row ) == 1 && this->getPiece(col + 1, row)->getColor() != color) {
                moves.emplace_back(col + 1, row);
            }
        }
        if (this->getSquare(col + 1, row - 1) != 2 &&) {  // implement if king will be in check
            if (this->getSquare(col + 1, row - 1) == 0) {
                moves.emplace_back(col + 1, row - 1);
            } else if (this->getSquare(col + 1, row - 1) == 1 && this->getPiece(col + 1, row - 1)->getColor() != color) {
                moves.emplace_back(col + 1, row - 1);
            }
        }
        if (this->getSquare(col, row - 1) != 2 &&) {  // implement if king will be in check
            if (this->getSquare(col, row - 1) == 0) {
                moves.emplace_back(col, row - 1);
            } else if (this->getSquare(col, row - 1) == 1 && this->getPiece(col, row - 1)->getColor() != color) {
                moves.emplace_back(col, row - 1);
            }
        }
        if (this->getSquare(col - 1, row - 1) != 2 &&) {  // implement if king will be in check
            if (this->getSquare(col - 1, row - 1) == 0) {
                moves.emplace_back(col - 1, row - 1);
            } else if (this->getSquare(col - 1, row - 1) == 1 && this->getPiece(col - 1, row - 1)->getColor() != color) {
                moves.emplace_back(col - 1, row - 1);
            }
        }
        if (this->getSquare(col - 1, row) != 2 &&) {  // implement if king will be in check
            if (this->getSquare(col - 1, row) == 0) {
                moves.emplace_back(col - 1, row);
            } else if (this->getSquare(col - 1, row) == 1 && this->getPiece(col - 1, row)->getColor() != color) {
                moves.emplace_back(col - 1, row);
            }
        }
        if (this->getSquare(col - 1, row + 1) != 2 &&) {  // implement if king will be in check
            if (this->getSquare(col - 1, row + 1) == 0) {
                moves.emplace_back(col - 1, row + 1);
            } else if (this->getSquare(col - 1, row + 1) == 1 && this->getPiece(col - 1, row + 1)->getColor() != color) {
                moves.emplace_back(col - 1, row + 1);
            }
        }
    }*/
    return possibleMoves2(piece, row, col, moves);
}
