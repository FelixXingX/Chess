#include "observer.h"
#include "board.h"
#include "textdisplay.h"
#include <iostream>
using namespace std;
void TextDisplay::notify(){
    for(int i = 0 ; i < rows; ++ i){
        for(int j = 0; j < cols; ++ j){
            cout << 8 - i << ' ';
            unique_ptr<Piece> piece = make_unique<Piece>(subject->getPiece(i,j));
            if(piece == nullptr){
                
            }else{
                cout << piece->getName();
            }
        }
    }

}