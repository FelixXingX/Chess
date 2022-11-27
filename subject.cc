#include"subject.h"
#include"observer.h"
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
