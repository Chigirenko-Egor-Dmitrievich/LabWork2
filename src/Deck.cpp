/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#include "../include/Deck.hpp"
#include "../include/Exceptions.hpp"
#include <algorithm>
#include <random>
#include <chrono>

namespace tellstones {

Deck::Deck() {
    init_standard();
}

void Deck::init_standard() {
    stones_.clear();

    // Exactly 10 starting stones, Egg is not included.
    std::vector<StoneType> base = {
        StoneType::Crown,
        StoneType::Rune,
        StoneType::Dragon,
        StoneType::Hammer,
        StoneType::Sword,
        StoneType::Shield,
        StoneType::Anvil,
        StoneType::Quill,
        StoneType::Scroll,
        StoneType::Scales
    };

    for (auto t : base) {
        stones_.emplace_back(t, true);
    }

    // Shuffle deck using a time-based seed for variability.
    auto seed = static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::mt19937 rng(seed);
    std::shuffle(stones_.begin(), stones_.end(), rng);
}

bool Deck::empty() const {
    return stones_.empty();
}

Stone Deck::draw_random() {
    if (stones_.empty()) {
        throw DeckEmptyException("Deck is empty");
    }
    // Since deck is shuffled, pop_back is fine and efficient.
    Stone s = stones_.back();
    stones_.pop_back();
    return s;
}

size_t Deck::size() const {
    return stones_.size();
}

void Deck::return_to_bottom(const Stone& s) {
    stones_.insert(stones_.begin(), s); // put at bottom (front) so draw (from back) won't immediately return it
}

} // namespace tellstones
