/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#include "gtest/gtest.h"
#include "../include/Deck.hpp"
#include "../include/Exceptions.hpp"
#include <set>

using namespace tellstones;

TEST(DeckTest, InitStandardSize10) {
    Deck d;
    d.init_standard();
    EXPECT_EQ(d.size(), (size_t)10);
}

TEST(DeckTest, DrawRandomReducesSize) {
    Deck d;
    d.init_standard();
    size_t before = d.size();
    Stone s = d.draw_random();
    EXPECT_EQ(d.size(), before - 1);
    // Stone type must be one of the non-egg types
    EXPECT_NE(s.type, StoneType::Egg);
}

TEST(DeckTest, DrawUntilEmptyThrows) {
    Deck d;
    d.init_standard();
    // draw all
    for (size_t i=0;i<10;++i) d.draw_random();
    EXPECT_TRUE(d.empty());
    EXPECT_THROW(d.draw_random(), DeckEmptyException);
}

TEST(DeckTest, ReturnToBottom) {
    Deck d;
    d.init_standard();
    size_t sz = d.size();
    Stone s(StoneType::Sword, true);
    d.return_to_bottom(s);
    EXPECT_EQ(d.size(), sz + 1);
}
