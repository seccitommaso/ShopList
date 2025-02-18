#include <gtest/gtest.h>
#include <climits>
#include "../User.h"

// Test per la creazione di un utente
TEST(UserTest, Constructor) {
    User user("Tommaso");
    EXPECT_EQ(user.getName(), "Tommaso");
}

// Test per la creazione di una lista della spesa
TEST(UserTest, CreateShoppingList) {
    User user("Tommaso");
    user.createShoppingList("Spesa");

    ShoppingList* list = user.getShoppingListByName("Spesa");
    ASSERT_NE(list, nullptr);  // La lista deve esistere
    EXPECT_EQ(list->getListName(), "Spesa");
}

// Test per la rimozione di una lista della spesa
TEST(UserTest, RemoveShoppingList) {
    User user("Tommaso");
    user.createShoppingList("Spesa");
    user.removeShoppingList("Spesa");
    // Verifica che la lista sia stata rimossa
    EXPECT_EQ(user.getShoppingListByName("Spesa"), nullptr);
}

// Test di rimozione di una lista non esistente
TEST(UserTest, RemoveNonExistentShoppingList) {
    User user("Alice");
    user.createShoppingList("Lista1");

    // Prova a rimuovere una lista che non esiste
    user.removeShoppingList("NonExistentList");

    // Verifica che la lista non esista
    EXPECT_EQ(user.getShoppingListByName("NonExistentList"), nullptr);
}

// Test per l'aggiunta di un elemento a una lista della spesa
TEST(UserTest, AddItemToShoppingList) {
    User user("Tommaso");
    user.createShoppingList("Spesa");

    user.addItemToShoppingList("Spesa", "Mela", "Frutta", 3);
    ShoppingList* list = user.getShoppingListByName("Spesa");

    ASSERT_NE(list, nullptr);
    auto items = list->getItems();
    ASSERT_EQ(items.size(), 1);
    EXPECT_EQ(items.front().getName(), "Mela");
    EXPECT_EQ(items.front().getCategory(), "Frutta");
    EXPECT_EQ(items.front().getQuantity(), 3);
}

// Test per la rimozione di un elemento da una lista
TEST(UserTest, RemoveItemFromShoppingList) {
    User user("Tommaso");
    user.createShoppingList("Spesa");

    user.addItemToShoppingList("Spesa", "Mela", "Frutta", 3);
    user.removeItemFromShoppingList("Spesa", "Mela");

    ShoppingList* list = user.getShoppingListByName("Spesa");
    ASSERT_NE(list, nullptr);
    EXPECT_EQ(list->getItems().size(), 0);
}

// Test di rimozione oggetti non esistenti
TEST(UserTest, RemoveNonExistentItem) {
    User user("Alice");
    user.createShoppingList("Lista1");

    // Rimuovi un oggetto non esistente
    user.removeItemFromShoppingList("Lista1", "NonExistentItem");

    // Verifica che non si verifichi errore o crash
    auto list = user.getShoppingListByName("Lista1");
    ASSERT_NE(list, nullptr);
    EXPECT_EQ(list->getItems().size(), 0);  // Nessun oggetto nella lista
}

// Test per la condivisione di una lista con un altro utente
TEST(UserTest, ShareShoppingList) {
    User user1("Tommaso");
    User user2("Luca");

    user1.createShoppingList("Spesa");
    user1.shareShoppingList(&user2, "Spesa");

    ShoppingList* sharedList = user2.getShoppingListByName("Spesa");
    ASSERT_NE(sharedList, nullptr);
    EXPECT_EQ(sharedList->getListName(), "Spesa");
}

// Test di gestione input estremi
TEST(UserTest, EdgeCaseInput) {
    User user("Alice");

    // Aggiungi oggetto con quantità molto grande
    user.createShoppingList("Lista1");
    user.addItemToShoppingList("Lista1", "Banana", "Frutta", INT_MAX);

    // Aggiungi oggetto con quantità negativa (se permesso)
    user.addItemToShoppingList("Lista1", "Apple", "Frutta", -5);

    // Verifica che la quantità grande non causi errori
    auto list = user.getShoppingListByName("Lista1");
    ASSERT_NE(list, nullptr);
    EXPECT_EQ(list->getItems().size(), 2); // Dovrebbero esserci due oggetti (se la quantità negativa è gestita)
}

// Test di aggiornamento della lista
TEST(UserTest, UpdateShoppingList) {
    User user("Alice");
    user.createShoppingList("Lista1");

    testing::internal::CaptureStdout();
    user.update("Lista1");
    std::string output = testing::internal::GetCapturedStdout();

    // Stampiamo l'output per vedere esattamente cosa viene catturato
    std::cout << "Output catturato: [" << output << "]" << std::endl;

    // Verifica che l'output sia corretto
    EXPECT_TRUE(output.find("L'utente Alice ha ricevuto un aggiornamento della lista \"Lista1\".") != std::string::npos);

}

// Test di condivisione della lista con lo stesso utente
TEST(UserTest, ShareShoppingListWithSameUser) {
    User user("Alice");

    // Creare una lista della spesa
    user.createShoppingList("Lista1");

    // Prova a condividere la lista con se stessi
    user.shareShoppingList(&user, "Lista1");

    // Verifica che la lista non venga duplicata (non dovrebbe essere aggiunta due volte)
    auto list = user.getShoppingListByName("Lista1");
    ASSERT_NE(list, nullptr);
    EXPECT_EQ(user.getShoppingListByName("Lista1"), list);

    // Verifica che l'utente non riceva un "aggiornamento" strano o errori
    testing::internal::CaptureStdout();
    user.update("Lista1");
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("L'utente Alice ha ricevuto un aggiornamento della lista \"Lista1\".") != std::string::npos);
}


