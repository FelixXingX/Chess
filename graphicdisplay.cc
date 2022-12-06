#include "observer.h"
#include "board.h"
#include "window.h"
#include "graphicdisplay.h"
using namespace std;
GraphicsDisplay::GraphicsDisplay(Board *sj, shared_ptr<Xwindow> window, int rows, int cols, int scale): subject{sj}, window{move(window)}, rows{rows}, cols{cols}, scale{scale}{
    subject->attach(this);
}

void GraphicsDisplay::match(char a, int y, int x, int scale){
    switch(a){
                case 'p':
                {
                    window->drawPawn(x, y, 1,scale);
                    //window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                case 'P':
                {
                    window->drawPawn(x, y, 0,scale);
                    //window->fillRectangle(x * scale, y * scale,scale,scale,0);
                    break;
                }
                case 'r':
                {
                    window->drawRook(x, y, 1,scale);
                    //window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                case 'R':
                {
                    window->drawRook(x, y,0,scale);
                    //window->fillRectangle(x * scale, y * scale,scale,scale,0);
                    break;
                }
                case 'n':
                {
                    window->drawKnight(x, y,1,scale);
                    //window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                case 'N':
                {
                    window->drawKnight(x, y, 0,scale);
                    //window->fillRectangle(x * scale, y * scale,scale,scale,0);
                    break;
                }
                case 'b':
                {
                    window->drawBishop(x, y, 1,scale);
                    //window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                case 'B':
                {
                    window->drawBishop(x, y, 0,scale);
                    //window->fillRectangle(x * scale, y * scale,scale,scale,0);
                    break;
                }
                case 'q':
                {
                    window->drawQueen(x, y, 1,scale);
                    //window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                case 'Q':
                {
                    window->drawQueen(x, y, 0,scale);
                    //window->fillRectangle(x * scale, y * scale,scale,scale,0);
                    break;
                }
                case 'k':
                {
                    window->drawKing(x, y, 1,scale);
                    //window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                case 'K':
                {
                    window->drawKing(x, y, 0,scale);
                    //window->fillRectangle(x * scale, y * scale,scale,scale,0);      
                    break;
                }
                case ' ':
                {
                    window->fillRectangle(x * scale, y * scale,scale,scale,10);
                    break;
                }
                case '_':
                {
                    window->fillRectangle(x * scale, y * scale,scale,scale,9);
                    break;
                }
                
            }
}

void GraphicsDisplay::notify(){
    for(int i = rows; i > 0; --i){
        for(int j = 1; j < cols + 1; ++j){
            if(i % 2 == 0){
            if(j % 2 == 0){
                match('_',rows-i,j,scale);
            }else{
                match(' ',rows-i,j,scale);
            }
            }else{
            if(j % 2 == 0){
                match(' ',rows-i,j,scale);
            }else {
                match('_',rows-i,j,scale);
            }
            }
        }
    }
    for(int i = rows; i > 0; --i){
        for(int j = 1; j < cols + 1; ++j){
           char a = subject->getState(i,j);
           match(a,rows-i ,j,scale);
       }
    }
}

void GraphicsDisplay::notify(int row, int col){
    if(row % 2 == 0){
            if(col % 2 == 0){
                match('_',rows-row,col,scale);
            }else{
                match(' ',rows-row,col,scale);
            }
            }else{
            if(col % 2 == 0){
                match(' ',rows-row,col,scale);
            }else {
                match('_',rows-row,col,scale);
            }
        }
    char a = subject->getState(row,col);
    match(a,rows-row,col,scale);
}

