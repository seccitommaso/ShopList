
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
