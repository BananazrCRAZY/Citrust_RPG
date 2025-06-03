#include "gtest/gtest.h"
#include "Shop.h"
#include <vector>

TEST(ShopTests, constructorFailFile) {
    EXPECT_DEATH(Shop s(""), ".*Shop file.*");
}

TEST(ShopTests, resetShopTest) {
    Shop s("assets/saves/testSave/TestShopList.txt");
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    s.resetShop();
    EXPECT_NE(s.purchaseItem(p, 0), "You bought.*");
    EXPECT_NE(s.purchaseItem(p, 1), "You bought.*");
    EXPECT_NE(s.purchaseItem(p, 2), "You bought.*");
    EXPECT_NE(s.purchaseItem(p, 3), "You bought.*");
    EXPECT_NE(s.purchaseItem(p, 4), "You bought.*");
    EXPECT_NE(s.purchaseItem(p, 5), "You bought.*");
}

TEST(ShopTests, getItemPriceOver) {
    Shop s("assets/saves/testSave/TestShopList.txt");
    s.resetShop();
    EXPECT_DEATH(s.getItemPrice(100), ".*out of range.*");
}

TEST(ShopTests, getItemPricePass) {
    Shop s("assets/saves/testSave/TestShopList.txt");
    s.resetShop();
    EXPECT_TRUE(s.getItemPrice(0) == 100 || s.getItemPrice(0) == 125 || s.getItemPrice(0) == 200 || s.getItemPrice(0) == 250 || s.getItemPrice(0) == 300);
    EXPECT_TRUE(s.getItemPrice(1) == 100 || s.getItemPrice(1) == 125 || s.getItemPrice(1) == 200 || s.getItemPrice(1) == 250 || s.getItemPrice(1) == 300);
    EXPECT_TRUE(s.getItemPrice(2) == 100 || s.getItemPrice(2) == 125 || s.getItemPrice(2) == 200 || s.getItemPrice(2) == 250 || s.getItemPrice(2) == 300);
    EXPECT_TRUE(s.getItemPrice(3) == 100 || s.getItemPrice(3) == 125 || s.getItemPrice(3) == 200 || s.getItemPrice(3) == 250 || s.getItemPrice(3) == 300);
    EXPECT_TRUE(s.getItemPrice(4) == 100 || s.getItemPrice(4) == 125 || s.getItemPrice(4) == 200 || s.getItemPrice(4) == 250 || s.getItemPrice(4) == 300);
    EXPECT_TRUE(s.getItemPrice(5) == 100 || s.getItemPrice(5) == 125 || s.getItemPrice(5) == 200 || s.getItemPrice(5) == 250 || s.getItemPrice(5) == 300);
}

TEST(ShopTests, purchaseItemFailNegative) {
    Shop s("assets/saves/testSave/TestShopList.txt");
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    s.resetShop();
    EXPECT_DEATH(s.purchaseItem(p, -1), ".*out of range.*");
}

TEST(ShopTests, purchaseItemFailOver) {
    Shop s("assets/saves/testSave/TestShopList.txt");
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    s.resetShop();
    EXPECT_DEATH(s.purchaseItem(p, 10), ".*out of range.*");
}

TEST(ShopTests, saveShop0ItemBought) {
    Shop s("assets/saves/testSave/TestShopList.txt");
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    s.resetShop();
    s.saveShop();
}

// TEST(ShopTests, saveShop1ItemBought) {
//     Shop s("assets/saves/testSave/TestShopList.txt");
//     Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
//     s.resetShop();
//     EXPECT_NE(s.purchaseItem(p, 0), "You bought.*");
//     s.saveShop();
// }

// TEST(ShopTests, saveShopAllItemsBought) {
//     Shop s("assets/saves/testSave/TestShopList.txt");
//     Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
//     s.resetShop();
//     EXPECT_NE(s.purchaseItem(p, 0), "You bought.*");
//     EXPECT_NE(s.purchaseItem(p, 1), "You bought.*");
//     EXPECT_NE(s.purchaseItem(p, 2), "You bought.*");
//     EXPECT_NE(s.purchaseItem(p, 3), "You bought.*");
//     EXPECT_NE(s.purchaseItem(p, 4), "You bought.*");
//     EXPECT_NE(s.purchaseItem(p, 5), "You bought.*");
//     s.saveShop();
// }