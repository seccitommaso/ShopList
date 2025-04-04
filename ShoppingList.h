
#ifndef SHOPLIST_SHOPPINGLIST_H
#define SHOPLIST_SHOPPINGLIST_H


#include "Item.h"
#include "Subject.h"
#include <list>
#include <vector>
// Classe che rappresenta una lista della spesa (ConcreteSubject)
class ShoppingList : public Subject{
private:
    std::list<Observer*> observers;
    std::string listName;
    std::vector<Item>items;

public:
    explicit ShoppingList(std::string name);
    void subscribe(Observer *o)override;
    void unsubscribe(Observer *o)override;
    void notify(const std::string& nameList)override;
    bool markItemAsPurchased(const std::string& itemName);
    [[nodiscard]] int countItemsToBuy() const;
    [[nodiscard]] int countTotalItems() const;
    const Item& getItemAt(size_t index) const;//metodo per prendere l'elemento alla posizione i-esima
    void addItem(const Item& item);
    bool removeItem(const std::string& itemName);
    [[nodiscard]] const std::string &getListName() const;
};



#endif //SHOPLIST_SHOPPINGLIST_H
