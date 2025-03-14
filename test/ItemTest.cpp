#include <gtest/gtest.h>
#include "../Item.h"

TEST(ItemTest, DefaultPurchasedIsFalse) {
    Item item("Latte", "Alimentari", 2);
    EXPECT_FALSE(item.isPurchased()); // Valore di default deve essere false
}

TEST(ItemTest, SetPurchasedFalseAfterTrue) {
    Item item("Latte", "Alimentari", 2);
    item.setPurchased(true);
    EXPECT_TRUE(item.isPurchased());

    item.setPurchased(false);
    EXPECT_FALSE(item.isPurchased());
}

// Test costruttore
TEST(ItemTest, Constructor) {
    Item item("Mela", "Frutta", 3);

    EXPECT_EQ(item.getName(), "Mela");
    EXPECT_EQ(item.getCategory(), "Frutta");
    EXPECT_EQ(item.getQuantity(), 3);
}

// Test per verificare che i metodi getter restituiscano i valori corretti
TEST(ItemTest, Getters) {
    Item item("Pane", "Forno", 5);

    EXPECT_EQ(item.getName(), "Pane");
    EXPECT_EQ(item.getCategory(), "Forno");
    EXPECT_EQ(item.getQuantity(), 5);
}

// Test con quantità negativa
TEST(ItemTest, NegativeQuantity) {
    Item item("Latte", "Latticini", -2);

    EXPECT_EQ(item.getQuantity(), 0);  //imposta le quantità negative a 0
}
