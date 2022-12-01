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
using namespace std;

int match(char cha){
	switch(cha){
		case 'a':
			return 8;
		case 'b':
			return 7;
		case 'c':
			return 6;
		case 'd':
			return 5;
		case 'e':
			return 4;
		case 'f':
			return 3;
		case 'g':
			return 2;
		case 'h':
			return 1;
	}
	return 0;
}
int main(){
	string c, white, black, turn, whoStart;
	int scoreW = 0, scoreB = 0;
	int numBk = 1, numWk = 1;
	bool start = false;
	bool bChecked = false, wChecked = false;
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
	Board mainBoard{board,false,false,false,false,false};
	auto text = make_unique<TextDisplay>(&mainBoard," ");
	mainBoard.render();
	for(int i = 0; i <9; ++i){
		mainBoard.addPiece(7,i,'p');
		mainBoard.addPiece(2,i,'P');
	}
	mainBoard.render();
	mainBoard.move(7,4,2,2,"test");
	mainBoard.render();
	while(cin >> c){
		if(c == "setup"){
			while(cin >> c){
				if(c == "done"){
					//check if numkings are 1, and no checks on board
					break;
				}else if(c == "="){
					cin >> start;
					//change turn to let colour go first
				}else if(c == "-"){
					string pos;
					int chr, num;
					cin >> pos;
					//somehow change char + num into two ints
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
					int coll = match(col);
					if(coll == 0 || row > 8 || row < 1) {cout << "invalid position" <<endl; continue;}
					mainBoard.addPiece(row,coll,piece);
					mainBoard.render();
					//display board
				}else{
					cout << "invalid" << endl;
				}
			}
		}else if(c == "game"){
		       cin >> white >> black;
		       break;
		}else{
		       cout << "invalid" << endl;
		}	       
	}
	while(cin >> c){
		if(c == "resign"){
			//resign
		}else if(c == "move"){
			//move stuff
			//if pass turn for bot
			// generic move
			string pos1,pos2;
			cin >> pos1 >> pos2;
			istringstream iss1{pos1};
			int fromRow;
			char fromCol;
			iss1 >>fromCol >> fromRow;
			int fCol = match(fromCol);
			istringstream iss2{pos2};
			int toRow;
			char toCol;
			iss2 >>toCol>> toRow;
			int tCol = match(toCol);
			mainBoard.move(fromRow,fCol,toRow,tCol,"test");
			mainBoard.render();
			//castling
			//move but with pawn promotion
			//check if checked / checkmate etc
			//bot statements probably go here
		}else{
			cout << "invalid" << endl;
		}
	}
	cout << "Final Score:" << endl;
	cout << "White: " << scoreW << endl;
	cout << "Black: " << scoreB << endl;
}
