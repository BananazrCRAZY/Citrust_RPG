#include "gtest/gtest.h"
#include "../include/Player.h"
#include "../include/Boss.h"

TEST(PlayerTests, constructorTest) {
    Player p("assets/saves/Save1/Player.txt");

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

TEST(PlayerTests, levelUpTest) {
    Player p("assets/saves/Save1/Player.txt");

    p.levelUp();

    EXPECT_EQ(p.getLevel(), 3);
    EXPECT_EQ(p.getHp(), 103);
    EXPECT_EQ(p.getMaxHp(), 104);
    EXPECT_EQ(p.getAttack(), 55);
    EXPECT_EQ(p.getDefense(), 31);
    EXPECT_EQ(p.getArts(), 57);
    EXPECT_EQ(p.getRes(), 33);
    EXPECT_EQ(p.getCritRate(), 19);
    EXPECT_EQ(p.getCritDmg(), 30);
}

TEST(PlayerTests, setTests) {
    Player p("assets/saves/Save1/Player.txt");

    p.setHp(1);
    p.setMaxHpAdd(1);
    p.setAttackAdd(1);
    p.setDefenseAdd(1);
    p.setArtsAdd(1);
    p.setResAdd(1);
    p.setCritRateAdd(1);
    p.setCritDmgAdd(1);

    EXPECT_EQ(p.getHp(), 4);
    EXPECT_EQ(p.getMaxHp(), 5);
    EXPECT_EQ(p.getAttack(), 6);
    EXPECT_EQ(p.getDefense(), 7);
    EXPECT_EQ(p.getArts(), 8);
    EXPECT_EQ(p.getRes(), 9);
    EXPECT_EQ(p.getCritRate(), 10);
    EXPECT_EQ(p.getCritDmg(), 11);
}

// TEST(PlayerTests, saveTest) {
//     Player p1("assets/saves/Save1/Player.txt");
//     p1.levelUp();
//     p1.savePlayer();
//     Player p2("assets/saves/Save1/Player.txt");
    
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