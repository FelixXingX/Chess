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
		//mainBoard.render('g',toRow,tCol);
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
					pair<int,int> vv (row,col);
					vector<pair<int,int>> possiMoves = trans(mainBoard.possibleMoves(mainBoard.getPiece(row,col),row,col));
					if(possiMoves.size() != 0){
						vector<pair<int,int>> verified;
						for(size_t k = 0; k < possiMoves.size(); ++k){
							if(mainBoard.isLegalMove(row,col,possiMoves[k].first,possiMoves[k].second,getColour())){
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
	mainBoard.render('t',1,1);
	//mainBoard.render('g',vs.first,vs.second);
	//mainBoard.render('g',vsmove.first,vsmove.second);
	++curTurn;
}
Computer2::Computer2(string colour): Player(colour){};
void Computer2::move(istream &in, ostream &out, Board &mainBoard, int& curTurn){
    vector<pair<int,int>> list;
	vector<pair<int,int>> listt;
	vector<pair<int,int>> listc;
	map<pair<int,int>,vector<pair<int,int>>> checked;
	map<pair<int,int>,vector<pair<int,int>>> takes;
	map<pair<int,int>,vector<pair<int,int>>> moves;
	//set up list of all pieces that we can move and a map of with key pieces and vector<Vec> of their possible move
	for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            auto p = mainBoard.getPiece(row,col);
            if (p != nullptr){
                if (p->getColor() == getColour()) {
					pair<int,int> vv (row,col);
					vector<pair<int,int>> possiMoves = trans(mainBoard.possibleMoves(mainBoard.getPiece(row,col),row,col));
					if(possiMoves.size() != 0){
						vector<pair<int,int>> verifiedchecked;
						vector<pair<int,int>> verifiedtakes;
						vector<pair<int,int>> verified;
						for(size_t k = 0; k < possiMoves.size(); ++k){
							if(mainBoard.isLegalMove(row,col,possiMoves[k].first,possiMoves[k].second,getColour())){
								verified.emplace_back(pair<int,int>(possiMoves[k].first,possiMoves[k].second));
								if(mainBoard.getPiece(possiMoves[k].first,possiMoves[k].second) != nullptr){
									verifiedtakes.emplace_back(pair<int,int>(possiMoves[k].first,possiMoves[k].second));
								}
								if(mainBoard.botChecked(possiMoves[k].first,possiMoves[k].second,getColour())){
									verifiedchecked.emplace_back(pair<int,int>(possiMoves[k].first,possiMoves[k].second));
								}
							}
						}
						if(verified.size() != 0){
							list.emplace_back(vv);
							moves[vv] = verified;
						}
						if(verifiedtakes.size() != 0){
							listt.emplace_back(vv);
							takes[vv] = verifiedtakes;
						}
						if(verifiedchecked.size() != 0){
							listc.emplace_back(vv);
							checked[vv] = verifiedchecked;
						}
					}else{
						continue;
					}
                }
            }
        }
    }
	pair<int,int> vs;
	pair<int,int> vsmove;
	//NOt done
	//randomly choose a piece and then randomly choose their move 
	if(listc.size() != 0){
		int random = rand() % listc.size();
		vs = listc[random];//get a random piece from the list
		vector<pair<int,int>> tmpmoves = checked[vs];
		//get all moves of the pieces in the map
		int random2 = rand() % tmpmoves. size();
		vsmove = tmpmoves[random2]; 
	}else if(listt.size() != 0){
		int random = rand() % listt.size();
		vs = listt[random];//get a random piece from the list
		vector<pair<int,int>> tmpmoves = takes[vs];
		//get all moves of the pieces in the map
		int random2 = rand() % tmpmoves. size();
		vsmove = tmpmoves[random2]; 
	}else{
		int random = rand() % list.size();
		vs = list[random];//get a random piece from the list
		vector<pair<int,int>> tmpmoves = moves[vs];
		//get all moves of the pieces in the map
		int random2 = rand() % tmpmoves. size();
		vsmove = tmpmoves[random2]; 
		//get a random move from all the moves
	}
	if((vs.first != 0 && vs.second != 0 )|| (vsmove.first != 0 && vsmove.second != 0)){
		cout << vs.first << vs.second << " to " <<vsmove.first << vsmove.second << endl;
		mainBoard.move(vs.first,vs.second,vsmove.first,vsmove.second, getColour());
		mainBoard.render('t',1,1);
		//mainBoard.render('g',vs.first,vs.second);
		//mainBoard.render('g',vsmove.first,vsmove.second);
		++curTurn;
	}else{
		cout << "Fatal error occured: check computer 2 move" << endl;
	}
	
}
Computer3::Computer3(string colour): Player(colour){};
void Computer3::move(istream &in, ostream &out, Board &mainBoard, int& curTurn){
    vector<pair<int,int>> list;
	vector<pair<int,int>> listt;
	vector<pair<int,int>> listc;
	vector<pair<int,int>> listDanger;
	map<pair<int,int>,vector<pair<int,int>>> checked;
	map<pair<int,int>,vector<pair<int,int>>> takes;
	map<pair<int,int>,vector<pair<int,int>>> moves;
	//set up list of all pieces that we can move and a map of with key pieces and vector<Vec> of their possible move
	for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            auto p = mainBoard.getPiece(row,col);
            if (p != nullptr){
                if (p->getColor() == getColour()) {
					pair<int,int> vv (row,col);
					vector<pair<int,int>> possiMoves = trans(mainBoard.possibleMoves(mainBoard.getPiece(row,col),row,col));
					if(possiMoves.size() != 0){
						vector<pair<int,int>> verifiedchecked;
						vector<pair<int,int>> verifiedtakes;
						vector<pair<int,int>> verified;
						for(size_t k = 0; k < possiMoves.size(); ++k){
							if(mainBoard.isLegalMove(row,col,possiMoves[k].first,possiMoves[k].second,getColour())){
								verified.emplace_back(pair<int,int>(possiMoves[k].first,possiMoves[k].second));
								if(mainBoard.getPiece(possiMoves[k].first,possiMoves[k].second) != nullptr){
									verifiedtakes.emplace_back(pair<int,int>(possiMoves[k].first,possiMoves[k].second));
								}
								if(mainBoard.botChecked(possiMoves[k].first,possiMoves[k].second,getColour())){
									verifiedchecked.emplace_back(pair<int,int>(possiMoves[k].first,possiMoves[k].second));
								}
							}
						}
						if(verified.size() != 0){
							list.emplace_back(vv);
							moves[vv] = verified;
						}
						if(verifiedtakes.size() != 0){
							listt.emplace_back(vv);
							takes[vv] = verifiedtakes;
						}
						if(verifiedchecked.size() != 0){
							listc.emplace_back(vv);
							checked[vv] = verifiedchecked;
						}
					}else{
						continue;
					}
                }
            }
        }
    }
	//check to avoid capture
	
	for (int row = 1; row <= 8; row++) {
        for (int col = 1; col <= 8; col++) {
            auto p = mainBoard.getPiece(row,col);
            if (p != nullptr){
                if (p->getColor() != getColour()) {//if piece is an enemy
					pair<int,int> vv (row,col);//get pos of piece
					vector<pair<int,int>> possiMoves = trans(mainBoard.possibleMoves(mainBoard.getPiece(row,col),row,col));//get pieces's possible move
					if(possiMoves.size() != 0){//if it can move
						for(size_t k = 0; k < possiMoves.size(); ++k){
							if(mainBoard.isLegalMove(row,col,possiMoves[k].first,possiMoves[k].second,p->getColor())){//if piece can make a legal move at that place
								for(pair<int,int> pp : list){
									if(possiMoves[k].first == pp.first && possiMoves[k].second == pp.second){//if the piece
										listDanger.emplace_back(pair<int,int>(possiMoves[k].first,possiMoves[k].second));
										//vector<pair<int,int>> avoidMoves = trans(mainBoard.possibleMoves(mainBoard.getPiece(pp.first,pp.second),pp.first,pp.second));
										//if(avoidMoves.size() != 0){
										//	vector<pair<int,int>> verifiedanger;
										//}
									}
									
								}
									
							}
						}
					}else{
						continue;
					}
				}
			}
		}
	}
	pair<int,int> vs;
	pair<int,int> vsmove;
	//NOt done
	//randomly choose a piece and then randomly choose their move 
	if(listc.size() != 0){
		int random = rand() % listc.size();
		vs = listc[random];//get a random piece from the list
		vector<pair<int,int>> tmpmoves = checked[vs];
		//get all moves of the pieces in the map
		int random2 = rand() % tmpmoves. size();
		vsmove = tmpmoves[random2]; 
	}else if(listt.size() != 0){
		int random = rand() % listt.size();
		vs = listt[random];//get a random piece from the list
		vector<pair<int,int>> tmpmoves = takes[vs];
		//get all moves of the pieces in the map
		int random2 = rand() % tmpmoves. size();
		vsmove = tmpmoves[random2]; 
	}else if(listDanger.size()!= 0){
		int random = rand() % listDanger.size();
		vs = listDanger[random];
		vector<pair<int,int>> tmpmoves = moves[vs];
		int random2 = rand() % tmpmoves. size();
		vsmove = tmpmoves[random2]; 
	}else{
		int random = rand() % list.size();
		vs = list[random];//get a random piece from the list
		vector<pair<int,int>> tmpmoves = moves[vs];
		//get all moves of the pieces in the map
		int random2 = rand() % tmpmoves. size();
		vsmove = tmpmoves[random2]; 
		//get a random move from all the moves
	}
	if((vs.first != 0 && vs.second != 0 )|| (vsmove.first != 0 && vsmove.second != 0)){
		cout << vs.first << vs.second << " to " <<vsmove.first << vsmove.second << endl;
		mainBoard.move(vs.first,vs.second,vsmove.first,vsmove.second, getColour());
		mainBoard.render('t',1,1);
		//mainBoard.render('g',vs.first,vs.second);
		//mainBoard.render('g',vsmove.first,vsmove.second);
		++curTurn;
	}else{
		cout << "Fatal error occured: check computer 3 move" << endl;
	}
}