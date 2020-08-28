#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "observer.h"
class Observer;

class Subject: public std::enable_shared_from_this <Subject>{
    std::vector<std::shared_ptr<Observer>> observers;

  public:
    void attach(std::shared_ptr<Observer> o);  
    void notifyObservers();
    virtual ~Subject()=0;
    virtual std::string getName()=0;

};

#endif
