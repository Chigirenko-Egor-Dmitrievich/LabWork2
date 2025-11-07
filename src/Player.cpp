/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#include "../include/Player.hpp"

namespace tellstones {

Player::Player(std::string name) : name_(std::move(name)) {}

const std::string& Player::name() const { return name_; }
int Player::score() const { return score_; }
void Player::add_point() { ++score_; }

} // namespace tellstones
