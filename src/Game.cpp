/*
    Чигиренко Егор Дмитриевич st128240@student.spbu.ru
    LabWork3
*/

#include "Game.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <sstream>
#include <vector>

namespace tellstones {

void Game::init(const std::string& p1, const std::string& p2) {
    players_[0] = Player(p1);
    players_[1] = Player(p2);
    deck_.init_standard();
}

bool Game::check_victory() const {
    return players_[0].score() >= 5 || players_[1].score() >= 5;
}

void Game::run() {
    ui_.show_message("Welcome to TellStones (terminal) — improved UI");
    // main loop: alternate players until victory
    while (!check_victory()) {
        // show_status prints board + legend + deck size + scores
        ui_.show_status(board_, deck_, players_, current_player_);

        bool turn_finished = false;
        // Player keeps trying until they execute a valid action that ends their turn
        while (!turn_finished && !check_victory()) {
            // actions range 0..6
            int action_idx = ui_.ask_action(0, 6);
            ActionType chosen = static_cast<ActionType>(action_idx);
            try {
                turn_finished = perform_action(chosen);
            } catch (const GameException& ge) {
                // Game-level exceptions: show and let player try again
                ui_.show_message(std::string("Error: ") + ge.what());
                turn_finished = false;
            } catch (const std::exception& ex) {
                ui_.show_message(std::string("Unexpected error: ") + ex.what());
                turn_finished = false;
            }
        }

        // check victory right after a successful turn
        if (check_victory()) break;

        // next player's turn
        current_player_ = opponent_index();
    }

    // endgame summary
    ui_.show_status(board_, deck_, players_, current_player_);
    if (players_[0].score() > players_[1].score()) ui_.show_message(players_[0].name() + " wins!");
    else if (players_[1].score() > players_[0].score()) ui_.show_message(players_[1].name() + " wins!");
    else ui_.show_message("Game ended in a draw.");
}

// Dispatcher: calls corresponding handler
bool Game::perform_action(ActionType action) {
    switch (action) {
        case ActionType::PlaceRandom: return handle_place_random();
        case ActionType::Flip:       return handle_flip();
        case ActionType::Swap:       return handle_swap();
        case ActionType::Peek:       return handle_peek();
        case ActionType::Challenge:  return handle_challenge();
        case ActionType::Brag:       return handle_brag();
        case ActionType::GiveUp:     return handle_give_up();
        default:
            ui_.show_message("Unknown action. Try again.");
            return false;
    }
}

// === Action handlers (return true if action completed and turn ends) ===
bool Game::handle_place_random() {
    if (deck_.empty()) { ui_.show_message("Deck empty: cannot place a random stone."); return false; }

    // draw a random stone from deck
    Stone drawn;
    try {
        drawn = deck_.draw_random();
    } catch (const DeckEmptyException&) {
        ui_.show_message("Deck became empty unexpectedly.");
        return false;
    }

    ui_.show_message(std::string("Random stone drawn: ") + drawn.to_string() +
                     (drawn.face_up ? " (face_up)" : " (face_down)"));

    // ask for target coordinates
    auto coord = ui_.ask_coords("target row", "target col", 0, Board::SIZE - 1);
    int r = coord.first, c = coord.second;

    // confirm
    if (!ui_.ask_confirm("Confirm place to (" + std::to_string(r) + "," + std::to_string(c) + ")?")) {
        ui_.show_message("Placement cancelled. Returning stone to bottom of deck.");
        deck_.return_to_bottom(drawn);
        return false; // allow player to choose action again
    }
// attempt to place
    try {
        board_.place_stone(r, c, drawn);
    } catch (const InvalidMoveException& im) {
        ui_.show_message(std::string("Invalid placement: ") + im.what());
        deck_.return_to_bottom(drawn); // return so it's not lost
        return false; // player retries
    }

    // apply mandatory special effects; these loops internally until valid sub-action
    try {
        apply_special_on_place(drawn, r, c);
    } catch (const GameException& ge) {
        // Unexpected; inform and treat as completed turn (to avoid infinite loops)
        ui_.show_message(std::string("Special effect error: ") + ge.what());
    }

    // successful placement completes turn
    return true;
}

bool Game::handle_flip() {
    auto coord = ui_.ask_coords("flip row", "flip col", 0, Board::SIZE - 1);
    int r = coord.first, c = coord.second;
    // check if empty — invalid but does not end turn (player retries)
    try {
        board_.flip_stone(r, c);
        ui_.show_message("Flipped cell (" + std::to_string(r) + "," + std::to_string(c) + ").");
        return true; // valid flip ends turn
    } catch (const InvalidMoveException& im) {
        ui_.show_message(std::string("Flip failed: ") + im.what() + " Try again.");
        return false; // allow retry
    }
}

bool Game::handle_swap() {
    ui_.show_message("Choose two positions to swap.");
    auto a = ui_.ask_coords("swap row-1", "swap col-1", 0, Board::SIZE - 1);
    auto b = ui_.ask_coords("swap row-2", "swap col-2", 0, Board::SIZE - 1);

    // if both empty, warn and allow retry
    const Cell& cell1 = board_.at(a.first, a.second);
    const Cell& cell2 = board_.at(b.first, b.second);
    if (cell1.is_empty() && cell2.is_empty()) {
        ui_.show_message("Both selected cells are empty. Swapping two empty cells is meaningless. Try again.");
        return false;
    }

    // confirm
    if (!ui_.ask_confirm("Confirm swap (" + std::to_string(a.first) + "," + std::to_string(a.second) +
                         ") <-> (" + std::to_string(b.first) + "," + std::to_string(b.second) + ")?")) {
        ui_.show_message("Swap cancelled.");
        return false;
    }

    try {
        board_.swap_cells(a.first, a.second, b.first, b.second);
        ui_.show_message("Swap executed.");
        return true;
    } catch (const InvalidMoveException& im) {
        ui_.show_message(std::string("Swap failed: ") + im.what());
        return false;
    }
}

bool Game::handle_peek() {
    auto coord = ui_.ask_coords("peek row", "peek col", 0, Board::SIZE - 1);
    int r = coord.first, c = coord.second;
    try {
        const Cell& cell = board_.at(r, c);
        if (cell.is_empty()) {
            ui_.show_message("Empty cell: nothing to peek. Try again.");
            return false;
        }
        if (cell.stone->face_up) {
            ui_.show_message(std::string("Stone already face-up: ") + cell.stone->to_string());
            return false;
        } else {
            ui_.show_message(std::string("Peek reveals: ") + cell.stone->to_string());
            return true;
        }
        
    } catch (const InvalidMoveException& im) {
        ui_.show_message(std::string("Peek failed: ") + im.what());
        return false;
    }
}

bool Game::handle_challenge() {
    ui_.show_message("Select coordinates to challenge (opponent will name the stone).");
    auto coord = ui_.ask_coords("row", "col", 0, Board::SIZE - 1);
    int r = coord.first, c = coord.second;
    try {
        const Cell& cell = board_.at(r, c);
        if (cell.is_empty()) {
            ui_.show_message("No stone there. Challenge invalid. Try again.");
            return false;
        }
        // ask opponent to guess
        ui_.show_message(std::string("Challenged player: ") + players_[opponent_index()].name() + " - please name the stone type by index:");
ui_.show_message("0:Crown(CRN) 1:Rune(RUN) 2:Dragon(DRG) 3:Hammer(HAM) 4:Sword(SWR) 5:Shield(SHD) 6:Anvil(ANV) 7:Quill(QLL) 8:Scroll(SCR) 9:Scales(SCL) 10:Egg(EGG)");
        int guess = ui_.ask_int("guess", 0, 10);
        int actual = static_cast<int>(cell.stone->type);
        if (guess == actual) {
            ui_.show_message(std::string("Correct. ") + players_[opponent_index()].name() + " gains 1 point.");
            players_[opponent_index()].add_point();
        } else {
            ui_.show_message(std::string("Incorrect. ") + players_[current_player_].name() + " gains 1 point.");
            players_[current_player_].add_point();
        }
        return true;
    } catch (const InvalidMoveException& im) {
        ui_.show_message(std::string("Challenge failed: ") + im.what());
        return false;
    }
}

bool Game::handle_brag() {
    if (!board_.all_cells_filled()) {
        ui_.show_message("Cannot brag: the board must be completely filled. Try again later.");
        return false;
    }

    ui_.show_message("Brag attempt: name all positions row-major (enter type index for each cell). Failure gives opponent 5 points.");
    bool success = true;
    for (int r = 0; r < Board::SIZE; ++r) {
        for (int c = 0; c < Board::SIZE; ++c) {
            int guess = ui_.ask_int("type at next cell", 0, 10);
            const Cell& cell = board_.at(r, c);
            if (cell.is_empty() || static_cast<int>(cell.stone->type) != guess) {
                success = false;
            }
        }
    }

    if (success) {
        ui_.show_message(std::string("Perfect! Automatic victory for ") + players_[current_player_].name());
        for (int i = 0; i < 5; ++i) players_[current_player_].add_point();
    } else {
        ui_.show_message("Incorrect. Opponent receives 5 points.");
        for (int i = 0; i < 5; ++i) players_[opponent_index()].add_point();
    }
    return true;
}

bool Game::handle_give_up() {
    // Current player gives up: opponent wins immediately.
    ui_.show_message(players_[current_player_].name() + " gives up!");
    ui_.show_message(players_[opponent_index()].name() + " is declared winner.");

    // Grant opponent enough points to trigger victory.
    while (players_[opponent_index()].score() < 5) players_[opponent_index()].add_point();

    return true; // ends the turn; run() will detect victory and finish
}

// === Special effects applied immediately after placement ===
// These effects are mandatory; the code prompts until a valid sub-action is executed.
void Game::apply_special_on_place(const Stone& placed, int placed_row, int placed_col) {
    // Crown: peek if any face-down stones other than the newly placed crown exist
    if (placed.type == StoneType::Crown) {
        bool any_face_down = false;
        for (int r = 0; r < Board::SIZE; ++r) for (int c = 0; c < Board::SIZE; ++c) {
            if (r == placed_row && c == placed_col) continue;
            const Cell& cell = board_.at(r,c);
            if (!cell.is_empty() && !cell.stone->face_up) { any_face_down = true; break; }
        }
        if (!any_face_down) {
            ui_.show_message("No face-down stones available to peek; Crown peek is skipped.");
        } else {
            ui_.show_message("Placed Crown: you must peek one face-down stone of your choice.");
            while (true) {
                auto coord = ui_.ask_coords("peek row", "peek col", 0, Board::SIZE - 1);
                try {
                    const Cell& cell = board_.at(coord.first, coord.second);
                    if (cell.is_empty()) { ui_.show_message("Selected cell is empty. Choose a non-empty cell."); continue; }
                    if (coord.first == placed_row && coord.second == placed_col) { ui_.show_message("You cannot peek the crown you just placed; choose another cell."); continue; }
if (cell.stone->face_up) { ui_.show_message("Selected stone is already face-up. Choose a face-down stone."); continue; }
                    ui_.show_message(std::string("Peek reveals: ") + cell.stone->to_string());
                    break; // effect resolved
                } catch (const InvalidMoveException& im) {
                    ui_.show_message(std::string("Invalid coordinates: ") + im.what());
                }
            }
        }
    }

    // Rune: must swap two stones if possible. If rune is the only stone on board, allow swapping the rune with any empty cell (move it).
    if (placed.type == StoneType::Rune) {
        ui_.show_message("Placed Rune: you must swap two stones on the board (choose two positions).");

        // Count non-empty cells excluding the placed rune
        int non_empty_others = 0;
        for (int r = 0; r < Board::SIZE; ++r) for (int c = 0; c < Board::SIZE; ++c) {
            if (r == placed_row && c == placed_col) continue;
            if (!board_.at(r,c).is_empty()) ++non_empty_others;
        }

        // If there are no other occupied cells, allow swapping the rune with any empty cell.
        if (non_empty_others == 0) {
            ui_.show_message("No other stones present. You may move the Rune by swapping it with any empty cell.");
            while (true) {
                auto target = ui_.ask_coords("target row to swap with rune", "target col", 0, Board::SIZE - 1);
                try {
                    // if target is same as placed position, it's a no-op; ask again
                    if (target.first == placed_row && target.second == placed_col) {
                        ui_.show_message("Selected the same position as the rune; choose a different cell.");
                        continue;
                    }
                    // allow swap placed <-> target even if target empty
                    if (!ui_.ask_confirm("Confirm moving rune to (" + std::to_string(target.first) + "," + std::to_string(target.second) + ")?")) {
                        ui_.show_message("Cancelled. Choose another target.");
                        continue;
                    }
                    board_.swap_cells(placed_row, placed_col, target.first, target.second);
                    ui_.show_message("Rune moved.");
                    break;
                } catch (const InvalidMoveException& im) {
                    ui_.show_message(std::string("Swap failed: ") + im.what());
                }
            }
        } else {
            // Normal case: there are other stones; require swapping two positions, but forbid swapping two empties
            while (true) {
                auto a = ui_.ask_coords("swap row-1", "swap col-1", 0, Board::SIZE - 1);
                auto b = ui_.ask_coords("swap row-2", "swap col-2", 0, Board::SIZE - 1);
                const Cell& cell1 = board_.at(a.first, a.second);
                const Cell& cell2 = board_.at(b.first, b.second);
                if (cell1.is_empty() && cell2.is_empty()) {
                    ui_.show_message("Both selected cells are empty. Choose at least one non-empty cell.");
                    continue;
                }
                if (!ui_.ask_confirm("Confirm rune swap?")) { ui_.show_message("Swap cancelled; please choose again."); continue; }
                try {
                    board_.swap_cells(a.first, a.second, b.first, b.second);
                    ui_.show_message("Rune swap executed.");
                    break;
                } catch (const InvalidMoveException& im) {
                    ui_.show_message(std::string("Swap failed: ") + im.what());
                }
            }
        }
    }

    // Dragon: must replace any stone on the board with an Egg (preserve face orientation).
    if (placed.type == StoneType::Dragon) {
ui_.show_message("Placed Dragon: you must replace any stone on board with an Egg (if none, replace the dragon itself).");
        while (true) {
            auto coord = ui_.ask_coords("replace row", "replace col", 0, Board::SIZE - 1);
            try {
                // if target is occupied, replace it with Egg keeping face orientation
                if (!board_.at(coord.first, coord.second).is_empty()) {
                    Stone replaced = board_.take_stone(coord.first, coord.second);
                    board_.place_stone(coord.first, coord.second, Stone(StoneType::Egg, replaced.face_up));
                    ui_.show_message("Replaced target stone with Egg.");
                    break;
                } else {
                    // target empty: replace the dragon itself (at placed_row, placed_col) with Egg
                    ui_.show_message("Target cell is empty; replacing the placed Dragon with an Egg.");
                    Stone removed = board_.take_stone(placed_row, placed_col); // should be the dragon
                    board_.place_stone(placed_row, placed_col, Stone(StoneType::Egg, removed.face_up));
                    break;
                }
            } catch (const InvalidMoveException& im) {
                ui_.show_message(std::string("Replace failed: ") + im.what());
            }
        }
    }
}

// === Programmatic helpers (used in tests) ===
void Game::place_random_at(int row, int col) {
    if (deck_.empty()) throw DeckEmptyException("Deck empty");
    Stone s = deck_.draw_random();
    board_.place_stone(row, col, s);
    apply_special_on_place(s, row, col);
}

void Game::flip_at(int row, int col) {
    board_.flip_stone(row, col);
}

void Game::swap_at(int r1,int c1,int r2,int c2) {
    board_.swap_cells(r1,c1,r2,c2);
}

void Game::peek_at(int row,int col) {
    const Cell& cell = board_.at(row, col);
    if (cell.is_empty()) throw InvalidMoveException("Empty cell");
    // reveal for test purposes (no UI)
}

void Game::challenge_at(int row,int col) {
    const Cell& cell = board_.at(row, col);
    if (cell.is_empty()) throw InvalidMoveException("Empty cell");
    // programmatic challenge would require a guess parameter; tests should call handle_challenge in special test harness or simulate input.
}

void Game::brag_programmatic(const std::vector<int>& ordered_types) {
    if (!board_.all_cells_filled()) throw InvalidMoveException("Board not full");
    // ordered_types must have Board::SIZE * Board::SIZE elements
    if ((int)ordered_types.size() != Board::SIZE * Board::SIZE) throw InvalidMoveException("Invalid brag size");
    bool ok = true;
    int idx = 0;
    for (int r = 0; r < Board::SIZE; ++r) for (int c = 0; c < Board::SIZE; ++c) {
        const Cell& cell = board_.at(r,c);
        if (cell.is_empty() || static_cast<int>(cell.stone->type) != ordered_types[idx]) ok = false;
        ++idx;
    }
    if (ok) {
        for (int i=0;i<5;i++) players_[current_player_].add_point();
    } else {
        for (int i=0;i<5;i++) players_[opponent_index()].add_point();
    }
}

} // namespace tellstones
