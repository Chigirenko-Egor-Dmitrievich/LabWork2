/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#ifndef TELLSTONES_ACTION_HPP
#define TELLSTONES_ACTION_HPP

namespace tellstones {

enum class ActionType {
    PlaceRandom = 0,
    Flip = 1,
    Swap = 2,
    Peek = 3,
    Challenge = 4,
    Brag = 5,
    GiveUp = 6
};

} // namespace tellstones

#endif // TELLSTONES_ACTION_HPP
