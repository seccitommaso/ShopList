
#include "ShoppingList.h"
#include <algorithm>
#include <utility>

ShoppingList::ShoppingList(std::string name):listName(std::move(name)) {}

void ShoppingList::subscribe(Observer *o) {
    observers.push_back(o);
}

void ShoppingList::unsubscribe(Observer *o) {
    observers.remove(o);
}

void ShoppingList::notify(const std::string& nameList) {
    for(auto& observer : observers){
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

int ShoppingList::countItemsToBuy() const {
    int count = 0;
    for (const auto& item : items) {
        if (!item.isPurchased()) {
            count++;
        }
    }
    return count;
}

int ShoppingList::countTotalItems() const {
    return items.size();
}

void ShoppingList::addItem(const Item &item) {
    items.push_back(item);
    notify(listName);
}

bool ShoppingList::removeItem(const std::string &itemName) {
    auto it = std::remove_if(items.begin(), items.end(), [&itemName](const Item& item) {
        return item.getName() == itemName;
    });
    if (it != items.end()) {
        items.erase(it, items.end());
        notify(listName);
        return true;
    }
    return false;
}


const std::string &ShoppingList::getListName() const {
    return listName;
}

// Nuovo metodo per ottenere un elemento tramite indice
const Item& ShoppingList::getItemAt(size_t index) const {
    if (index < items.size()) {
        return items[index];
    }
    throw std::out_of_range("Index out of range");
}
// Nuovo metodo per ottenere lista di oggetti da acquistare
std::vector<Item> ShoppingList::getItemsToBuy() const {
    std::vector<Item> itemsToBuy;
    for (const auto& item : items) {
        if (!item.isPurchased()) {
            itemsToBuy.push_back(item);
        }
    }
    return itemsToBuy;
}