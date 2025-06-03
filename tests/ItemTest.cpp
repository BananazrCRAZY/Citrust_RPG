#include "gtest/gtest.h"
#include "Item.h"
#include "Status.h"
#include "Player.h"

TEST(ItemTests, constructorFailFile) {
    EXPECT_DEATH(Item item(""), ".*item file.*");
}

TEST(ItemTests, constructorFailFormat) {
    EXPECT_DEATH(Item item("assets/items/TestItem.txt"), ".*file format.*");
}

TEST(ItemTests, constructorPass) {
    Item item("assets/items/TestItem1.txt");
    EXPECT_EQ(item.getName(), "test name");
    EXPECT_EQ(item.getDescription(), "test description");
    EXPECT_EQ(item.getCost(), 300);
    EXPECT_FALSE(item.isConsumableTrue());
    EXPECT_EQ(item.getCooldown(), 0);
    EXPECT_EQ(item.getAppearanceProbabiity(), 10);

    Status s("assets/status/AttackUpY.txt");
    EXPECT_EQ(s.getName(), item.getStatus()->getName());
    EXPECT_EQ(s.getDescription(), item.getStatus()->getDescription());
    EXPECT_EQ(s.getTurns(), item.getStatus()->getTurns());
    EXPECT_EQ(s.isPercentBased(), item.getStatus()->isPercentBased());
    EXPECT_EQ(s.getHpChange(), item.getStatus()->getHpChange());
    EXPECT_EQ(s.getMaxHpChange(), item.getStatus()->getMaxHpChange());
    EXPECT_EQ(s.getAttackChange(), item.getStatus()->getAttackChange());
    EXPECT_EQ(s.getDefenseChange(), item.getStatus()->getDefenseChange());
    EXPECT_EQ(s.getArtsChange(), item.getStatus()->getArtsChange());
    EXPECT_EQ(s.getResChange(), item.getStatus()->getResChange());
    EXPECT_EQ(s.getCritRateChange(), item.getStatus()->getCritRateChange());
    EXPECT_EQ(s.getCritDamageChange(), item.getStatus()->getCritDamageChange());
    EXPECT_EQ(s.getRechargeCountChange(), item.getStatus()->getRechargeCountChange());
    EXPECT_EQ(s.getTurnChange(), item.getStatus()->getTurnChange());
}

TEST(ItemTests, decreaseCoolDownTest) {
    Item item("assets/items/TestItem1.txt");
    item.decreaseCooldown();
    EXPECT_EQ(item.getCooldown(), -1);
}

TEST(ItemTests, useTest) {
    Item item("assets/items/TestItem1.txt");
    Player* p = new Player("assets/saves/Save1/Player.txt", "assets/saves/Save1/InventoryList.txt");
    item.decreaseCooldown();
    item.use(p);
    EXPECT_EQ(item.getCooldown(), 0);

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