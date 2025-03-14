
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
bool ShoppingList::markItemAsPurchased(const std::string &itemName) {
    for (auto& item : items) {
        if (item.getName() == itemName) {
            if (!item.isPurchased()) {
                item.setPurchased(true);
                notify(listName);
                return true;//successo
            }
            return false;//già acquistato
        }
    }
    return false;//non trovato
}


void ShoppingList::addItem(const Item &item) {
    items.push_back(item);
    notify(listName);
}

bool ShoppingList::removeItem(const std::string &itemName) {
    for (auto it = items.begin(); it != items.end();it++ ) {
        if (it->getName() == itemName) {
            it = items.erase(it);
            notify(listName);
            return true;
        }
    }
   return false;
}

const std::list<Item> &ShoppingList::getItems() const{
    return items;
}

const std::string &ShoppingList::getListName() const {
    return listName;
}