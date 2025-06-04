#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Shop.h"
#include <vector>

using testing::Contains;

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
    std::vector<int> expectedVal = {100, 125, 200, 250, 300};
    EXPECT_THAT(expectedVal, Contains(s.getItemPrice(0)));
    EXPECT_THAT(expectedVal, Contains(s.getItemPrice(1)));
    EXPECT_THAT(expectedVal, Contains(s.getItemPrice(2)));
    EXPECT_THAT(expectedVal, Contains(s.getItemPrice(3)));
    EXPECT_THAT(expectedVal, Contains(s.getItemPrice(4)));
    EXPECT_THAT(expectedVal, Contains(s.getItemPrice(5)));
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