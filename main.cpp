#include <iostream>
#include <vector>
#include "User.h"

// Funzione per creare un nuovo utente
User* createUser(std::vector<User*>& users) {
    std::string userName;
    std::cout << "Inserisci il nome del nuovo utente: ";
    std::cin.ignore();
    std::getline(std::cin, userName);

    User* newUser = new User(userName);
    users.push_back(newUser);

    std::cout << "Utente \"" << userName << "\" creato con successo.\n";
    return newUser;
}

// Funzione per selezionare un utente esistente
User* selectUser(const std::vector<User*>& users) {
    if (users.empty()) {
        std::cout << "Nessun utente presente. Creane uno nuovo.\n";
        return nullptr;
    }

    std::cout << "\n--- Seleziona un utente ---\n";
    for (size_t i = 0; i < users.size(); ++i) {
        std::cout << i + 1 << ". " << users[i]->getName() << "\n";
    }

    int choice;
    std::cout << "Scegli un numero: ";
    std::cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(users.size())) {
        std::cout << " Utente \"" << users[choice - 1]->getName() << "\" selezionato.\n";
        return users[choice - 1];
    }

    std::cout << "Scelta non valida.\n";
    return nullptr;
}

// Funzione per mostrare il menu della lista della spesa
void showShoppingListMenu(User* user, const std::vector<User*>& users) {
    if (!user) {
        std::cout << " Nessun utente selezionato.\n";
        return;
    }

    int choice;
    do {
        std::cout << "\n--- Menu Lista della Spesa di "<<user->getName()<<"---\n"
                  << "1  Crea una nuova lista\n"
                  << "2  Visualizza tutte le liste\n"
                  << "3  Aggiungi un oggetto a una lista\n"
                  << "4  Rimuovi un oggetto da una lista\n"
                  << "5. Marca un oggetto come acquistato\n"
                  << "6. Elimina una lista\n"
                  << "7. Condividi una lista\n"
                  << "8. Torna al menu principale\n"
                  << "- Scegli un'opzione: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::string listName;
                std::cout << "Nome della nuova lista: ";
                std::getline(std::cin, listName);
                user->createShoppingList(listName);
                break;
            }
            case 2:
                user->viewAllShoppingLists();
                break;
            case 3: {
                std::string listName, itemName, category;
                int quantity;
                std::cout << "Nome della lista: ";
                std::getline(std::cin, listName);
                std::cout << "Nome dell'oggetto: ";
                std::getline(std::cin, itemName);
                std::cout << "Categoria: ";
                std::getline(std::cin, category);
                std::cout << "Quantita: ";
                std::cin >> quantity;
                std::cin.ignore();

                user->addItemToShoppingList(listName, itemName, category, quantity);
                break;
            }
            case 4: {
                std::string listName, itemName;
                std::cout << "Nome della lista: ";
                std::getline(std::cin, listName);
                std::cout << "Nome dell'oggetto da rimuovere: ";
                std::getline(std::cin, itemName);
                user->removeItemFromShoppingList(listName, itemName);
                break;
            }
            case 5: {
                std::string listName, itemName;
                std::cout << "Nome della lista: ";
                std::getline(std::cin, listName);
                std::cout << "Nome dell'oggetto da marcare/smarcare: ";
                std::getline(std::cin, itemName);
                user->markItemAsPurchasedInList(listName, itemName);
                break;
            }
            case 6: {
                std::string listName;
                std::cout << "Nome della lista da eliminare: ";
                std::getline(std::cin, listName);
                user->removeShoppingList(listName);
                break;
            }
            case 7: {
                std::string listName;
                std::cout << "Nome della lista da condividere: ";
                std::getline(std::cin, listName);

                User* otherUser = selectUser(users);
                if (otherUser && otherUser != user) {
                    user->shareShoppingList(otherUser, listName);
                } else {
                    std::cout << " Non puoi condividere la lista con te stesso o l'utente non esiste.\n";
                }
                break;
            }
            case 8:
                std::cout << " Tornando al menu principale...\n";
                break;
            default:
                std::cout << " Opzione non valida. Riprova.\n";
        }
    } while (choice != 7);
}

// Funzione principale con menu generale
int main() {
    std::vector<User*> users;
    User* currentUser = nullptr;
    int choice;

    do {
        std::cout << "\n===  Gestione Liste della Spesa ===\n"
                  << "1 crea un nuovo utente\n"
                  << "2 Seleziona un utente\n"
                  << "3 Accedi al menu della lista della spesa\n"
                  << "4 Esci\n"
                  << "- Scegli un'opzione: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                currentUser = createUser(users);
                break;
            case 2:
                currentUser = selectUser(users);
                break;
            case 3:
                showShoppingListMenu(currentUser, users);
                break;
            case 4:
                std::cout << " Uscita dal programma...\n";
                break;
            default:
                std::cout << " Opzione non valida. Riprova.\n";
        }
    } while (choice != 4);

    // Pulizia della memoria per evitare memory leaks
    for (User* user : users) {
        delete user;
    }
}
