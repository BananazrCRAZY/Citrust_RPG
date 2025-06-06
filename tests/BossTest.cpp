#include "gtest/gtest.h"
#include "gmock/gmock.h"
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
#include "Player.h"
#include <vector>

using std::vector;
using testing::Contains;

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

TEST(BossTests, endOfTurnTest) {
    Boss* boss = new Apple("assets/bosses/Apple.txt", "assets/bossItems/AppleCore.txt", -1);
    boss->endOfTurn();
    EXPECT_EQ(boss->getBossAbilityCharge(), 2);
}

TEST(AppleTests, specialAttackDamageTest) {
    Boss* boss = new Apple("assets/bosses/Apple.txt", "assets/bossItems/AppleCore.txt", -1);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    EXPECT_EQ(boss->specialAttack(p), "Apple: Dealt 119 damage.");
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(AppleTests, specialAttackZeroTest) {
    Boss* boss = new Apple("assets/bosses/Apple.txt", "assets/bossItems/AppleCore.txt", -1);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    boss->setAttackAdd(-1 * boss->getAttack());

    EXPECT_EQ(boss->specialAttack(p), "Apple: Dealt 0 damage.");
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(AppleTests, abilityTestSubMax) {
    Boss* boss = new Apple("assets/bosses/Apple.txt", "assets/bossItems/AppleCore.txt", -1);
    boss->setHp(-33);

    EXPECT_EQ(boss->bossAbility(), "Apple: Healed 32 hp.");
    EXPECT_EQ(boss->getHp(), 646);
}

TEST(AppleTests, abilityTestOverMax) {
    Boss* boss = new Apple("assets/bosses/Apple.txt", "assets/bossItems/AppleCore.txt", -1);

    EXPECT_EQ(boss->bossAbility(), "Apple: Healed 32 hp.");
    EXPECT_EQ(boss->getHp(), 647);
}

TEST(PearTests, specialAttackDamageTest) {
    Boss* boss = new Pear("assets/bosses/Pear.txt", "assets/bossItems/PearStem.txt", -1);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    boss->setCritRateAdd(-100);
    EXPECT_EQ(boss->specialAttack(p), "Pear: Dealt 185 damage.");

    boss->setCritRateAdd(200);
    EXPECT_EQ(boss->specialAttack(p), "Pear: Dealt 323 damage.");
    EXPECT_EQ(boss->getRechargeCount(), -2);
}

TEST(PearTests, specialAttackZeroTest) {
    Boss* boss = new Pear("assets/bosses/Pear.txt", "assets/bossItems/PearStem.txt", -1);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    boss->setAttackAdd(-1 * boss->getAttack());

    EXPECT_EQ(boss->specialAttack(p), "Pear: Dealt 0 damage.");
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(PearTests, abilityTest) {
    Boss* boss = new Pear("assets/bosses/Pear.txt", "assets/bossItems/PearStem.txt", -1);

    EXPECT_EQ(boss->bossAbility(), "Pear: Increased critical rate.");
    EXPECT_EQ(boss->getCritRate(), 42);
}

TEST(StrawberryTests, specialAttackDamageTest) {
    Boss* boss = new Strawberry("assets/bosses/Strawberry.txt", "assets/bossItems/StrawberrySeed.txt", 3);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    vector<string> expectedVal = {
        "Strawberry: Attack 1 did 138 damage.\nStrawberry: Lost 1 defense.",
        "Strawberry: Attack 1 did 138 damage.\nStrawberry: Attack 2 did 138 damage.\nStrawberry: Lost 2 defense.",
        "Strawberry: Attack 1 did 138 damage.\nStrawberry: Attack 2 did 138 damage.\nStrawberry: Attack 3 did 138 damage.\nStrawberry: Lost 3 defense.",
        "Strawberry: Attack 1 did 138 damage.\nStrawberry: Attack 2 did 138 damage.\nStrawberry: Attack 3 did 138 damage.\nStrawberry: Attack 4 did 138 damage.\nStrawberry: Lost 4 defense.",
        "Strawberry: Attack 1 did 138 damage.\nStrawberry: Attack 2 did 138 damage.\nStrawberry: Attack 3 did 138 damage.\nStrawberry: Attack 4 did 138 damage.\nStrawberry: Attack 5 did 138 damage.\nStrawberry: Lost 5 defense."
    };
    EXPECT_THAT(expectedVal, Contains(boss->specialAttack(p)));
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(StrawberryTests, specialAttackZeroTest) {
    Boss* boss = new Strawberry("assets/bosses/Strawberry.txt", "assets/bossItems/StrawberrySeed.txt", 3);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    boss->setAttackAdd(-1 * boss->getAttack());

    vector<string> expectedVal = {
        "Strawberry: Attack 1 did 0 damage.\nStrawberry: Lost 1 defense.",
        "Strawberry: Attack 1 did 0 damage.\nStrawberry: Attack 2 did 0 damage.\nStrawberry: Lost 2 defense.",
        "Strawberry: Attack 1 did 0 damage.\nStrawberry: Attack 2 did 0 damage.\nStrawberry: Attack 3 did 0 damage.\nStrawberry: Lost 3 defense.",
        "Strawberry: Attack 1 did 0 damage.\nStrawberry: Attack 2 did 0 damage.\nStrawberry: Attack 3 did 0 damage.\nStrawberry: Attack 4 did 0 damage.\nStrawberry: Lost 4 defense.",
        "Strawberry: Attack 1 did 0 damage.\nStrawberry: Attack 2 did 0 damage.\nStrawberry: Attack 3 did 0 damage.\nStrawberry: Attack 4 did 0 damage.\nStrawberry: Attack 5 did 0 damage.\nStrawberry: Lost 5 defense."
    };
    EXPECT_THAT(expectedVal, Contains(boss->specialAttack(p)));
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(StrawberryTests, abilityTest) {
    Boss* boss = new Strawberry("assets/bosses/Strawberry.txt", "assets/bossItems/StrawberrySeed.txt", 3);

    EXPECT_EQ(boss->bossAbility(), "Strawberry: Lost 5 defense.");
    EXPECT_EQ(boss->getBossAbilityCharge(), -2);
}

TEST(GrapeTests, specialAttackDamageTest) {
    Boss* boss = new Grape("assets/bosses/Grape.txt", "assets/bossItems/Grapevine.txt", 4);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    vector<string> expectedVal = {
        "Grape: Attack 1 did 93 damage.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Gave bob Johnson a random effect.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Attack 2 did 93 damage.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 2 did 93 damage.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Attack 2 did 93 damage.\nGrape: Gave bob Johnson a random effect.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 2 did 93 damage.\nGrape: Gave bob Johnson a random effect.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Attack 2 did 93 damage.\nGrape: Attack 3 did 93 damage.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 2 did 93 damage.\nGrape: Attack 3 did 93 damage.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Attack 2 did 93 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 3 did 93 damage.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Attack 2 did 93 damage.\nGrape: Attack 3 did 93 damage.\nGrape: Gave bob Johnson a random effect.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 2 did 93 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 3 did 93 damage.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 2 did 93 damage.\nGrape: Attack 3 did 93 damage.\nGrape: Gave bob Johnson a random effect.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Attack 2 did 93 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 3 did 93 damage.\nGrape: Gave bob Johnson a random effect.\n",
        "Grape: Attack 1 did 93 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 2 did 93 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 3 did 93 damage.\nGrape: Gave bob Johnson a random effect.\n"
    };
    EXPECT_THAT(expectedVal, Contains(boss->specialAttack(p)));
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(GrapeTests, specialAttackZeroTest) {
    Boss* boss = new Grape("assets/bosses/Grape.txt", "assets/bossItems/Grapevine.txt", 4);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    boss->setArtsAdd(-1 * boss->getArts());

    vector<string> expectedVal = {
        "Grape: Attack 1 did 0 damage.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Gave bob Johnson a random effect.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Attack 2 did 0 damage.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 2 did 0 damage.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Attack 2 did 0 damage.\nGrape: Gave bob Johnson a random effect.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 2 did 0 damage.\nGrape: Gave bob Johnson a random effect.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Attack 2 did 0 damage.\nGrape: Attack 3 did 0 damage.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 2 did 0 damage.\nGrape: Attack 3 did 0 damage.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Attack 2 did 0 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 3 did 0 damage.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Attack 2 did 0 damage.\nGrape: Attack 3 did 0 damage.\nGrape: Gave bob Johnson a random effect.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 2 did 0 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 3 did 0 damage.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 2 did 0 damage.\nGrape: Attack 3 did 0 damage.\nGrape: Gave bob Johnson a random effect.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Attack 2 did 0 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 3 did 0 damage.\nGrape: Gave bob Johnson a random effect.\n",
        "Grape: Attack 1 did 0 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 2 did 0 damage.\nGrape: Gave bob Johnson a random effect.\nGrape: Attack 3 did 0 damage.\nGrape: Gave bob Johnson a random effect.\n"
    };
    EXPECT_THAT(expectedVal, Contains(boss->specialAttack(p)));
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(GrapeTests, abilityTest) {
    Boss* boss = new Grape("assets/bosses/Grape.txt", "assets/bossItems/Grapevine.txt", 4);

    EXPECT_EQ(boss->bossAbility(), "Grape: Charged up.");
    EXPECT_EQ(boss->getBossAbilityCharge(), -3);
}

TEST(DekoponTests, specialAttackTest) {
    Boss* boss = new Dekopon("assets/saves/testSave/TestPlayer.txt", "assets/bossItems/Dekopeel.txt", 3);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    boss->setHp(-40);

    EXPECT_EQ(boss->specialAttack(p), "Dekopon: Absorbed 20% of bob Johnson\'s hp.");
    EXPECT_EQ(boss->getHp(), 80);
    EXPECT_EQ(p->getHp(), 80);
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(DekoponTests, specialAttackOverHeal) {
    Boss* boss = new Dekopon("assets/saves/testSave/TestPlayer.txt", "assets/bossItems/Dekopeel.txt", 3);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    EXPECT_EQ(boss->specialAttack(p), "Dekopon: Absorbed 20% of bob Johnson\'s hp.");
    EXPECT_EQ(boss->getHp(), 100);
    EXPECT_EQ(p->getHp(), 80);
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(DekoponTests, abilityTest) {
    Boss* boss = new Dekopon("assets/saves/testSave/TestPlayer.txt", "assets/bossItems/Dekopeel.txt", 3);

    EXPECT_EQ(boss->bossAbility(), "Dekopon: Stats boosted.");
    EXPECT_EQ(boss->getHp(), 150);
    EXPECT_EQ(boss->getMaxHp(), 150);
    EXPECT_EQ(boss->getAttack(), 100);
    EXPECT_EQ(boss->getDefense(), 75);
    EXPECT_EQ(boss->getRes(), 30);
    EXPECT_EQ(boss->getBossAbilityCharge(), -2);
}

TEST(MangoGreenTests, specialAttackZeroDmg) {
    Boss* boss = new MangoGreen("assets/bosses/MangoGreen.txt", "assets/bossItems/DriedMango.txt", -1);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    boss->setAttackAdd(-1 * boss->getAttack());

    EXPECT_EQ(boss->specialAttack(p), "Mango Green: Dealt 0 damage.\nbob Johnson: Attack decreased by Mango Green.");
    EXPECT_EQ(p->getAttack(), 30);
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(MangoGreenTests, specialAttackNotZero) {
    Boss* boss = new MangoGreen("assets/bosses/MangoGreen.txt", "assets/bossItems/DriedMango.txt", -1);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    EXPECT_EQ(boss->specialAttack(p), "Mango Green: Dealt 107 damage.\nbob Johnson: Attack decreased by Mango Green.");
    EXPECT_EQ(p->getAttack(), 30);
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(MangoGreenTests, abilityTestOver50) {
    Boss* boss = new MangoGreen("assets/bosses/MangoGreen.txt", "assets/bossItems/DriedMango.txt", -1);
    int baseAttack = boss->getAttack();

    EXPECT_EQ(boss->bossAbility(), "");
    EXPECT_EQ(boss->getAttack(), baseAttack);
    EXPECT_EQ(boss->getRequiredBossCharge(), -1);
}

TEST(MangoGreenTests, abilityTestSub50) {
    Boss* boss = new MangoGreen("assets/bosses/MangoGreen.txt", "assets/bossItems/DriedMango.txt", -1);
    boss->setHp(-1 * boss->getHp() * .6);
    int expectedAttack = boss->getAttack() + 100;

    EXPECT_EQ(boss->bossAbility(), "Mango Green: Attack increased.");
    EXPECT_EQ(boss->getAttack(), expectedAttack);
    EXPECT_EQ(boss->getRequiredBossCharge(), 101);
}

TEST(MangoRedTests, specialAttackZeroDmg) {
    Boss* boss = new MangoRed("assets/bosses/MangoRed.txt", "assets/bossItems/DriedMango.txt", -1);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");
    boss->setArtsAdd(-1 * boss->getArts());

    EXPECT_EQ(boss->specialAttack(p), "Mango Red: Dealt 0 damage.\nbob Johnson: Attack decreased by Mango Red.");
    EXPECT_EQ(p->getAttack(), 20);
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(MangoRedTests, specialAttackNotZero) {
    Boss* boss = new MangoRed("assets/bosses/MangoRed.txt", "assets/bossItems/DriedMango.txt", -1);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    EXPECT_EQ(boss->specialAttack(p), "Mango Red: Dealt 132 damage.\nbob Johnson: Attack decreased by Mango Red.");
    EXPECT_EQ(p->getAttack(), 20);
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(MangoRedTests, abilityTestOver50) {
    Boss* boss = new MangoRed("assets/bosses/MangoRed.txt", "assets/bossItems/DriedMango.txt", -1);
    int baseAttack = boss->getAttack();

    EXPECT_EQ(boss->bossAbility(), "");
    EXPECT_EQ(boss->getAttack(), baseAttack);
    EXPECT_EQ(boss->getRequiredBossCharge(), -1);
}

TEST(MangoRedTests, abilityTestSub50) {
    Boss* boss = new MangoRed("assets/bosses/MangoRed.txt", "assets/bossItems/DriedMango.txt", -1);
    boss->setHp(-1 * boss->getHp() * .6);
    int expectedAttack = boss->getAttack() + 150;

    EXPECT_EQ(boss->bossAbility(), "Mango Red: Attack increased.");
    EXPECT_EQ(boss->getAttack(), expectedAttack);
    EXPECT_EQ(boss->getRequiredBossCharge(), 101);
}

TEST(PineappleTests, specialAttackTest) {
    Boss* boss = new Pineapple("assets/bosses/Pineapple.txt", "assets/bossItems/PineappleCrown.txt", 1000);
    Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

    EXPECT_EQ(boss->specialAttack(p), "bob Johnson: Inflicted with DoT by Pineapple.");
    EXPECT_EQ(p->getHp(), 100);
    p->endOfTurn();
    EXPECT_EQ(p->getHp(), 40);
    p->endOfTurn();
    EXPECT_EQ(p->getHp(), -20);
    p->endOfTurn();
    EXPECT_EQ(p->getHp(), -20);
    EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(PineappleTests, basicAttack) {
  Boss* boss = new Pineapple("assets/bosses/Pineapple.txt", "assets/bossItems/PineappleCrown.txt", 1000);
  Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

  EXPECT_EQ(boss->basicAttack(p), "Pineapple: Dealt 300 damage.\nbob Johnson: Inflicted with DoT by Pineapple.");
  EXPECT_EQ(p->getHp(), -200);
  p->endOfTurn();
  EXPECT_EQ(p->getHp(), -230);
  EXPECT_EQ(boss->getRechargeCount(), 2);
}

TEST(DurianTests, bossAbility) {
  Boss* boss = new Durian("assets/bosses/Durian.txt", "assets/bossItems/DurianThorn.txt", -1);
  Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

  boss->setHp(-25);
  EXPECT_EQ(boss->bossAbility(), "Durian: Getting angry.");
  EXPECT_EQ(boss->getAttack(), 629);
  boss->setHp(-25);
  EXPECT_EQ(boss->bossAbility(), "Durian: Getting angry.");
  EXPECT_EQ(boss->getAttack(), 631);
  boss->setHp(-25);
  EXPECT_EQ(boss->bossAbility(), "Durian: Getting angry.");
  EXPECT_EQ(boss->getAttack(), 633);
}

TEST(DurianTests, basicAttack) {
  Boss* boss = new Durian("assets/bosses/Durian.txt", "assets/bossItems/DurianThorn.txt", -1);
  Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

  EXPECT_EQ(boss->basicAttack(p), "Durian: Dealt 602 damage.\nbob Johnson: Inflicted with DoT by Durian.");
  EXPECT_EQ(p->getHp(), -502);
  p->endOfTurn();
  EXPECT_EQ(p->getHp(), -702);
}

TEST(DurianTests, specialAttack) {
  Boss* boss = new Durian("assets/bosses/Durian.txt", "assets/bossItems/DurianThorn.txt", -1);
  Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

  EXPECT_EQ(boss->specialAttack(p), "Durian: Dealt 1868 damage.");
  EXPECT_EQ(p->getHp(), -1768);
  EXPECT_EQ(boss->getRechargeCount(), 0);
}

TEST(WatermelonTests, specialAttack) {
  Boss* boss = new Watermelon("assets/bosses/Watermelon.txt", "assets/bossItems/DurianThorn.txt", 1000);
  Player* p = new Player("assets/saves/testSave/TestPlayer.txt", "assets/saves/testSave/TestInventoryList.txt");

  EXPECT_EQ(boss->specialAttack(p), "Watermelon: Dealt 2883 damage.\nWatermelon: Attack and res increased, and defense decreased.\n");
  EXPECT_EQ(boss->getAttack(), 777);
  EXPECT_EQ(boss->getDefense(), 770);
  EXPECT_EQ(boss->getRes(), 9);

  EXPECT_EQ(boss->specialAttack(p), "Watermelon: Dealt 3083 damage.\nWatermelon: Attack and res increased, and defense decreased.\n");
  EXPECT_EQ(boss->getAttack(), 827);
  EXPECT_EQ(boss->getDefense(), 720);
  EXPECT_EQ(boss->getRes(), 16);
}
