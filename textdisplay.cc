#include "observer.h"
#include "board.h"
#include "textdisplay.h"
#include <iostream>
using namespace std;
void TextDisplay::notify(){
    for(int i = rows ; i < 1; -- i){
        cout << 8 - i << ' ';
        for(int j = cols; j < 1; -- j){
            cout << subject->getState(rows,cols);
        }
        cout << endl;
    }
    cout << msg << endl;
}
void TextDisplay::changeMsg(string n){
    msg = n;
}
TextDisplay::TextDisplay(Board* subject, string msg): subject{subject}, msg{msg}{
			subject->attach(this);
}