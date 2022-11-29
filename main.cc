//test harness
//To do:
//change board position into two ints
//handle different variations of move
//add in throw/catch exceptions for input?
//IMPLEMENT EVERYTHING
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "squares.h"
#include "board.h"
#include "piece.h"
using namespace std;
int main(){
	string c;
	string p1;
	string p2;
	int scoreW = 0, scoreB = 0;
	bool start = false;
	vector<vector<unique_ptr<Squares>>> board;
	for(int i = 0; i < 9 ; ++i){
		vector<unique_ptr<Squares>> row;
		for(int j = 0; j < 9 ; ++j){
			row.emplace_back(make_unique<Squares>(i,j,nullptr));
		}
		board.emplace_back(row);
	}
	Board mainBoard{board,false,false,false,false,false};
	auto text = make_unique<TextDisplay>(mainBoard," ");
	while(cin >> c){
		if(c == "setup"){
			while(cin >> c){
				if(c == "done"){
					break;
				}else if(c == "="){
					string colour;
					cin >> colour;
					//change turn to let colour go first
				}else if(c == "-"){
					string pos;
					int chr, num;
					cin >> pos;
					//somehow change char + num into two ints
					//remove piece at pos char + num
					//display board
				}else if(c == "+"){
					string piece, pos;
					cin >> piece >> pos;
					//add piece to pos
					//display board
				}else{
					cout << "invalid" << endl;
				}
			}
		}else if(c == "game"){
		       cin >> p1 >> p2;
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
