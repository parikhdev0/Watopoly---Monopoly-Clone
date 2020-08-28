#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <memory>
class Subject;

class Observer {
  public:
    virtual void notify(std::shared_ptr<Subject> whoNotified ) = 0; 
    virtual void notify() = 0; 
    virtual ~Observer() = default;
};

#endif
