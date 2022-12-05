#include "player.h"
#include "board.h"
#include <iostream>
#include <map>
#include <utility>
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
vector<pair<int,int>> trans(const vector<Vec> &v){
	vector<pair<int,int>> p;
	for(Vec i: v){
		p.emplace_back(make_pair(i.row,i.col));
	}
	return p;
}
void Computer1::move(istream &in, ostream &out, Board &mainBoard, int& curTurn){
	vector<pair<int,int>> list;
	map<pair<int,int>,vector<pair<int,int>>> moves;
	//set up list of all pieces that we can move and a map of with key pieces and vector<Vec> of their possible move
	for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            auto p = mainBoard.getPiece(row,col);
            if (p != nullptr){
                if (p->getColor() == getColour()) {
					Vec v = Vec(row,col);
					pair<int,int> vv (v.row,v.col);
					vector<Vec> m = mainBoard.possibleMoves(mainBoard.getPiece(v.row,v.col),v.row,v.col);
					vector<pair<int,int>> possiMoves = trans(m);
					if(possiMoves.size() != 0){
						vector<pair<int,int>> verified;
						for(size_t k = 0; k < possiMoves.size(); ++k){
							if(mainBoard.isLegalMove(v.row,v.col,m[k].row,m[k].col,getColour())){
								verified.emplace_back(pair<int,int>(possiMoves[k].first,possiMoves[k].second));
							}
						}
						if(verified.size() != 0){
							list.emplace_back(vv);
							moves[vv] = verified;
						}
					}else{
						continue;
					}
                }
            }
        }
    }
	//randomly choose a piece and then randomly choose their move 
	int random = rand() % list. size();
	pair<int,int> vs = list[random];//get a random piece from the list
	vector<pair<int,int>> tmpmoves = moves[vs];
	//get all moves of the pieces in the map
	int random2 = rand() % tmpmoves. size();
	pair<int,int> vsmove = tmpmoves[random2]; 
	//get a random move from all the moves
	cout << vs.first << vs.second << " to " <<vsmove.first << vsmove.second << endl;
	mainBoard.move(vs.first,vs.second,vsmove.first,vsmove.second, getColour());
	mainBoard.render();
	++curTurn;
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