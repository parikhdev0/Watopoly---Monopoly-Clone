#include "subject.h"
void Subject::attach(std::shared_ptr<Observer> o) { observers.emplace_back(o); }

void Subject::notifyObservers() {
    for (auto &ob : observers) ob->notify( shared_from_this() );
}

std::string Subject::getName(){
	return getName();
}

Subject::~Subject(){}

