#include <gtest/gtest.h>
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
    EXPECT_EQ(user.getShoppingListByName("Spesa"), nullptr);
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
