/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#ifndef TELLSTONES_BOARD_HPP
#define TELLSTONES_BOARD_HPP

#include "Cell.hpp"
#include <array>
#include <optional>
#include <vector>
#include <string>

namespace tellstones {

class Board {
public:
    static constexpr int SIZE = 3;
    Board();

    // Place a stone into an empty cell. Throws InvalidMoveException if cell occupied or out of range.
    void place_stone(int r, int c, const Stone& s);

    // Flip the stone at (r,c). Throws InvalidMoveException if empty or out of range.
    void flip_stone(int r, int c);

    // Swap two positions. Throws InvalidMoveException if coordinates out of range.
    void swap_cells(int r1, int c1, int r2, int c2);

    // Remove and return stone at (r,c). Throws InvalidMoveException if empty.
    Stone take_stone(int r, int c);

    const Cell& at(int r, int c) const;
    bool all_cells_filled() const;
    std::vector<std::pair<int,int>> empty_cells() const;

private:
    std::array<std::array<Cell, SIZE>, SIZE> grid_;

    void check_bounds(int r, int c) const;
};

} // namespace tellstones

#endif // TELLSTONES_BOARD_HPP
