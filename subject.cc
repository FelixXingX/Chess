#include"subject.h"
#include"observer.h"
#include "graphicdisplay.h"
#include "textdisplay.h"
void Subject::attach(Observer* ob){
	observers.emplace_back(ob);
}

void Subject::detach(Observer* ob){
	for(auto it = observers.begin(); it != observers.end(); ++it){
		if(*it == ob){
			observers.erase(it);
			break;
		}
	}
}

void Subject::notifyObservers(){
	for(auto ob: observers){
		ob->notify();
	}
}
void Subject::notifyObservers(char t,int x, int y){
	for(auto ob: observers){
		if(dynamic_cast<GraphicsDisplay *>(ob) != nullptr && t == 'g'){
			ob->notify(x,y);
		}else if(dynamic_cast<TextDisplay *>(ob) != nullptr && t == 't'){
			ob->notify(x,y);
		}
	}
}
