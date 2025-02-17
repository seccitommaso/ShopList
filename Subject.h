//
// Created by tommaso on 17/02/25.
//

#ifndef SHOPLIST_SUBJECT_H
#define SHOPLIST_SUBJECT_H

#include "Observer.h"
class Subject {
public:
    virtual void notify(const std::string& listName)=0;
    virtual ~Subject()= default;
    virtual void subscribe(Observer* o)=0;
    virtual void unsubscribe(Observer* o)=0;
};

#endif //SHOPLIST_SUBJECT_H
