#include "gtest/gtest.h"
#include "../include/Player.h"
#include "../include/Boss.h"

#include <string>
using std::string;

TEST(FruitTests, constructorFailFile) {
    EXPECT_DEATH(Player p("", "assets/saves/testSave/TestInventoryList.txt"), ".*Fruit file.*");
}

TEST(FruitTests, constructorFailFormat) {
    EXPECT_DEATH(Player p("assets/saves/testSave/TestPlayerFail.txt", "assets/saves/testSave/TestInventoryList.txt"), ".*file format.*");
}

TEST(FruitTests, setTestsPositiveNoHp) {
    Player p("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    p.setMaxHpAdd(1);
    p.setAttackAdd(1);
    p.setDefenseAdd(1);
    p.setArtsAdd(1);
    p.setResAdd(1);
    p.setCritRateAdd(1);
    p.setCritDmgAdd(1);
    p.setRechargeCount(1);
    p.setTurn(1);

    EXPECT_EQ(p.getHp(), 101);
    EXPECT_EQ(p.getMaxHp(), 101);
    EXPECT_EQ(p.getAttack(), 51);
    EXPECT_EQ(p.getDefense(), 26);
    EXPECT_EQ(p.getArts(), 51);
    EXPECT_EQ(p.getRes(), 26);
    EXPECT_EQ(p.getCritRate(), 11);
    EXPECT_EQ(p.getCritDmg(), 51);
    EXPECT_EQ(p.getRechargeCount(), 3);
    EXPECT_EQ(p.getTurn(), 2);
}

TEST(FruitTests, setTestsPositiveHpFirst) {
    Player p("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    
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

    EXPECT_EQ(p.getHp(), 101);
    EXPECT_EQ(p.getMaxHp(), 101);
    EXPECT_EQ(p.getAttack(), 51);
    EXPECT_EQ(p.getDefense(), 26);
    EXPECT_EQ(p.getArts(), 51);
    EXPECT_EQ(p.getRes(), 26);
    EXPECT_EQ(p.getCritRate(), 11);
    EXPECT_EQ(p.getCritDmg(), 51);
    EXPECT_EQ(p.getRechargeCount(), 3);
    EXPECT_EQ(p.getTurn(), 2);
}

TEST(FruitTests, setTestsZero) {
    Player p("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    p.setHp(0);
    p.setMaxHpAdd(0);
    p.setAttackAdd(0);
    p.setDefenseAdd(0);
    p.setArtsAdd(0);
    p.setResAdd(0);
    p.setCritRateAdd(0);
    p.setCritDmgAdd(0);

    EXPECT_EQ(p.getHp(), 100);
    EXPECT_EQ(p.getMaxHp(), 100);
    EXPECT_EQ(p.getAttack(), 50);
    EXPECT_EQ(p.getDefense(), 25);
    EXPECT_EQ(p.getArts(), 50);
    EXPECT_EQ(p.getRes(), 25);
    EXPECT_EQ(p.getCritRate(), 10);
    EXPECT_EQ(p.getCritDmg(), 50);
}

TEST(FruitTests, setTestsNegative) {
    Player p("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

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

    EXPECT_EQ(p.getHp(), 99);
    EXPECT_EQ(p.getMaxHp(), 99);
    EXPECT_EQ(p.getAttack(), 49);
    EXPECT_EQ(p.getDefense(), 24);
    EXPECT_EQ(p.getArts(), 49);
    EXPECT_EQ(p.getRes(), 24);
    EXPECT_EQ(p.getCritRate(), 9);
    EXPECT_EQ(p.getCritDmg(), 49);
    EXPECT_EQ(p.getRechargeCount(), 1);
    EXPECT_EQ(p.getTurn(), 0);
}

TEST(FruitTests, setTestsLargeNegative) {
    Player p("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    p.setHp(-1000);
    p.setMaxHpAdd(-1000);
    p.setAttackAdd(-1000);
    p.setDefenseAdd(-1000);
    p.setArtsAdd(-1000);
    p.setResAdd(-1000);
    p.setCritRateAdd(-1000);
    p.setCritDmgAdd(-1000);
    p.setRechargeCount(-1000);

    EXPECT_EQ(p.getHp(), -900);
    EXPECT_EQ(p.getMaxHp(), 0);
    EXPECT_EQ(p.getAttack(), 0);
    EXPECT_EQ(p.getDefense(), 0);
    EXPECT_EQ(p.getArts(), 0);
    EXPECT_EQ(p.getRes(), 0);
    EXPECT_EQ(p.getCritRate(), 0);
    EXPECT_EQ(p.getCritDmg(), 0);
    EXPECT_EQ(p.getRechargeCount(), 0);
}

TEST(FruitTests, clearStatusTest) {
    Player p("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    p.setHp(1);
    p.setMaxHpAdd(1);
    p.setAttackAdd(1);
    p.setDefenseAdd(1);
    p.setArtsAdd(1);
    p.setResAdd(1);
    p.setCritRateAdd(1);
    p.setCritDmgAdd(1);
    p.clearStatus();

    EXPECT_EQ(p.getHp(), 100);
    EXPECT_EQ(p.getMaxHp(), 100);
    EXPECT_EQ(p.getAttack(), 50);
    EXPECT_EQ(p.getDefense(), 25);
    EXPECT_EQ(p.getArts(), 50);
    EXPECT_EQ(p.getRes(), 25);
    EXPECT_EQ(p.getCritRate(), 10);
    EXPECT_EQ(p.getCritDmg(), 50);
}

TEST(FruitTests, isDeadFalse) {
    Player p("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    EXPECT_FALSE(p.isDead());
}

TEST(FruitTests, isDeadTrue) {
    Player p("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    p.setHp(-1000);
    EXPECT_TRUE(p.isDead());
}

TEST(PlayerTests, constructorFailFile) {
    EXPECT_DEATH(Player p("assets/saves/testSave/TestPlayer.txt", "");, ".*Inventory list file.*");
}

TEST(PlayerTests, constructorTestPass) {
    Player p("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    EXPECT_EQ(p.getName(), "bob Johnson");
    EXPECT_EQ(p.getLevel(), 1);
    EXPECT_EQ(p.getHp(), 100);
    EXPECT_EQ(p.getMaxHp(), 100);
    EXPECT_EQ(p.getAttack(), 50);
    EXPECT_EQ(p.getDefense(), 25);
    EXPECT_EQ(p.getArts(), 50);
    EXPECT_EQ(p.getRes(), 25);
    EXPECT_EQ(p.getCritRate(), 10);
    EXPECT_EQ(p.getCritDmg(), 50);
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

TEST(PlayerTests, saveNoChange) {
    Player p1("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    p1.savePlayer();
    Player p("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    EXPECT_EQ(p.getName(), "bob Johnson");
    EXPECT_EQ(p.getLevel(), 1);
    EXPECT_EQ(p.getHp(), 100);
    EXPECT_EQ(p.getMaxHp(), 100);
    EXPECT_EQ(p.getAttack(), 50);
    EXPECT_EQ(p.getDefense(), 25);
    EXPECT_EQ(p.getArts(), 50);
    EXPECT_EQ(p.getRes(), 25);
    EXPECT_EQ(p.getCritRate(), 10);
    EXPECT_EQ(p.getCritDmg(), 50);
}

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