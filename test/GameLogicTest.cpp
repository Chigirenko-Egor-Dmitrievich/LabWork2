/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#include "gtest/gtest.h"
#include "../include/Board.hpp"
#include "../include/Player.hpp"
#include "../include/Stone.hpp"

using namespace tellstones;

TEST(GameLogic, BragEquivalentSuccess) {
    Board b;
    // fill board row-major with known stones
    std::vector<int> types;
    for (int r=0;r<Board::SIZE;++r) for (int c=0;c<Board::SIZE;++c) {
        b.place_stone(r,c, Stone(StoneType::Sword, true));
        types.push_back(static_cast<int>(StoneType::Sword));
    }
    // check all filled
    ASSERT_TRUE(b.all_cells_filled());
    // simulate brag correctness check
    bool ok = true;
    int idx = 0;
    for (int r=0;r<Board::SIZE;++r) for (int c=0;c<Board::SIZE;++c) {
        const Cell& cell = b.at(r,c);
        if (cell.is_empty() || static_cast<int>(cell.stone->type) != types[idx]) ok = false;
        ++idx;
    }
    EXPECT_TRUE(ok);
}

TEST(GameLogic, BragEquivalentFail) {
    Board b;
    // fill board with different stones in one position
    for (int r=0;r<Board::SIZE;++r) for (int c=0;c<Board::SIZE;++c) b.place_stone(r,c, Stone(StoneType::Sword, true));
    // change one
    b.take_stone(1,1);
    b.place_stone(1,1, Stone(StoneType::Shield, true));
    std::vector<int> guesses(Board::SIZE*Board::SIZE, static_cast<int>(StoneType::Sword));
    // the guess list is all Sword -> should fail
    bool ok = true;
    int idx = 0;
    for (int r=0;r<Board::SIZE;++r) for (int c=0;c<Board::SIZE;++c) {
        const Cell& cell = b.at(r,c);
        if (cell.is_empty() || static_cast<int>(cell.stone->type) != guesses[idx]) ok = false;
        ++idx;
    }
    EXPECT_FALSE(ok);
}
