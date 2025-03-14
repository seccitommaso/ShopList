
#include "User.h"
#include <utility>

User::User(std::string n) : name(std::move(n)) {}

void User::createShoppingList(const std::string& listName) {
    auto* newList= new ShoppingList(listName);
    newList->subscribe(this);
    shoppingLists.push_back(newList);
    std::cout << "Lista \"" << listName << "\" creata con successo."<<std::endl;
}

void User::removeShoppingList(const std::string &listName) {
    bool listFound=false;
    for(auto it : shoppingLists){
        if(it->getListName()==listName) {
            it->unsubscribe(this);
            shoppingLists.remove(it);
            delete it;
            std::cout<<"Lista "<<listName<<" rimossa"<<std::endl;
            listFound=true;
            break;
        }
    }
    if(!listFound){
        std::cout<<"Lista "<<listName<<" non trovata"<<std::endl;
    }
}

ShoppingList *User::getShoppingListByName(const std::string &listName) {
    for(auto it: shoppingLists) {
        if (it->getListName() == listName) {
            return it;
        }
    }
    return nullptr;
}

void User::addItemToShoppingList(const std::string &listName, const std::string &itemName, const std::string &category,int quantity) {
    auto list= getShoppingListByName(listName);
    if(list!= nullptr){
        list->addItem(Item(itemName,category,quantity));
        std::cout << "Oggetto \"" << itemName << "\" aggiunto alla lista \"" << listName << "\"."<<std::endl;
    }else{
        std::cout<<"Lista "<<listName<<" non trovata"<<std::endl;
    }
}

void User::removeItemFromShoppingList(const std::string &listName, const std::string &itemName) {
    auto list = getShoppingListByName(listName);  // Trova la lista
    if (list != nullptr) {  // Verifica se la lista esiste
        bool itemRemoved = list->removeItem(itemName);  // Rimuove l'oggetto dalla lista

        if (itemRemoved) {
            std::cout << "Oggetto \"" << itemName << "\" rimosso dalla lista \"" << listName << "\"." << std::endl;
        } else {
            std::cout << "Oggetto \"" << itemName << "\" non trovato nella lista \"" << listName << "\"." << std::endl;
        }
    } else {
        std::cout << "Lista \"" << listName << "\" non trovata." << std::endl;
    }
}

void User::viewShoppingList(const std::string& listName) {
    auto list= getShoppingListByName(listName);
    if(list!= nullptr){
        const std::list<Item>& items = list->getItems();
        std::cout << "Lista della spesa " << list->getListName() << " di " << name << ":"<<std::endl;
        for (const auto& item : items) {
            std::cout << "- " << item.getName() << " (" << item.getCategory() << "), Quantità: " << item.getQuantity() <<std::endl;
        }
    } else {
        std::cout<<"Lista "<<listName<<" non trovata"<<std::endl;
    }
}
void User::shareShoppingList(User* otherUser, const std::string& listName) {
    auto list = getShoppingListByName(listName);
    if (list != nullptr) {
        list->subscribe(otherUser);
        otherUser->shoppingLists.push_back(list);
        std::cout << "Lista \"" << listName << "\" condivisa con " << otherUser->getName() << "."<<std::endl;
    } else {
        std::cout << "Lista \"" << listName << "\" non trovata."<<std::endl;
    }
}
void User::update(const std::string& listName) {
    std::cout<<"L'utente "<<name<<" ha ricevuto un aggiornamento della lista \""<<listName<<"\"."<<std::endl;
}

void User::viewAllShoppingLists() {
    std::cout << "Liste della spesa di " << name << ":"<<std::endl;
    for (auto list : shoppingLists) {
        viewShoppingList(list->getListName());
    }
}
User::~User()  {
    for(auto list : shoppingLists){
        list->unsubscribe(this);
    }
}



const std::string &User::getName() const {
    return name;
}
