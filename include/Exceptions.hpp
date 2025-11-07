/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#ifndef TELLSTONES_EXCEPTIONS_HPP
#define TELLSTONES_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace tellstones {

class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& msg) : std::runtime_error(msg) {}
};

class InvalidMoveException : public GameException {
public:
    explicit InvalidMoveException(const std::string& msg) : GameException(msg) {}
};

class DeckEmptyException : public GameException {
public:
    explicit DeckEmptyException(const std::string& msg = "Deck is empty") : GameException(msg) {}
};

} // namespace tellstones

#endif // TELLSTONES_EXCEPTIONS_HPP
