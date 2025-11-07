/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#ifndef TELLSTONES_DECK_HPP
#define TELLSTONES_DECK_HPP

#include "Stone.hpp"
#include <vector>
#include <cstddef>

namespace tellstones {

class Deck {
public:
    Deck();               // constructs and initializes a standard deck of stones (10 stones)
    void init_standard(); // reinitialize a standard deck
    bool empty() const;
    Stone draw_random();  // draw a stone (throws DeckEmptyException if empty)
    size_t size() const;

    // Return a stone to the bottom of the deck (used when placement is cancelled).
    void return_to_bottom(const Stone& s);

private:
    std::vector<Stone> stones_;
};

} // namespace tellstones

#endif // TELLSTONES_DECK_HPP
