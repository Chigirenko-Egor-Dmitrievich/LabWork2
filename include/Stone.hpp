/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#ifndef TELLSTONES_STONE_HPP
#define TELLSTONES_STONE_HPP

#pragma once
#include <string>

namespace tellstones {

enum class StoneType {
    Crown, Rune, Dragon, Hammer, Sword, Shield,
    Anvil, Quill, Scroll, Scales, Egg
};

struct Stone {
    StoneType type;
    bool face_up;

    Stone(StoneType t = StoneType::Egg, bool up = true) : type(t), face_up(up) {}

    std::string to_string() const {
        switch (type) {
            case StoneType::Crown:  return "CRN";
            case StoneType::Rune:   return "RUN";
            case StoneType::Dragon: return "DRG";
            case StoneType::Hammer: return "HAM";
            case StoneType::Sword:  return "SWR";
            case StoneType::Shield: return "SHD";
            case StoneType::Anvil:  return "ANV";
            case StoneType::Quill:  return "QLL";
            case StoneType::Scroll: return "SCR";
            case StoneType::Scales: return "SCL";
            case StoneType::Egg:    return "EGG";
        }
        return "UNK";
    }
};

} // namespace tellstones

#endif // TELLSTONES_STONE_HPP
