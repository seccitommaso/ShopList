
#ifndef SHOPLIST_USER_H
#define SHOPLIST_USER_H

#include <string>
#include "Observer.h"
#include "ShoppingList.h"
#include <iostream>
// Classe che rappresenta un Utente (ConcreteObserver)
class User : public Observer{
private:
    std::string name;
    std::list<ShoppingList*> shoppingLists;
public:
    explicit User(std::string  n);
    void createShoppingList(const std::string& listName);
    void removeShoppingList(const std::string& listName);
    ShoppingList* getShoppingListByName(const std::string& listName);
    void addItemToShoppingList(const std::string& listName, const std::string& itemName, const std::string& category, int quantity);
    void removeItemFromShoppingList(const std::string& listName, const std::string& itemName);
    void viewShoppingList(const std::string& listName);
    void viewItemsToBuy(const std::string& listName);
    void markItemAsPurchased(const std::string &listName, const std::string &itemName);
    void shareShoppingList(User* otherUser, const std::string& listName);
    void update(const std::string& listName)override;
    void viewAllShoppingLists();
    [[nodiscard]] const std::string &getName() const;
    ~User() override;
};

#endif //SHOPLIST_USER_H
