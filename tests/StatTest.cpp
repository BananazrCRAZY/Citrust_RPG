#include "gtest/gtest.h"
#include "Stat.h"

TEST(StatTests, constuctorPositive) {
    Stat s(100);
    EXPECT_EQ(s.getBase(), 100);
}

TEST(StatTests, constuctorZero) {
    Stat s(0);
    EXPECT_EQ(s.getBase(), 0);
}

TEST(StatTests, constuctorNegative) {
    Stat s(-100);
    EXPECT_EQ(s.getBase(), -100);
}

TEST(StatTests, addPositive) {
    Stat s(100);
    s.add(250);
    EXPECT_EQ(s.getBase(), 100);
    EXPECT_EQ(s.getTotal(), 350);
}

TEST(StatTests, addZero) {
    Stat s(100);
    s.add(0);
    EXPECT_EQ(s.getBase(), 100);
    EXPECT_EQ(s.getTotal(), 100);
}

TEST(StatTests, addNegative) {
    Stat s(100);
    s.add(-17);
    EXPECT_EQ(s.getBase(), 100);
    EXPECT_EQ(s.getTotal(), 83);
}

TEST(StatTests, rmaddPositive) {
    Stat s(100);
    s.add(250);
    s.removeAdd();
    EXPECT_EQ(s.getBase(), 100);
    EXPECT_EQ(s.getTotal(), 100);
}

TEST(StatTests, rmaddZero) {
    Stat s(75);
    s.add(0);
    s.removeAdd();
    EXPECT_EQ(s.getBase(), 75);
    EXPECT_EQ(s.getTotal(), 75);
}

TEST(StatTests, rmaddNegative) {
    Stat s(1050);
    s.add(-17);
    s.removeAdd();
    EXPECT_EQ(s.getBase(), 1050);
    EXPECT_EQ(s.getTotal(), 1050);
}

TEST(StatTests, addBasePositive) {
    Stat s(100);
    s.addBase(250);
    EXPECT_EQ(s.getBase(), 350);
    EXPECT_EQ(s.getTotal(), 350);
}

TEST(StatTests, addBaseZero) {
    Stat s(100);
    s.addBase(0);
    EXPECT_EQ(s.getBase(), 100);
    EXPECT_EQ(s.getTotal(), 100);
}

TEST(StatTests, addBaseNegative) {
    Stat s(100);
    s.addBase(-17);
    EXPECT_EQ(s.getBase(), 83);
    EXPECT_EQ(s.getTotal(), 83);
}