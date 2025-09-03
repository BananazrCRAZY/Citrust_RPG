#include "gtest/gtest.h"
#include "include/Objects/Item.h"
#include "include/Objects/Status.h"
#include "include/Objects/Player.h"

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
    EXPECT_TRUE(item.isUseOnPlayer());

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

TEST(ItemTests, decreaseCoolDownTestOne) {
    Item item("assets/items/TestItem1.txt");
    item.decreaseCooldown();
    EXPECT_EQ(item.getCooldown(), -1);
}

TEST(ItemTests, decreaseCoolDownTestTwo) {
    Item item("assets/items/TestItem1.txt");
    item.decreaseCooldown();
    item.decreaseCooldown();
    EXPECT_EQ(item.getCooldown(), -2);
}

TEST(ItemTests, decreaseCooldownAfterUse) {
    Item item("assets/items/TestItem1.txt");
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    item.use(p);
    item.decreaseCooldown();
    EXPECT_EQ(item.getCooldown(), -1);
}

TEST(ItemTests, useTest) {
    Item item("assets/items/TestItem1.txt");
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    item.use(p);
    EXPECT_EQ(item.getCooldown(), 0);

    EXPECT_EQ(p->getHp(), 100);
    EXPECT_EQ(p->getMaxHp(), 100);
    EXPECT_EQ(p->getAttack(), 70);
    EXPECT_EQ(p->getDefense(), 25);
    EXPECT_EQ(p->getArts(), 50);
    EXPECT_EQ(p->getRes(), 25);
    EXPECT_EQ(p->getCritRate(), 50);
    EXPECT_EQ(p->getCritDmg(), 70);
    EXPECT_EQ(p->getRechargeCount(), 2);
    EXPECT_EQ(p->getTurn(), 1);
}