/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#include "gtest/gtest.h"
#include "../include/Board.hpp"
#include "../include/Stone.hpp"
#include "../include/Exceptions.hpp"

using namespace tellstones;

TEST(BoardTest, PlaceAndAt) {
    Board b;
    Stone s(StoneType::Hammer, true);
    b.place_stone(0,0,s);
    const Cell& cell = b.at(0,0);
    ASSERT_FALSE(cell.is_empty());
    EXPECT_EQ(cell.stone->type, StoneType::Hammer);
    EXPECT_TRUE(cell.stone->face_up);
}

TEST(BoardTest, PlaceOccupiedThrows) {
    Board b;
    Stone s(StoneType::Sword, true);
    b.place_stone(0,1,s);
    EXPECT_THROW(b.place_stone(0,1,s), InvalidMoveException);
}

TEST(BoardTest, FlipToggle) {
    Board b;
    Stone s(StoneType::Shield, false);
    b.place_stone(1,1,s);
    b.flip_stone(1,1);
    EXPECT_TRUE(b.at(1,1).stone->face_up);
    b.flip_stone(1,1);
    EXPECT_FALSE(b.at(1,1).stone->face_up);
}

TEST(BoardTest, FlipEmptyThrows) {
    Board b;
    EXPECT_THROW(b.flip_stone(2,2), InvalidMoveException);
}

TEST(BoardTest, SwapOccupied) {
    Board b;
    Stone a(StoneType::Anvil, true);
    Stone c(StoneType::Quill, true);
    b.place_stone(0,0,a);
    b.place_stone(2,2,c);
    b.swap_cells(0,0,2,2);
    EXPECT_EQ(b.at(0,0).stone->type, StoneType::Quill);
    EXPECT_EQ(b.at(2,2).stone->type, StoneType::Anvil);
}

TEST(BoardTest, SwapEmptyAndOccupied) {
    Board b;
    Stone a(StoneType::Sword, true);
    b.place_stone(0,0,a);
    // swap (0,0) with empty (1,1)
    b.swap_cells(0,0,1,1);
    EXPECT_TRUE(b.at(0,0).is_empty());
    EXPECT_FALSE(b.at(1,1).is_empty());
    EXPECT_EQ(b.at(1,1).stone->type, StoneType::Sword);
}

TEST(BoardTest, SwapTwoEmptyThrows) {
    Board b;
    EXPECT_THROW(b.swap_cells(0,0,1,1), InvalidMoveException);
}

TEST(BoardTest, TakeStone) {
    Board b;
    Stone a(StoneType::Dragon, true);
    b.place_stone(1,2,a);
    Stone taken = b.take_stone(1,2);
    EXPECT_EQ(taken.type, StoneType::Dragon);
    EXPECT_TRUE(b.at(1,2).is_empty());
}

TEST(BoardTest, EmptyCellsAndAllFilled) {
    Board b;
    // initially all empty
    auto empties = b.empty_cells();
    EXPECT_EQ(empties.size(), 9u);
    // fill all
    for (int r=0;r<Board::SIZE;++r) for (int c=0;c<Board::SIZE;++c)
        b.place_stone(r,c, Stone(StoneType::Hammer, true));
    EXPECT_TRUE(b.all_cells_filled());
    EXPECT_EQ(b.empty_cells().size(), 0u);
}
