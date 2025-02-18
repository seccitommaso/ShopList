
#ifndef SHOPLIST_SHOPPINGLIST_H
#define SHOPLIST_SHOPPINGLIST_H


#include "Item.h"
#include "Subject.h"
#include <list>
// Classe che rappresenta una lista della spesa (ConcreteSubject)
class ShoppingList : public Subject{
private:
    std::list<Observer*> observers;
    std::string listName;
    std::list<Item>items;

public:
    explicit ShoppingList(std::string name);
    void subscribe(Observer *o)override;
    void unsubscribe(Observer *o)override;
    void notify(const std::string& nameList)override;
    void addItem(const Item& item);
    void removeItem(const std::string& itemName);
    [[nodiscard]] const std::list<Item>& getItems() const;
    [[nodiscard]] const std::string &getListName() const;
};



#endif //SHOPLIST_SHOPPINGLIST_H
