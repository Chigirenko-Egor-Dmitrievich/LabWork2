/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#include "../include/Board.hpp"
#include "../include/Exceptions.hpp"

namespace tellstones {

Board::Board() {
    // grid_ default-initialized
}

void Board::check_bounds(int r, int c) const {
    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE)
        throw InvalidMoveException("Coordinates out of range");
}

void Board::place_stone(int r, int c, const Stone& s) {
    check_bounds(r,c);
    if (!grid_[r][c].is_empty()) throw InvalidMoveException("Cell already occupied");
    grid_[r][c].stone = s;
}

void Board::flip_stone(int r, int c) {
    check_bounds(r,c);
    if (grid_[r][c].is_empty()) throw InvalidMoveException("Cannot flip an empty cell");
    grid_[r][c].stone->face_up = !grid_[r][c].stone->face_up;
}

void Board::swap_cells(int r1, int c1, int r2, int c2) {
    check_bounds(r1,c1);
    check_bounds(r2,c2);
    if (grid_[r1][c1].is_empty() && grid_[r2][c2].is_empty())
        throw InvalidMoveException("Swapping two empty cells is meaningless");
    std::swap(grid_[r1][c1].stone, grid_[r2][c2].stone);
}

Stone Board::take_stone(int r, int c) {
    check_bounds(r,c);
    if (grid_[r][c].is_empty()) throw InvalidMoveException("No stone to take at that position");
    Stone s = *grid_[r][c].stone;
    grid_[r][c].clear();
    return s;
}

const Cell& Board::at(int r, int c) const {
    check_bounds(r,c);
    return grid_[r][c];
}

bool Board::all_cells_filled() const {
    for (int r = 0; r < SIZE; ++r)
        for (int c = 0; c < SIZE; ++c)
            if (grid_[r][c].is_empty()) return false;
    return true;
}

std::vector<std::pair<int,int>> Board::empty_cells() const {
    std::vector<std::pair<int,int>> out;
    for (int r=0;r<SIZE;++r) for (int c=0;c<SIZE;++c) if (grid_[r][c].is_empty()) out.emplace_back(r,c);
    return out;
}

} // namespace tellstones
