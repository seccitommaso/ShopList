//
// Created by tommaso on 17/02/25.
//

#ifndef SHOPLIST_OBSERVER_H
#define SHOPLIST_OBSERVER_H

#include <string>

class Observer {
public:
    virtual ~Observer()= default;
    virtual void update(const std::string& listName)=0;
};

#endif //SHOPLIST_OBSERVER_H
