/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#ifndef TELLSTONES_TERMINAL_UI_HPP
#define TELLSTONES_TERMINAL_UI_HPP

#include <string>
#include <utility>
#include <array>

namespace tellstones {
class Board;
class Deck;
class Player;

class TerminalUI {
public:
    TerminalUI() = default;

    // Print full board with optional reveal for face-down stones.
    void print_board(const Board& board, bool reveal_face_down = false) const;

    // Print status: board, deck size, player scores and current player highlight.
    void show_status(const Board& board, const Deck& deck, const std::array<Player,2>& players, int current_player) const;

    // Ask an action index (e.g. 0..5). Will re-prompt until valid integer in range is entered.
    int ask_action(int minv, int maxv) const;

    // Ask an integer within range with prompt.
    int ask_int(const std::string& prompt, int minv, int maxv) const;

    // Ask for pair coordinates (row, col) with a single prompt label.
    std::pair<int,int> ask_coords(const std::string& prompt_row, const std::string& prompt_col, int minv = 0, int maxv = 2) const;

    // Ask yes/no confirmation. Returns true for 'y'/'Y', false for 'n'/'N'.
    bool ask_confirm(const std::string& prompt) const;

    // Show a message to the user (info, warnings etc.)
    void show_message(const std::string& message) const;

    // Print legend (stone type indices and short names).
    void print_legend() const;

    // Clear screen (simple approach using ANSI escape; safe to ignore if terminal doesn't support).
    void clear_screen() const;
};

} // namespace tellstones

#endif // TELLSTONES_TERMINAL_UI_HPP
