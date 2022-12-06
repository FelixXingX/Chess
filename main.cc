//test harness
//To do:
//change board position into two ints
//handle different variations of move
//add in throw/catch exceptions for input?
//IMPLEMENT EVERYTHING
#include <string>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "squares.h"
#include "board.h"
#include "piece.h"
#include "player.h"
//#include "graphicdisplay.h"
//#include "window.h"
using namespace std;
void createCopy(vector<vector<Squares>> & copy, const vector<vector<Squares>> &main){
	for(size_t i = 0; i < main.size() ; ++i){
		vector<Squares> row;
		for(size_t j = 0; j < main[i].size() ; ++j){
			Squares s {main[i][j]};
			row.emplace_back(s);
		}
		copy.emplace_back(row);
	}
}
int match(char cha){
	switch(cha){
		case 'a':
			return 1;
		case 'b':
			return 2;
		case 'c':
			return 3;
		case 'd':
			return 4;
		case 'e':
			return 5;
		case 'f':
			return 6;
		case 'g':
			return 7;
		case 'h':
			return 8;
	}
	return 0;
}

bool outOfBounds(int row, char col){
	int coll = match(col);
	if(row > 8 || row < 1 || coll == 0){
		cout << "invalid position" << col << row;
		return true;
	}
	return false;
}
unique_ptr<Player> createPlayer(string p,string colour){
	if(p == "human"){
		unique_ptr<Player> player = make_unique<Human>(colour);
		return player;
	} else if(p == "computer[1]"){
		unique_ptr<Player> player = make_unique<Computer1>(colour);
		return player;
	} else if(p == "computer[2]"){
		unique_ptr<Player> player = make_unique<Computer2>(colour);
		return player;
	} else if(p == "computer[3]"){
		unique_ptr<Player> player = make_unique<Computer3>(colour);
		return player;
	}else if(p == "computer[4]"){
		unique_ptr<Player> player = make_unique<Computer3>(colour);
		return player;
	}else{
		cout << "invalid player" << p << endl;
	}
	unique_ptr<Player> player;
	return player;
}
void setUp(Board& board){
	for(int i = 0; i <9; ++i){
		board.addPiece(7,i,'p');
		board.addPiece(2,i,'P');
	}
	board.addPiece(8,1,'r');
	board.addPiece(8,2,'n');
	board.addPiece(8,3,'b');
	board.addPiece(8,4,'q');
	board.addPiece(8,5,'k');
	board.addPiece(8,6,'b');
	board.addPiece(8,7,'n');
	board.addPiece(8,8,'r');
	board.addPiece(1,1,'R');
	board.addPiece(1,2,'N');
	board.addPiece(1,3,'B');
	board.addPiece(1,4,'Q');
	board.addPiece(1,5,'K');
	board.addPiece(1,6,'B');
	board.addPiece(1,7,'N');
	board.addPiece(1,8,'R');
}

int main(){
	string c, white, black, turn;
	int whoStart = 0, curTurn = 0;//0 for white start, 1 for black start
	double scoreW = 0, scoreB = 0;
	int numBk = 1, numWk = 1;
	//bool start = false;
	//bool bChecked = false, wChecked = false;
	//Set up the board, text and graphic display
	int scale = 80;
	int rows = 8, cols = 8;
	vector<vector<Squares>> board;
	for(int i = 0; i < 9 ; ++i){
		vector<Squares> row;
		for(int j = 0; j < 9 ; ++j){
			shared_ptr<Piece> p;
			Squares s{i,j,p};
			row.emplace_back(s);
		}
		board.emplace_back(row);
	}
	Board mainBoard{board,false,false," "};
	auto text = make_unique<TextDisplay>(&mainBoard," ");
	//auto window = make_shared<Xwindow>((rows + 2) * scale, (cols + 1) *scale);
	//auto graphic = make_unique<GraphicsDisplay>(&mainBoard,window, rows,cols,scale);
	//setUp(mainBoard);
    mainBoard.addPiece(1, 5, 'K');
    mainBoard.addPiece(8, 5, 'k');
    mainBoard.addPiece(1, 8, 'R');
    mainBoard.addPiece(1, 1, 'R');
    mainBoard.addPiece(8, 8, 'r');
    mainBoard.addPiece(8, 1, 'r');
    mainBoard.addPiece(2, 3, 'P');
    mainBoard.render();
    //This is the test harness
	while(cin >> c){
		//Setup mode
		if(c == "setup"){
			cout << "entering setup mode" << endl;
			text->changeMsg("setup mode");
			mainBoard.render('t',1,1); //Just to update board
			while(cin >> c){
				if(c == "done"){
					//check if numkings are 1
					if(numBk != 1 || numWk != 1){cout << "invalid number of kings"<< endl; continue;}
					//and no pawns on ends of the board
					bool pawn = false;
					for(int i = 1; i < 9 ; ++i){
						if(mainBoard.getPiece(8,i))	{
							if(mainBoard.getPiece(8,i)->getName() == 'p' || mainBoard.getPiece(8,i)->getName() == 'P'){
								cout << "Pawns not allowed on the first/last row of the board" << endl;
								pawn = true;
								break;
							}
						}
						if(mainBoard.getPiece(1,i)){
							if(mainBoard.getPiece(1,i)->getName() == 'p'||mainBoard.getPiece(1,i)->getName() == 'p'){
								cout << "Pawns not allowed on the first/last row of the board" << endl;
								pawn = true;
								break;
							}
						}
					}
					if(pawn) continue;
					//check for checks
					if(mainBoard.checked("white")){cout << "cannot start in check" << endl;}
					if(mainBoard.checked("black")){cout << "cannot start in check" << endl;}
					cout << "Exiting setup mode" << endl;
					break;
				}else if(c == "="){
					string goStart;
					cin >> goStart;
					if(goStart == "black"){whoStart = 1;}
					if(goStart == "white"){whoStart = 0;}
					//change turn to let colour go first
				}else if(c == "-"){
					string pos;
					cin >> pos;
					istringstream iss{pos};
					char col;
					int row;
					iss >> col >> row;
					//if the pos given is invalid, just skip the things below
					if(outOfBounds(row,col))continue;
					int coll = match(col);
					if(mainBoard.getPiece(row,coll)){
						if(mainBoard.getPiece(row,coll)->getName() == 'k')--numBk;
						if(mainBoard.getPiece(row,coll)->getName() == 'K')--numWk;
					}
					mainBoard.removePiece(row,coll);
					mainBoard.render('t',row,coll);
					mainBoard.render('g',row,coll);
					//remove piece at pos char + num
					//display board
				}else if(c == "+"){
					string pos;
					char piece;
					cin >> piece >> pos;
					istringstream iss{pos};
					char col;
					int row; 
					iss >> col >> row;
					//if the pos given is invalid, just skip the things below
					if(outOfBounds(row,col))continue;
					int coll = match(col);
					if(piece == 'k') ++numBk;
					if(piece == 'K') ++numWk;
					mainBoard.addPiece(row,coll,piece);
					mainBoard.render('t',row,coll);
					mainBoard.render('g',row,coll);
					//display board
				}else{
					cout << "invalid" << endl;
				}
			}
			//Game mode
		}else if(c == "game"){
				text->changeMsg("in game");
				curTurn = whoStart;//Start turn at 0 for white to go or Start turn at 1 for black to go
		    	cin >> white >> black;
				unique_ptr<Player> p1 = move(createPlayer(white,"white"));
				unique_ptr<Player> p2 = move(createPlayer(black,"black"));
				if(!p1 || !p2) continue;//if invalid params just break and go back to loop

				//makes a copy of the main board as the game board. This way changes to board stays
				vector<vector<Squares>> gmBoard;
				createCopy(gmBoard,mainBoard.getBoard());
				Board gameBoard{gmBoard,false,false," "};
				auto text2 = make_unique<TextDisplay>(&gameBoard," ");
				//auto window2 = make_shared<Xwindow>((rows + 2) * scale, (cols + 1) *scale);
				//auto graphic2 = make_unique<GraphicsDisplay>(&gameBoard,window2, rows,cols,scale);
				gameBoard.render('t',1,1);
			    //create player object depending on the input
					while(cin >> c){
						if(c == "resign"){
							//resign
							if(curTurn % 2 == 0){
								++ scoreB;
								cout << "Black wins!" <<endl;
							}else{
								++ scoreW;
								cout << "White wins!" <<endl;
							}
							//reset the status
							mainBoard.render();
							break;
						}else if(c == "move"){
							//move stuff
							//Each player object have their own unique overloaded method
							if(curTurn % 2 == 0){
								p1->move(cin,cout,gameBoard,curTurn);
								
							}else if(curTurn % 2 == 1){
								p2->move(cin,cout,gameBoard,curTurn);
								
							}
						}else{
							cout << "invalid" << endl;
						}
						string stat = gameBoard.getWon();
						if(stat == "black"){
								++ scoreB;
								cout << "Checkmate! Black wins!" <<endl;
								mainBoard.render();
								break;
						}
						if(stat == "white"){
							++ scoreW;
							cout << "Checkmate! White wins!" <<endl;
							mainBoard.render();
							break;
						}
						if(stat == "stalemate"){}
			}
		}else{
		       cout << "invalid" << endl;
		}	       
	}
	cout << "Final Score:" << endl;
	cout << "White: " << scoreW << endl;
	cout << "Black: " << scoreB << endl;
}
