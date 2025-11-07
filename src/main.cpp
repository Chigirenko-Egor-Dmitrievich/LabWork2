/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#include "../include/Game.hpp"
#include <iostream>

int main() {
    tellstones::Game g;
    std::string p1, p2;
    std::cout << "Enter name for Player 1: "; std::getline(std::cin, p1);
    if (p1.empty()) p1 = "Player1";
    std::cout << "Enter name for Player 2: "; std::getline(std::cin, p2);
    if (p2.empty()) p2 = "Player2";
    g.init(p1,p2);
    g.run();
    return 0;
}
