/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#ifndef TELLSTONES_CELL_HPP
#define TELLSTONES_CELL_HPP

#include "Stone.hpp"
#include <optional>

namespace tellstones {

struct Cell {
    std::optional<Stone> stone;

    bool is_empty() const { return !stone.has_value(); }
    void clear() { stone.reset(); }
};

} // namespace tellstones

#endif // TELLSTONES_CELL_HPP
