
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
    auto list = getShoppingListByName(listName);
    if (list != nullptr) {
        std::cout << "Lista della spesa " << list->getListName() << " di " << name << ":" << std::endl;

        for (size_t i = 0; i < list->countTotalItems(); ++i) {
            try {
                const auto& item = list->getItemAt(i);
                std::string status = item.isPurchased() ? "Acquistato" : "Da acquistare";
                std::cout << "- " << item.getName() << " (" << item.getCategory() << "), Quantità: " << item.getQuantity() << " --> " << status << "\n";
            } catch (const std::out_of_range&) {
                std::cout << "Errore: indice fuori dai limiti.\n";
            }
        }
    } else {
        std::cout << "Lista " << listName << " non trovata" << std::endl;
    }
}

void User::viewItemsToBuy(const std::string& listName) {
    auto list = getShoppingListByName(listName);

    if (!list) {
        std::cout << "Lista \"" << listName << "\" non trovata." << std::endl;
        return;
    }

    // Stampa il numero di oggetti ancora da comprare
    int itemsToBuy = list->countItemsToBuy();
    std::cout << "Numero di oggetti ancora da comprare nella lista \""
              << list->getListName() << "\": " << itemsToBuy << std::endl;

    std::cout << "Oggetti da comprare nella lista \"" << list->getListName() << "\":" << std::endl;

    bool hasItemsToBuy = false;
    for (size_t i = 0; i < list->countTotalItems(); ++i) {
        const auto& item = list->getItemAt(i);
        if (!item.isPurchased()) {
            std::cout << "- " << item.getName() << " (" << item.getCategory()
                      << "), Quantità: " << item.getQuantity() << std::endl;
            hasItemsToBuy = true;
        }
    }

    if (!hasItemsToBuy) {
        std::cout << "Tutti gli oggetti sono stati acquistati!" << std::endl;
    }
}

void User::markItemAsPurchased(const std::string& listName, const std::string& itemName) {
    auto list = getShoppingListByName(listName);
    if (!list) {
        std::cout << "Lista \"" << listName << "\" non trovata.\n";
        return;
    }

    bool result = list->markItemAsPurchased(itemName);
    if (result) {
        std::cout << "Oggetto \"" << itemName << "\" segnato come acquistato.\n";
    } else {
        std::cout << "Oggetto \"" << itemName << "\" non trovato o già acquistato.\n";
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
