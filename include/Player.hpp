/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#ifndef TELLSTONES_PLAYER_HPP
#define TELLSTONES_PLAYER_HPP

#include <string>

namespace tellstones {

class Player {
public:
    Player() = default;
    Player(std::string name);
    const std::string& name() const;
    int score() const;
    void add_point();

private:
    std::string name_;
    int score_{0};
};

} // namespace tellstones

#endif // TELLSTONES_PLAYER_HPP
