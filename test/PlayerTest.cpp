/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#include "gtest/gtest.h"
#include "../include/Player.hpp"

using namespace tellstones;

TEST(PlayerTest, NameAndScore) {
    Player p("Alice");
    EXPECT_EQ(p.name(), "Alice");
    EXPECT_EQ(p.score(), 0);
    p.add_point();
    EXPECT_EQ(p.score(), 1);
    p.add_point();
    EXPECT_EQ(p.score(), 2);
}
