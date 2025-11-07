/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#ifndef TELLSTONES_GAME_HPP
#define TELLSTONES_GAME_HPP

#include "Board.hpp"
#include "Deck.hpp"
#include "Player.hpp"
#include "Action.hpp"
#include "TerminalUI.hpp"
#include <array>
#include <string>
#include <vector>

namespace tellstones {

class Game {
public:
    Game() = default;

    void init(const std::string& p1, const std::string& p2);
    void run();

    // Programmatic helpers (used by tests)
    void place_random_at(int row, int col);
    void flip_at(int row, int col);
    void swap_at(int r1,int c1,int r2,int c2);
    void peek_at(int row,int col);
    void challenge_at(int row,int col);
    void brag_programmatic(const std::vector<int>& ordered_types);

private:
    Board board_;
    Deck deck_;
    std::array<Player,2> players_;
    int current_player_{0};

    TerminalUI ui_;

    int opponent_index() const { return 1 - current_player_; }

    bool perform_action(ActionType action);

    bool handle_place_random();
    bool handle_flip();
    bool handle_swap();
    bool handle_peek();
    bool handle_challenge();
    bool handle_brag();
    bool handle_give_up();

    void apply_special_on_place(const Stone& placed, int placed_row, int placed_col);

    bool check_victory() const;
};

} // namespace tellstones

#endif // TELLSTONES_GAME_HPP
