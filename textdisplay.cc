#include "observer.h"
#include "board.h"
#include "textdisplay.h"
#include <iostream>
using namespace std;
void TextDisplay::notify(){
    for(int i = 8; i > 0; --i){
        cout << i << " ";
        for(int j = 1; j < 9; ++j){
            cout << subject->getState(i,j);
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
