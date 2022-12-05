#include "board.h"
#include <string>
#include "squares.h"
#include "textdisplay.h"
using namespace std;

//note: col = x, row = y
struct Vec {
    int row, col;
    Vec(int row, int col) : row{row}, col{col} {}
};
//ctor
Board::Board(vector<vector<Squares>> board, bool whiteCheck, bool blackCheck,string Won):
board{board},whiteCheck{whiteCheck},blackCheck{blackCheck},Won{Won}{}
vector<vector<Squares>> Board::getBoard(){
    return board;
}
// Important!! getSquare: 0 = no piece, 1 = theres a piece; 2 = out of bounds
int Board::getSquare(int row, int col){
    if (row > 8 || col > 8 || row < 1 || col < 1) {
        return 2;
    }
    auto p = board[row][col].getPiece();
    if (p != nullptr) {
        return 1;
    }
    return 0;
}
string Board::getWon(){
    return Won;
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
//invariant we are assuming board goes from 8 to 1 top to down, and 1 to 8 from left to right
shared_ptr<Piece> Board::getPiece(int row, int col){ // returns the piece on the square 
	if (row >= 1 && row <= 8 && col >=1 && col <= 8) {
            return board[row][col].getPiece();
    }
    return nullptr;
}
void Board::removePiece(int row, int col){
    board[row][col].removePiece();
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
            {shared_ptr<Piece>p = make_shared<King>("black", name, row,col,false);
            board[row][col].addPiece(p);
            break;}
        case 'K':
            {shared_ptr<Piece> p = make_shared<King>("white", name, row,col,false);
            board[row][col].addPiece(p);
            break;}
    }
}

//renders the graphic and text observers
void Board::render(){
    this->notifyObservers();
}

void Board::render(char type,int x,int y){
    this->notifyObservers(type,x, y);
}


bool Board::move(int fromRow, int fromCol, int toRow, int toCol, string turn) {  // instead of string from, string to etc, i made it into an int cuz seems easier for me :P
    if (this->isLegalMove(fromRow, fromCol, toRow, toCol, turn) == true) {
        //move
        shared_ptr<Piece> p = board[fromRow][fromCol].getPiece();  // copy the piece
        board[fromRow][fromCol].removePiece();                     // removes to piece and adds from piece
        board[toRow][toCol].addPiece(p);
        //possibleMoves(board[toRow][toCol].getPiece(), toRow, toCol);
        //is enemy king in check -> is he checkmated
        if (this->checked(turn) == true){
            cout << "checked" << endl;
            if (this->checkmate(turn) == true){
                cout << "checkmate" << endl;
                Won = turn;
            }
        }
        return true;
        //if its a pawn, check if first step or not and set it to false...
        //if its king check if it can castle or not and set it to false etc...
    } else {
        cout << "Illegal move" << endl;
        return false;
    }
}
bool Board::isLegalMove(int fromRow, int fromCol, int toRow, int toCol, string turn) {
    vector<Vec> moves;
    //cout << turn << endl;
    if (this->getSquare(fromRow, fromCol) == 1 && this->getPiece(fromRow, fromCol)->getColor() == turn) {  // if theyre moving a piece thats theirs
        //cout << toRow << toCol << endl;
        moves = possibleMoves(this->getPiece(fromRow, fromCol), fromRow, fromCol);
        //for (int i = 0; i < moves.size(); i ++){
        //    cout << '{' << moves[i].col << ',' << moves[i].row << '}';
       // }
        //cout << endl;
        if (moves.size() == 0){
            return false;
        }
        for (size_t i = 0; i < moves.size(); i++) {  // if their piece is in the list produced by possibleMoves
            if (moves[i].col == toCol && moves[i].row == toRow) {
                // check if you are in check -> does moving prevent you from being in check
                shared_ptr<Piece> p = board[fromRow][fromCol].getPiece();
                shared_ptr<Piece> p2 = nullptr;
                if (this->getSquare(toRow, toCol) == 1 && this->getPiece(toRow, toCol)->getColor() == turn){
                    return false;
                }
                else if (this->getSquare(toRow, toCol) == 1 && this->getPiece(toRow, toCol)->getColor() != turn) {
                    p2 = board[toRow][toCol].getPiece();
                }
                board[fromRow][fromCol].removePiece();
                board[toRow][toCol].addPiece(p);  // temp removes the piece
                //cout << this->getPiece(toRow, toCol)->getName() << endl;
                if (amIChecked(turn) == true) {   // still in check after move
                    board[toRow][toCol].removePiece();
                    board[fromRow][fromCol].addPiece(p);  // adds piece back
                    //cout << (p2 != nullptr) << endl;
                    if (p2 != nullptr) {
                        board[toRow][toCol].addPiece(p2);
                    }
                    return false;
                }
                board[toRow][toCol].removePiece();
                board[fromRow][fromCol].addPiece(p);  // puts board to how it was
                //cout << (p2 != nullptr) << endl;
                if (p2 != nullptr) {
                    board[toRow][toCol].addPiece(p2);
                }
                return true;
            }
        }
        cout << endl;
    }
    return false;
}
bool Board::amIChecked(string turn){ // there is a way to combine this with checked() i might do that later
    int kingRow;
    int kingCol;
    for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            auto p = board[row][col].getPiece();
            if (p != nullptr){
                if ((turn == "white" && p->getName() == 'K') || (turn == "black" && p->getName() == 'k')) {
                    kingRow = row;  // get your king location
                    kingCol = col;
                }
            }
        }
    }
    //cout << '{' << kingRow << ',' << kingCol << '}' << endl;
    for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            auto p = board[row][col].getPiece();
            if (p != nullptr) {
                vector<Vec> moves = possibleMoves(p, row, col);
                for (size_t i = 0; i < moves.size(); i++) {  // checks every piece to see if they can capture your king.
                    if (moves[i].row == kingRow && moves[i].col == kingCol) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool Board::checked(string turn){ //checks if you can capture enemy king.
    int kingRow;
    int kingCol;
    for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {  
            auto p = board[row][col].getPiece();
            if (p != nullptr){
                if ((turn == "white" && p->getName() == 'k') || (turn == "black" && p->getName() == 'K')) {
                    kingRow = row;  // get enemy location
                    kingCol = col;
                }
            }
        }
    }
    //cout << '{' << kingRow << ',' << kingCol << '}' << endl;
    for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++){
            auto p = board[row][col].getPiece();
            if (p != nullptr){
                vector<Vec> moves = possibleMoves(p, row, col);
                for (size_t i = 0; i < moves.size(); i++) { // checks every piece to see if they can capture enemy king.
                    if (moves[i].row == kingRow && moves[i].col == kingCol){
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
    int count = 0;

    for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            auto p = board[row][col].getPiece();
            if (p != nullptr) {
                if (p->getColor() != turn){ //checks opponents pieces
                    vector<Vec> moves = possibleMoves(p, row, col);
                    int len = moves.size();
                    for (int i = 0; i < len; i++){

                        //cout << moves[i].row << " " << moves [i].col << endl;
                        
                        if (turn == "white"){
                            if (isLegalMove(row, col, moves[i].row, moves[i].col, "black") == true) {
                                count++;
                            }
                        } else {
                            if (isLegalMove(row, col, moves[i].row, moves[i].col, "white") == true) {
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }
    if (count != 0) {
        return false;
    }
    return true;
}

// I have yet to implement checking if the king can castle or not
vector<Vec> Board::possibleMoves(shared_ptr<Piece> piece, int row, int col) {
    vector<Vec> moves; // vector of pairs (x y)
    char name = piece->getName();
    string color = piece->getColor();
    if (name == 'p' || name == 'P') {
        /*
        if (color == "white"){
            if (piece.getFirstStep() == false){ // checks if its first step or not
                if (this->getSquare(row,col + 1) == 0) { // empty square
                    moves.emplace_back(row, col + 1); // adds move to vector
                }
                if (this->getSquare(row + 1, col + 1) == 1 && this->getPiece(row + 1, col + 1)->getColor() == "black") {  // checks if there is a capture available;
                    moves.emplace_back(row + 1, col + 1);
                }
                if (this->getSquare(row - 1, col + 1) == 1 && this->getPiece(row - 1, col + 1)->getColor() == "black") {  // checks if there is a capture available;
                    moves.emplace_back(row - 1, col + 1);
                }
            } else if (piece.getFirstStep() == 1) {  // first move
                if (this->getSquare(row, col + 1) == 0) {
                    moves.emplace_back(row, col + 1);
                }
                if (this->getSquare(row, col + 2) == 0) {  // moves 2 steps if
                    moves.emplace_back(row, col + 2);
                }
            }
        } else if (color == "black") { // black pieces moves the other direction
            if (piece.getFirstStep() == false) {
                if (this->getSquare(row, col - 1) == 0) {
                    moves.emplace_back(row, col - 1);
                }
                if (this->getSquare(row + 1, col - 1) == 1 && this->getPiece(row + 1, col - 1)->getColor() == "white") {
                    moves.emplace_back(row + 1, col - 1);
                }
                if (this->getSquare(row - 1, col - 1) == 1 && this->getPiece(row - 1, col - 1)->getColor() == "white") {
                    moves.emplace_back(row - 1, col - 1);
                }
            } else if (piece.getFirstStep() == true) {
                if (this->getSquare(row, col - 1) == 0) {
                    moves.emplace_back(row, col - 1);
                }
                if (this->getSquare(row, col - 2) == 0) {
                    moves.emplace_back(row, col - 2);
                }
            }
        }
    */} else if (name == 'n' || name == 'N') {
        if (this->getSquare(row + 1, col + 2) == 0) {  // i ordered the checks counter clockwise) hopefully i didnt fuck up lul
            moves.emplace_back(row + 1, col + 2);
        } else if (this->getSquare(row + 1, col + 2) == 1 && this->getPiece(row + 1, col + 2)->getColor() != color) {  // checks if there is piece and not out of bounds + its capturable (enemy color)
            moves.emplace_back(row + 1, col + 2);
        }
        if (this->getSquare(row - 1, col + 2) == 0) {
            moves.emplace_back(row - 1, col + 2);
        } else if (this->getSquare(row - 1, col + 2) == 1 && this->getPiece(row - 1, col + 2)->getColor() != color) {
            moves.emplace_back(row - 1, col + 2);
        }
        if (this->getSquare(row - 2, col + 1) == 0) {
            moves.emplace_back(row - 2, col + 1);
        } else if (this->getSquare(row - 2, col + 1) == 1 && this->getPiece(row - 2, col + 1)->getColor() != color) {
            moves.emplace_back(row - 2, col + 1);
        }
        if (this->getSquare(row - 2, col - 1) == 0) {
            moves.emplace_back(row - 2, col - 1);
        } else if (this->getSquare(row - 2, col - 1) == 1 && this->getPiece(row - 2, col - 1)->getColor() != color) {
            moves.emplace_back(row - 2, col - 1);
        }
        if (this->getSquare(row - 1, col - 2) == 0) {
            moves.emplace_back(row - 1, col - 2);
        } else if (this->getSquare(row - 1, col - 2) == 1 && this->getPiece(row - 1, col - 2)->getColor() != color) {
            moves.emplace_back(row - 1, col - 2);
        }
        if (this->getSquare(row + 1, col - 2) == 0) {
            moves.emplace_back(row + 1, col - 2);
        } else if (this->getSquare(row + 1, col - 2) == 1 && this->getPiece(row + 1, col - 2)->getColor() != color) {
            moves.emplace_back(row + 1, col - 2);
        }
        if (this->getSquare(row + 2, col - 1) == 0) {
            moves.emplace_back(row + 2, col - 1);
        } else if (this->getSquare(row + 2, col - 1) == 1 && this->getPiece(row + 2, col - 1)->getColor() != color) {
            moves.emplace_back(row + 2, col - 1);
        }
        if (this->getSquare(row + 2, col + 1) == 0) {
            moves.emplace_back(row + 2, col + 1);
        } else if (this->getSquare(row + 2, col + 1) == 1 && this->getPiece(row + 2, col + 1)->getColor() != color) {
            moves.emplace_back(row + 2, col + 1);
        }
    } else if (name == 'r' || name == 'R') {
        for (int i = 1; i < 8; i++) {                  // moves up
            if (this->getSquare(row, col + i) == 2) {  // checks out of bounds
                break;
            }
            if (this->getSquare(row, col + i) == 0) {  // empty square
                moves.emplace_back(row, col + i);
            } else if (this->getSquare(row, col + i) == 1 && this->getPiece(row, col + i)->getColor() != color) {  // capturable piece
                moves.emplace_back(row, col + i);
                break;
            } else if (this->getSquare(row, col + i) == 1 && this->getPiece(row, col + i)->getColor() == color) {  // uncapturable piece (ally)
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves down
            if (this->getSquare(row, col - i) == 2) {
                break;
            }
            if (this->getSquare(row, col - i) == 0) {
                moves.emplace_back(row, col - i);
            } else if (this->getSquare(row, col - i) == 1 && this->getPiece(row, col - i)->getColor() != color) {
                moves.emplace_back(row, col - i);
                break;
            } else if (this->getSquare(row, col - i) == 1 && this->getPiece(row, col - i)->getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves left
            if (this->getSquare(row - i, col) == 2) {
                break;
            }
            if (this->getSquare(row - i, col) == 0) {
                moves.emplace_back(row - i, col);
            } else if (this->getSquare(row - i, col) == 1 && this->getPiece(row - i, col)->getColor() != color) {
                moves.emplace_back(row - i, col);
                break;
            } else if (this->getSquare(row - i, col) == 1 && this->getPiece(row - i, col)->getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves right
            if (this->getSquare(row + i, col) == 2) {
                break;
            }
            if (this->getSquare(row + i, col) == 0) {
                moves.emplace_back(row + i, col);
            } else if (this->getSquare(row + i, col) == 1 && this->getPiece(row + i, col)->getColor() != color) {
                moves.emplace_back(row + i, col);
                break;
            } else if (this->getSquare(row + i, col) == 1 && this->getPiece(row + i, col)->getColor() == color) {
                break;
            }
        }
    } else if (name == 'b' || name == 'B') {
        for (int i = 1; i < 8; i++) {                      // moves top right
            if (this->getSquare(row + i, col + i) == 2) {  // check out of bounds
                break;
            }
            if (this->getSquare(row + i, col + i) == 0) {
                moves.emplace_back(row + i, col + i);                                                                      // empty square
            } else if (this->getSquare(row + i, col + i) == 1 && this->getPiece(row + i, col + i)->getColor() != color) {  // capturable piece
                moves.emplace_back(row + i, col + i);
                break;
            } else if (this->getSquare(row + i, col + i) == 1 && this->getPiece(row + i, col + i)->getColor() == color) {  // uncapturable piece (ally)
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves top left
            if (this->getSquare(row - i, col + i) == 2) {
                break;
            }
            if (this->getSquare(row - i, col + i) == 0) {
                moves.emplace_back(row - i, col + i);
            } else if (this->getSquare(row - i, col + i) == 1 && this->getPiece(row - i, col + i)->getColor() != color) {
                moves.emplace_back(row - i, col + i);
                break;
            } else if (this->getSquare(row - i, col + i) == 1 && this->getPiece(row - i, col + i)->getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves bottom left
            if (this->getSquare(row - i, col - i) == 2) {
                break;
            }
            if (this->getSquare(row - i, col - i) == 0) {
                moves.emplace_back(row - i, col - i);
            } else if (this->getSquare(row - i, col - i) == 1 && this->getPiece(row - i, col - i)->getColor() != color) {
                moves.emplace_back(row - i, col - i);
                break;
            } else if (this->getSquare(row - i, col - i) == 1 && this->getPiece(row - i, col - i)->getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves bottom right
            if (this->getSquare(row + i, col - i) == 2) {
                break;
            }
            if (this->getSquare(row + i, col - i) == 0) {
                moves.emplace_back(row + i, col - i);
            } else if (this->getSquare(row + i, col - i) == 1 && this->getPiece(row + i, col - i)->getColor() != color) {
                moves.emplace_back(row + i, col - i);
                break;
            } else if (this->getSquare(row + i, col - i) == 1 && this->getPiece(row + i, col - i)->getColor() == color) {
                break;
            }
        }
    } else if (name == 'q' || name == 'Q') {               // ROOK + BISHOP
        for (int i = 1; i < 8; i++) {                      // moves top right
            if (this->getSquare(row + i, col + i) == 2) {  // check out of bounds
                break;
            }
            if (this->getSquare(row + i, col + i) == 0) {
                moves.emplace_back(row + i, col + i);                                                                      // empty square
            } else if (this->getSquare(row + i, col + i) == 1 && this->getPiece(row + i, col + i)->getColor() != color) {  // capturable piece
                moves.emplace_back(row + i, col + i);
                break;
            } else if (this->getSquare(row + i, col + i) == 1 && this->getPiece(row + i, col + i)->getColor() == color) {  // uncapturable piece (ally)
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves top left
            if (this->getSquare(row - i, col + i) == 2) {
                break;
            }
            if (this->getSquare(row - i, col + i) == 0) {
                moves.emplace_back(row - i, col + i);
            } else if (this->getSquare(row - i, col + i) == 1 && this->getPiece(row - i, col + i)->getColor() != color) {
                moves.emplace_back(row - i, col + i);
                break;
            } else if (this->getSquare(row - i, col + i) == 1 && this->getPiece(row - i, col + i)->getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves bottom left
            if (this->getSquare(row - i, col - i) == 2) {
                break;
            }
            if (this->getSquare(row - i, col - i) == 0) {
                moves.emplace_back(row - i, col - i);
            } else if (this->getSquare(row - i, col - i) == 1 && this->getPiece(row - i, col - i)->getColor() != color) {
                moves.emplace_back(row - i, col - i);
                break;
            } else if (this->getSquare(row - i, col - i) == 1 && this->getPiece(row - i, col - i)->getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves bottom right
            if (this->getSquare(row + i, col - i) == 2) {
                break;
            }
            if (this->getSquare(row + i, col - i) == 0) {
                moves.emplace_back(row + i, col - i);
            } else if (this->getSquare(row + i, col - i) == 1 && this->getPiece(row + i, col - i)->getColor() != color) {
                moves.emplace_back(row + i, col - i);
                break;
            } else if (this->getSquare(row + i, col - i) == 1 && this->getPiece(row + i, col - i)->getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {                  // moves up
            if (this->getSquare(row, col + i) == 2) {  // checks out of bounds
                break;
            }
            if (this->getSquare(row, col + i) == 0) {  // empty square
                moves.emplace_back(row, col + i);
            } else if (this->getSquare(row, col + i) == 1 && this->getPiece(row, col + i)->getColor() != color) {  // capturable piece
                moves.emplace_back(row, col + i);
                break;
            } else if (this->getSquare(row, col + i) == 1 && this->getPiece(row, col + i)->getColor() == color) {  // uncapturable piece (ally)
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves down
            if (this->getSquare(row, col - i) == 2) {
                break;
            }
            if (this->getSquare(row, col - i) == 0) {
                moves.emplace_back(row, col - i);
            } else if (this->getSquare(row, col - i) == 1 && this->getPiece(row, col - i)->getColor() != color) {
                moves.emplace_back(row, col - i);
                break;
            } else if (this->getSquare(row, col - i) == 1 && this->getPiece(row, col - i)->getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves left
            if (this->getSquare(row - i, col) == 2) {
                break;
            }
            if (this->getSquare(row - i, col) == 0) {
                moves.emplace_back(row - i, col);
            } else if (this->getSquare(row - i, col) == 1 && this->getPiece(row - i, col)->getColor() != color) {
                moves.emplace_back(row - i, col);
                break;
            } else if (this->getSquare(row - i, col) == 1 && this->getPiece(row - i, col)->getColor() == color) {
                break;
            }
        }
        for (int i = 1; i < 8; i++) {  // moves right
            if (this->getSquare(row + i, col) == 2) {
                break;
            }
            if (this->getSquare(row + i, col) == 0) {
                moves.emplace_back(row + i, col);
            } else if (this->getSquare(row + i, col) == 1 && this->getPiece(row + i, col)->getColor() != color) {
                moves.emplace_back(row + i, col);
                break;
            } else if (this->getSquare(row + i, col) == 1 && this->getPiece(row + i, col)->getColor() == color) {
                break;
            }
        }
    }
    else if (name == 'k' || name == 'K') { //checks in order of clockwise
        if (this->getSquare(row, col + 1) != 2){ // in bounds 
            if (this->getSquare(row, col + 1) == 0) {  // empty square
                moves.emplace_back(row, col + 1);
            } else if (this->getSquare(row, col + 1) == 1 && this->getPiece(row, col + 1)->getColor() != color) {  // capturable piece
                moves.emplace_back(row, col + 1);
            }
        }
        if (this->getSquare(row + 1, col + 1) != 2) {   //implement if king will be in check
            if (this->getSquare(row + 1, col + 1) == 0) {
                moves.emplace_back(row + 1, col + 1);
            } else if (this->getSquare(row + 1, col + 1) == 1 && this->getPiece(row + 1, col + 1)->getColor() != color) {
                moves.emplace_back(row + 1, col + 1);
            }
        }
        if (this->getSquare(row + 1, col) != 2) {  // implement if king will be in check
            if (this->getSquare(row + 1, col) == 0) {
                moves.emplace_back(row + 1, col);
            } else if (this->getSquare(row + 1, col ) == 1 && this->getPiece(row + 1, col)->getColor() != color) {
                moves.emplace_back(row + 1, col);
            }
        }
        if (this->getSquare(row + 1, col - 1) != 2) {  // implement if king will be in check
            if (this->getSquare(row + 1, col - 1) == 0) {
                moves.emplace_back(row + 1, col - 1);
            } else if (this->getSquare(row + 1, col - 1) == 1 && this->getPiece(row + 1, col - 1)->getColor() != color) {
                moves.emplace_back(row + 1, col - 1);
            }
        }
        if (this->getSquare(row, col - 1) != 2) {  // implement if king will be in check
            if (this->getSquare(row, col - 1) == 0) {
                moves.emplace_back(row, col - 1);
            } else if (this->getSquare(row, col - 1) == 1 && this->getPiece(row, col - 1)->getColor() != color) {
                moves.emplace_back(row, col - 1);
            }
        }
        if (this->getSquare(row - 1, col - 1) != 2 ) {  // implement if king will be in check
            if (this->getSquare(row - 1, col - 1) == 0) {
                moves.emplace_back(row - 1, col - 1);
            } else if (this->getSquare(row - 1, col - 1) == 1 && this->getPiece(row - 1, col - 1)->getColor() != color) {
                moves.emplace_back(row - 1, col - 1);
            }
        }
        if (this->getSquare(row - 1, col) != 2) {  // implement if king will be in check
            if (this->getSquare(row - 1, col) == 0) {
                moves.emplace_back(row - 1, col);
            } else if (this->getSquare(row - 1, col) == 1 && this->getPiece(row - 1, col)->getColor() != color) {
                moves.emplace_back(row - 1, col);
            }
        }
        if (this->getSquare(row - 1, col + 1) != 2) {  // implement if king will be in check
            if (this->getSquare(row - 1, col + 1) == 0) {
                moves.emplace_back(row - 1, col + 1);
            } else if (this->getSquare(row - 1, col + 1) == 1 && this->getPiece(row - 1, col + 1)->getColor() != color) {
                moves.emplace_back(row - 1, col + 1);
            }
        }
    }
    return moves;
}
