
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../ShoppingList.h"
class MockObserver : public Observer {
public:
    MOCK_METHOD(void, update, (const std::string&), (override));
};
//test per il costruttore
TEST(ShoppingListTest, ConstructorTest) {
    ShoppingList list("Spesa");
    EXPECT_EQ(list.getListName(), "Spesa");
}
//test per aggiunta di un item
TEST(ShoppingListTest, AddItemTest) {
    ShoppingList list("Spesa");
    Item item("Mela", "Frutta", 3);
    list.addItem(item);
    EXPECT_EQ(list.getItems().size(), 1);
    EXPECT_EQ(list.getItems().front().getName(), "Mela");
}
//test per rimozione di un item
TEST(ShoppingListTest, RemoveItemTest) {
    ShoppingList list("Spesa");
    Item item("Mela", "Frutta", 3);
    list.addItem(item);
    list.removeItem("Mela");
    EXPECT_TRUE(list.getItems().empty());
}
// Test per la rimozione di un item non presente
TEST(ShoppingListTest, RemoveNonExistentItemTest) {
    ShoppingList list("Spesa");

    // Rimuovi un oggetto che non esiste
    bool result = list.removeItem("Banana");

    // Verifica che l'oggetto non sia stato trovato e che la rimozione sia fallita
    EXPECT_FALSE(result);
}

//test verifica agli observer
TEST(ShoppingListTest, ObserverNotificationTest) {
    ShoppingList list("Spesa");
    MockObserver mockObserver;
    list.subscribe(&mockObserver);
    EXPECT_CALL(mockObserver, update("Spesa")).Times(1);
    Item item("Mela", "Frutta", 3);
    list.addItem(item);
}
// Test per countItemsToBuy
TEST(ShoppingListTest, TestCountItemsToBuy) {
    ShoppingList list("Spesa");
    list.addItem(Item("item1", "category1", 2));  // Aggiungi un oggetto non acquistato
    list.addItem(Item("item2", "category2", 1));  // Aggiungi un oggetto non acquistato
    list.addItem(Item("item3", "category3", 3));  // Aggiungi un oggetto acquistato

    list.markItemAsPurchased("item3");

    EXPECT_EQ(list.countItemsToBuy(), 2);
}

// Test per countTotalItems
TEST(ShoppingListTest, TestCountTotalItems) {
    ShoppingList list("Spesa");
    list.addItem(Item("item1", "category1", 2));
    list.addItem(Item("item2", "category2", 1));
    list.addItem(Item("item3", "category3", 3));

    EXPECT_EQ(list.countTotalItems(), 3);
}

// Test per countItemsToBuy quando la lista è vuota
TEST(ShoppingListTest, TestCountItemsToBuyEmpty) {
    ShoppingList list("Spesa");
    EXPECT_EQ(list.countItemsToBuy(), 0);
}

// Test per countTotalItems quando la lista è vuota
TEST(ShoppingListTest, TestCountTotalItemsEmpty) {
    ShoppingList list("Spesa");
    EXPECT_EQ(list.countTotalItems(), 0);
}