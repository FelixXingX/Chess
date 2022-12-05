#include "player.h"
#include "board.h"
#include <iostream>
#include <map>
using namespace std;
int matchs(char cha){
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
bool outOfBound(int row, char col,ostream &out){
	int coll = matchs(col);
	if(row > 8 || row < 1 || coll == 0){
		out  << "invalid position" << col << row;
		return true;
	}
	return false;
}

Player::Player(string colour): colour{colour}{}
string Player::getColour(){return colour;}
//Human player stuff
Human::Human(string colour): Player(colour){};
void Human::move(istream &in, ostream &out, Board &mainBoard, int& curTurn){
    string pos1,pos2;
	in >> pos1 >> pos2;
	istringstream iss1{pos1};
	int fromRow;
	char fromCol;
	iss1 >> fromCol >> fromRow;
    if(outOfBound(fromRow,fromCol,out))return;
	int fCol = matchs(fromCol);
	istringstream iss2{pos2};
	int toRow;
	char toCol;
	iss2 >> toCol >> toRow;
    if(outOfBound(toRow,toCol,out))return;
	int tCol = matchs(toCol);
    //move function
	bool pass = mainBoard.move(fromRow,fCol,toRow,tCol,getColour());
	if (pass == true){
        ++curTurn;
		mainBoard.render('t',1,1);
		//mainBoard.render('g',fromRow,fCol);
		mainBoard.render('g',toRow,tCol);
    }
    cout << curTurn << endl;
    //mainBoard.render('t',1,1);
}
//Bots stuff
Computer1::Computer1(string colour): Player(colour){};

void Computer1::move(istream &in, ostream &out, Board &mainBoard, int& curTurn){
    out << "not yet implemented" << endl;
	vector<Vec> list;
	for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            auto p = mainBoard.getBoard()[row][col].getPiece();
            if (p != nullptr){
                if (p->getColor() == getColour()) {
					list.emplace_back(row,col);
					
                }
            }
        }
    }
}
Computer2::Computer2(string colour): Player(colour){};
void Computer2::move(istream &in, ostream &out, Board &mainBoard, int& curTurn){
    out << "not yet implemented" << endl;

    string pos1,pos2;
	in >> pos1 >> pos2;
	istringstream iss1{pos1};
	int fromRow;
	char fromCol;
	iss1 >> fromCol >> fromRow;
    if(outOfBound(fromRow,fromCol,out))return;
	int fCol = matchs(fromCol);
	istringstream iss2{pos2};
	int toRow;
	char toCol;
	iss2 >> toCol >> toRow;
    if(outOfBound(toRow,toCol,out))return;
	int tCol = matchs(toCol);
    //move function
	mainBoard.move(fromRow,fCol,toRow,tCol,getColour());
    ++curTurn;
	mainBoard.render();
}
Computer3::Computer3(string colour): Player(colour){};
void Computer3::move(istream &in, ostream &out, Board &mainBoard, int& curTurn){
    out << "not yet implemented" << endl;

    string pos1,pos2;
	in >> pos1 >> pos2;
	istringstream iss1{pos1};
	int fromRow;
	char fromCol;
	iss1 >> fromCol >> fromRow;
    if(outOfBound(fromRow,fromCol,out))return;
	int fCol = matchs(fromCol);
	istringstream iss2{pos2};
	int toRow;
	char toCol;
	iss2 >> toCol >> toRow;
    if(outOfBound(toRow,toCol,out))return;
	int tCol = matchs(toCol);
    //move function
	mainBoard.move(fromRow,fCol,toRow,tCol,getColour());
    ++curTurn;
	mainBoard.render();
}