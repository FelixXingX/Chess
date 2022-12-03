#include "observer.h"
#include "board.h"
#include "window.h"
#include "graphicdisplay.h"

GraphicsDisplay::GraphicsDisplay(Board *sj, Xwindow *window, int rows, int cols, int scale): subject{sj}, window{window}, rows{rows}, cols{cols}, scale{scale}{
    subject->attach(this);
}

void match(char a, Xwindow *window, int x, int y, int scale){
    switch(a){
                case 'p':
                {
                    //window->drawPawn(x, y, 1,scale);
                    window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                case 'P':
                {
                   // window->drawPawn(x, y, 0,scale);
                   window->fillRectangle(x * scale, y * scale,scale,scale,0);
                    break;
                }
                case 'r':
                {
                    //window->drawRook(x, y, 1,scale);
                    window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                case 'R':
                {
                    //window->drawRook(x, y, 0,scale);
                    window->fillRectangle(x * scale, y * scale,scale,scale,0);
                    break;
                }
                case 'n':
                {
                    //window->drawKnight(x, y, 1,scale);
                    window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                case 'N':
                {
                    //window->drawKnight(x, y, 0,scale);
                    window->fillRectangle(x * scale, y * scale,scale,scale,0);
                    break;
                }
                case 'b':
                {
                    //window->drawBishop(x, y, 1,scale);
                    window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                case 'B':
                {
                    //window->drawBishop(x, y, 0,scale);
                    window->fillRectangle(x * scale, y * scale,scale,scale,0);
                    break;
                }
                case 'q':
                {
                    //window->drawQueen(x, y, 1,scale);
                    window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                case 'Q':
                {
                    //window->drawQueen(x, y, 0,scale);
                    window->fillRectangle(x * scale, y * scale,scale,scale,0);
                    break;
                }
                case 'k':
                {
                    //window->drawKing(x, y, 1,scale);
                    window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                case 'K':
                {
                    //window->drawKing(x, y, 0,scale);
                    window->fillRectangle(x * scale, y * scale,scale,scale,0);      
                    break;
                }
                case ' ':
                {
                    window->fillRectangle(x * scale, y * scale,scale,scale,0);
                    break;
                }
                case '_':
                {
                    window->fillRectangle(x * scale, y * scale,scale,scale,1);
                    break;
                }
                
            }
}

void GraphicsDisplay::notify(){
    for(int i = rows; i > 0; --i){
        for(int j = 1; j < cols; ++j){
            char a = subject->getState(i,j);
            match(a, window,i,j,scale);
        }
    }
}

void GraphicsDisplay::notify(int row, int col){
    char a = subject->getState(row,col);
    match(a,window,row,col,scale);
}

