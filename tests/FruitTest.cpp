#include "gtest/gtest.h"
#include "../include/Player.h"
#include "../include/Boss.h"

#include <string>
using std::string;

TEST(FruitTests, constructorFailFile) {
    EXPECT_DEATH(Player p("", "assets/saves/Save1/InventoryList.txt"), ".*Fruit file.*");
}

TEST(FruitTests, setTestsPositive) {
    Player p("assets/saves/Save1/Player.txt", "assets/saves/Save1/InventoryList.txt");

    p.setHp(1);
    p.setMaxHpAdd(1);
    p.setAttackAdd(1);
    p.setDefenseAdd(1);
    p.setArtsAdd(1);
    p.setResAdd(1);
    p.setCritRateAdd(1);
    p.setCritDmgAdd(1);
    p.setRechargeCount(1);
    p.setTurn(1);

    EXPECT_EQ(p.getHp(), 4);
    EXPECT_EQ(p.getMaxHp(), 5);
    EXPECT_EQ(p.getAttack(), 6);
    EXPECT_EQ(p.getDefense(), 7);
    EXPECT_EQ(p.getArts(), 8);
    EXPECT_EQ(p.getRes(), 9);
    EXPECT_EQ(p.getCritRate(), 10);
    EXPECT_EQ(p.getCritDmg(), 11);
    EXPECT_EQ(p.getRechargeCount(), 3);
    EXPECT_EQ(p.getTurn(), 2);
}

TEST(FruitTests, setTestsZero) {
    Player p("assets/saves/Save1/Player.txt", "assets/saves/Save1/InventoryList.txt");

    p.setHp(0);
    p.setMaxHpAdd(0);
    p.setAttackAdd(0);
    p.setDefenseAdd(0);
    p.setArtsAdd(0);
    p.setResAdd(0);
    p.setCritRateAdd(0);
    p.setCritDmgAdd(0);
    p.setRechargeCount(0);
    p.setTurn(0);

    EXPECT_EQ(p.getHp(), 3);
    EXPECT_EQ(p.getMaxHp(), 4);
    EXPECT_EQ(p.getAttack(), 5);
    EXPECT_EQ(p.getDefense(), 6);
    EXPECT_EQ(p.getArts(), 7);
    EXPECT_EQ(p.getRes(), 8);
    EXPECT_EQ(p.getCritRate(), 9);
    EXPECT_EQ(p.getCritDmg(), 10);
    EXPECT_EQ(p.getRechargeCount(), 2);
    EXPECT_EQ(p.getTurn(), 1);
}

TEST(FruitTests, setTestsNegative) {
    Player p("assets/saves/Save1/Player.txt", "assets/saves/Save1/InventoryList.txt");

    p.setHp(-1);
    p.setMaxHpAdd(-1);
    p.setAttackAdd(-1);
    p.setDefenseAdd(-1);
    p.setArtsAdd(-1);
    p.setResAdd(-1);
    p.setCritRateAdd(-1);
    p.setCritDmgAdd(-1);
    p.setRechargeCount(-1);
    p.setTurn(-1);

    EXPECT_EQ(p.getHp(), 2);
    EXPECT_EQ(p.getMaxHp(), 3);
    EXPECT_EQ(p.getAttack(), 4);
    EXPECT_EQ(p.getDefense(), 5);
    EXPECT_EQ(p.getArts(), 6);
    EXPECT_EQ(p.getRes(), 7);
    EXPECT_EQ(p.getCritRate(), 8);
    EXPECT_EQ(p.getCritDmg(), 9);
    EXPECT_EQ(p.getRechargeCount(), 1);
    EXPECT_EQ(p.getTurn(), 0);
}

TEST(FruitTests, clearStatusTest) {
    Player p("assets/saves/Save1/Player.txt", "assets/saves/Save1/InventoryList.txt");

    p.setHp(1);
    p.setMaxHpAdd(1);
    p.setAttackAdd(1);
    p.setDefenseAdd(1);
    p.setArtsAdd(1);
    p.setResAdd(1);
    p.setCritRateAdd(1);
    p.setCritDmgAdd(1);
    p.clearStatus();

    EXPECT_EQ(p.getLevel(), 2);
    EXPECT_EQ(p.getHp(), 4);
    EXPECT_EQ(p.getMaxHp(), 4);
    EXPECT_EQ(p.getAttack(), 5);
    EXPECT_EQ(p.getDefense(), 6);
    EXPECT_EQ(p.getArts(), 7);
    EXPECT_EQ(p.getRes(), 8);
    EXPECT_EQ(p.getCritRate(), 9);
    EXPECT_EQ(p.getCritDmg(), 10);
}

TEST(FruitTests, isDeadFalse) {
    Player p("assets/saves/Save1/Player.txt", "assets/saves/Save1/InventoryList.txt");
    EXPECT_TRUE(!p.isDead());
}

TEST(FruitTests, isDeadTrue) {
    Player p("assets/saves/Save1/Player.txt", "assets/saves/Save1/InventoryList.txt");
    p.setHp(-1000);
    EXPECT_TRUE(p.isDead());
}

TEST(PlayerTests, constructorTestFail) {
    EXPECT_DEATH(Player p("assets/saves/Save1/Player.txt", "assets/saves/Save1/InventoryList"), ".*Inventory list file.*");
}

TEST(PlayerTests, constructorTestPass) {
    Player p("assets/saves/Save1/Player.txt", "assets/saves/Save1/InventoryList.txt");

    EXPECT_EQ(p.getName(), "bob Johnson");
    EXPECT_EQ(p.getLevel(), 2);
    EXPECT_EQ(p.getHp(), 3);
    EXPECT_EQ(p.getMaxHp(), 4);
    EXPECT_EQ(p.getAttack(), 5);
    EXPECT_EQ(p.getDefense(), 6);
    EXPECT_EQ(p.getArts(), 7);
    EXPECT_EQ(p.getRes(), 8);
    EXPECT_EQ(p.getCritRate(), 9);
    EXPECT_EQ(p.getCritDmg(), 10);
}

// sebastian working on this
// TEST(PlayerTests, levelUpTest) {
//     Player p("assets/saves/Save1/Player.txt", "assets/saves/Save1/InventoryList.txt");

//     p.levelUp();

//     EXPECT_EQ(p.getLevel(), 3);
//     EXPECT_EQ(p.getHp(), 103);
//     EXPECT_EQ(p.getMaxHp(), 104);
//     EXPECT_EQ(p.getAttack(), 55);
//     EXPECT_EQ(p.getDefense(), 31);
//     EXPECT_EQ(p.getArts(), 57);
//     EXPECT_EQ(p.getRes(), 33);
//     EXPECT_EQ(p.getCritRate(), 19);
//     EXPECT_EQ(p.getCritDmg(), 30);
// }

// needs level up
// TEST(PlayerTests, saveTest) {
//     Player p1("assets/saves/Save1/Player.txt", "assets/saves/Save1/InventoryList.txt");
//     p1.levelUp();
//     Item* addItem = new Item("assets/items/TestItem2.txt");
//     p1.newItem(addItem);
//     p1.savePlayer();
//     Player p2("assets/saves/Save1/Player.txt", "assets/saves/Save1/InventoryList.txt");
    
//     EXPECT_EQ(p2.getName(), "bob Johnson");
//     EXPECT_EQ(p2.getLevel(), 3);
//     EXPECT_EQ(p2.getHp(), 103);
//     EXPECT_EQ(p2.getMaxHp(), 104);
//     EXPECT_EQ(p2.getAttack(), 55);
//     EXPECT_EQ(p2.getDefense(), 31);
//     EXPECT_EQ(p2.getArts(), 57);
//     EXPECT_EQ(p2.getRes(), 33);
//     EXPECT_EQ(p2.getCritRate(), 19);
//     EXPECT_EQ(p2.getCritDmg(), 30);
// }