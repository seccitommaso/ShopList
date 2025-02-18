
#include "ShoppingList.h"
#include <utility>

ShoppingList::ShoppingList(std::string name):listName(std::move(name)) {}

void ShoppingList::subscribe(Observer *o) {
    observers.push_back(o);
}

void ShoppingList::unsubscribe(Observer *o) {
    observers.remove(o);
}

void ShoppingList::notify(const std::string& nameList) {
    for(auto & observer : observers){
        observer->update(nameList);
    }
}

void ShoppingList::addItem(const Item &item) {
    items.push_back(item);
    notify(listName);
}

void ShoppingList::removeItem(const std::string &itemName) {
    bool itemFound=false;
    for (auto it = items.begin(); it != items.end();it++ ) {
        if (it->getName() == itemName) {
            it = items.erase(it);
            itemFound=true;
            notify(listName);
        }
    }
    if(!itemFound){
        std::cout<<"Item "<<itemName<<" non trovato"<<std::endl;
    }
}

const std::list<Item> &ShoppingList::getItems() const{
    return items;
}

const std::string &ShoppingList::getListName() const {
    return listName;
}