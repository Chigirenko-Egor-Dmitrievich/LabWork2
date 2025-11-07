/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#include "TerminalUI.hpp"
#include "Board.hpp"
#include "Deck.hpp"
#include "Player.hpp"
#include "Stone.hpp"
#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>

namespace tellstones {

void TerminalUI::clear_screen() const {
    // ANSI escape sequence to clear screen and move cursor home.
    std::cout << "\x1B[2J\x1B[H";
}

void TerminalUI::print_legend() const {
    std::cout << "Legend (index:name(abbr)):\n";
    std::cout << "0:Crown(CRN) 1:Rune(RUN) 2:Dragon(DRG) 3:Hammer(HAM) 4:Sword(SWR) 5:Shield(SHD) 6:Anvil(ANV) 7:Quill(QLL) 8:Scroll(SCR) 9:Scales(SCL) 10:Egg(EGG)\n";
}

void TerminalUI::print_board(const Board& board, bool reveal_face_down) const {
    std::cout << "     0     1     2\n";
    for (int r = 0; r < Board::SIZE; ++r) {
        std::cout << r << " ";
        for (int c = 0; c < Board::SIZE; ++c) {
            const auto& cell = board.at(r,c);
            if (cell.is_empty()) {
                std::cout << " [   ]";
            } else {
                std::string s = cell.stone->to_string();
                if (!cell.stone->face_up && !reveal_face_down) s = "???";
                std::cout << " [" << std::setw(3) << s << "]";
            }
        }
        std::cout << "\n";
    }
}

void TerminalUI::show_status(const Board& board, const Deck& deck, const std::array<Player,2>& players, int current_player) const {
    clear_screen();
    print_board(board, false);
    std::cout << "\n";
    print_legend();
    std::cout << "\nDeck size: " << deck.size() << "\n";
    std::cout << players[0].name() << ": " << players[0].score();
    if (current_player == 0) std::cout << " <- (current)";
    std::cout << " | ";
    std::cout << players[1].name() << ": " << players[1].score();
    if (current_player == 1) std::cout << " <- (current)";
    std::cout << "\n\n";
}

int TerminalUI::ask_action(int minv, int maxv) const {
    std::cout << "Choose action:\n";
    std::cout << "0: PlaceRandom 1:Flip 2:Swap 3:Peek 4:Challenge 5:Brag 6:GiveUp\n";
    return ask_int("Action", minv, maxv);
}

int TerminalUI::ask_int(const std::string& prompt, int minv, int maxv) const {
    int v;
    while (true) {
        std::cout << prompt << " (" << minv << "-" << maxv << "): ";
        if (!(std::cin >> v)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input: please enter a number.\n";
            continue;
        }
        if (v < minv || v > maxv) {
            std::cout << "Out of range: input must be between " << minv << " and " << maxv << ".\n";
            continue;
        }
        // consume trailing newline for subsequent getline uses
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return v;
    }
}

std::pair<int,int> TerminalUI::ask_coords(const std::string& prompt_row, const std::string& prompt_col, int minv, int maxv) const {
    int r = ask_int(prompt_row, minv, maxv);
    int c = ask_int(prompt_col, minv, maxv);
    return {r,c};
}

bool TerminalUI::ask_confirm(const std::string& prompt) const {
    std::string s;
    while (true) {
        std::cout << prompt << " (y/n): ";
        if (!(std::cin >> s)) return false;
        if (s == "y" || s == "Y") return true;
        if (s == "n" || s == "N") return false;
        std::cout << "Please answer 'y' or 'n'.\n";
    }
}

void TerminalUI::show_message(const std::string& message) const {
    std::cout << message << "\n";
}

} // namespace tellstones
