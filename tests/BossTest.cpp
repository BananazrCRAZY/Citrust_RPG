#include "gtest/gtest.h"
#include "bossHeaders/Apple.h"
#include "bossHeaders/Pear.h"
#include "bossHeaders/Strawberry.h"
#include "bossHeaders/Grape.h"
#include "bossHeaders/Dekopon.h"
#include "bossHeaders/MangoGreen.h"
#include "bossHeaders/MangoRed.h"
#include "bossHeaders/Pineapple.h"
#include "bossHeaders/Durian.h"
#include "bossHeaders/Watermelon.h"

TEST(BossTests, constructorFailFruitFile) {
    EXPECT_DEATH(Boss* boss = new Apple("", "assets/bossItems/AppleCore.txt", -1), ".*Fruit file.*");
}

TEST(BossTests, constructorFailItemFile) {
    EXPECT_DEATH(Boss* boss = new Apple("assets/bosses/Apple.txt", "", -1), ".*item file.*");
}

TEST(BossTests, constructorPass) {
    Boss* boss = new Apple("assets/bosses/Apple.txt", "assets/bossItems/AppleCore.txt", -1);
    Item* item = new Item("assets/bossItems/AppleCore.txt");

    EXPECT_EQ(boss->getBossAbilityCharge(), 1);
    EXPECT_EQ(boss->getRequiredBossCharge(), -1);
    EXPECT_EQ(boss->getItem()->getCooldown(), item->getCooldown());
    EXPECT_EQ(boss->getItem()->getCost(), item->getCost());
    EXPECT_EQ(boss->getItem()->getDescription(), item->getDescription());
    EXPECT_EQ(boss->getItem()->getName(), item->getName());
    EXPECT_EQ(boss->getItem()->getAppearanceProbabiity(), item->getAppearanceProbabiity());
    EXPECT_EQ(boss->getItem()->getFilePath(), item->getFilePath());
}