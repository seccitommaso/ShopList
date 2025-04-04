
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
    EXPECT_EQ(list.countTotalItems(), 1);
    EXPECT_EQ(list.getItems().front().getName(), "Mela");
}
//test per rimozione di un item
TEST(ShoppingListTest, RemoveItemTest) {
    ShoppingList list("Spesa");
    Item item("Mela", "Frutta", 3);
    list.addItem(item);
    list.removeItem("Mela");
    EXPECT_EQ(list.countTotalItems(), 0);
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
    list.addItem(Item("item1", "category1", 2));
    list.addItem(Item("item2", "category2", 1));
    list.addItem(Item("item3", "category3", 3));
    list.markItemAsPurchased("item3");//marca item3 come acquistato
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
// Test per getItemAt
TEST(ShoppingListTest, GetItemAtTest) {
    // Crea una ShoppingList con alcuni elementi
    ShoppingList list("Spesa");
    Item apple("Mela", "Frutta", 3);
    Item banana("Banana", "Frutta", 5);
    Item bread("Pane", "Panetteria", 2);

    list.addItem(apple);
    list.addItem(banana);
    list.addItem(bread);

    // Test per ottenere un elemento alla posizione corretta
    const Item& item1 = list.getItemAt(0);  // Prende il primo elemento
    EXPECT_EQ(item1.getName(), "Mela");
    EXPECT_EQ(item1.getCategory(), "Frutta");
    EXPECT_EQ(item1.getQuantity(), 3);

    // Test per un indice fuori dai limiti (dovrebbe lanciare una std::out_of_range)
    EXPECT_THROW(list.getItemAt(3), std::out_of_range);
}