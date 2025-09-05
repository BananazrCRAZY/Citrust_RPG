#include "gtest/gtest.h"
#include "include/Objects/Status.h"

TEST(StatusTests, constructorFailFile) {
    EXPECT_DEATH(Status s(""), ".*status file.*");
}

TEST(StatusTests, constructorFailFormat) {
    EXPECT_DEATH(Status s("assets/status/TestItem1Status.txt"), ".*file format.*");
}

TEST(StatusTests, constructorPass) {
    Status s("assets/status/TestStatus.txt");
    EXPECT_EQ(s.getName(), "test status name");
    EXPECT_EQ(s.getDescription(), "test status description");
    EXPECT_EQ(s.getTurns(), 0);
    EXPECT_TRUE(s.isPercentBased());
    EXPECT_EQ(s.getHpChange(), 0);
    EXPECT_EQ(s.getMaxHpChange(), 0);
    EXPECT_EQ(s.getAttackChange(), 40);
    EXPECT_EQ(s.getDefenseChange(), 0);
    EXPECT_EQ(s.getArtsChange(), 0);
    EXPECT_EQ(s.getResChange(), 0);
    EXPECT_EQ(s.getCritRateChange(), 40);
    EXPECT_EQ(s.getCritDamageChange(), 20);
    EXPECT_EQ(s.getRechargeCountChange(), 0);
    EXPECT_EQ(s.getTurnChange(), 0);
}

TEST(StatusTests, decreaseTurnTest) {
    Status s("assets/status/TestStatus.txt");
    s.decreaseTurn();
    EXPECT_EQ(s.getTurns(), -1);
}

TEST(StatusTests, resetDecreaseTurns) {
    Status s("assets/status/TestStatus.txt");
    s.resetStatusTurns();
    s.decreaseTurn();
    EXPECT_EQ(s.getTurns(), -1);
}

TEST(StatusTests, resetStatusTurns) {
    Status s("assets/status/TestStatus.txt");
    s.resetStatusTurns();
    EXPECT_EQ(s.getTurns(), 0);
}

TEST(StatusTests, decreaseResetTurns) {
    Status s("assets/status/TestStatus.txt");
    s.decreaseTurn();
    s.resetStatusTurns();
    EXPECT_EQ(s.getTurns(), 0);
}