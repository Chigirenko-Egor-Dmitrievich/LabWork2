# Requirements — TellStones Terminal Game

## 1. Functional Requirements

R1. The system shall maintain a 3×3 board of cells. Each cell may contain at most one stone or be empty.

R2. There shall be a deck containing exactly 10 starting stones (one of each of the 10 non-Egg stone types). The Egg stone is not in the initial deck.

R3. A Stone has:
 - type ∈ {Crown, Rune, Dragon, Hammer, Sword, Shield, Anvil, Quill, Scroll, Scales, Egg}
 - face_up (boolean).

R4. Two players alternate turns until one player's score is ≥ 5 or GiveUp is invoked.

R5. On the player's turn the system shall allow choosing exactly one action: PlaceRandom (0), Flip (1), Swap (2), Peek (3), Challenge (4), Brag (5), GiveUp (6).

R6. PlaceRandom:
  - Draw a random stone from the deck (removing it from the deck).
  - Prompt the player for a target cell (row, col).
  - Require explicit confirmation before placement.
  - If placement fails (cell occupied/out of range), the drawn stone is returned to the bottom of the deck and player retries (turn not consumed).
  - After successful placement, apply special rules for Crown/Rune/Dragon immediately.

R7. Flip:
  - Player chooses coordinates.
  - If the cell is empty → show message "Cannot flip an empty cell" and allow player to choose again (turn not consumed).
  - Otherwise flip the stone; flip is a valid action and ends the turn.

R8. Swap:
  - Player selects two coordinates.
  - If both selected cells are empty → show message "Swapping two empty cells is meaningless" and allow retry (turn not consumed).
  - Otherwise confirm; perform swap and end the turn.

R9. Peek:
  - Player selects coordinates.
  - If cell is empty → show message "Empty cell: nothing to peek" and allow retry (turn not consumed).
  - If cell is face-up → display its type and allow retry (turn not consumed).
  - If cell is face-down → reveal the stone and this action ends the turn.

R10. Challenge:
  - Player selects coordinates.
  - If cell is empty → show message and allow retry.
  - The opponent names the stone type by index.
  - If opponent is correct → opponent gains 1 point. If incorrect → challenger gains 1 point.
  - Action ends the turn.

R11. Brag:
  - Only allowed when the board is fully filled (all 9 cells occupied). Deck state does not matter.
  - Player must name the stone types in row-major order. If all correct → player gains 5 points (wins). If any wrong → opponent gains 5 points.
  - Action ends the turn (and likely ends game).

R12. GiveUp:
  - Ends the game immediately: opponent is declared winner.

R13. UI:
  - TerminalUI::show_status shall print:
    - Board with header row: "     0     1     2"
    - Legend showing indices and abbreviations for all stone types (0..10)
    - Deck size and players’ scores, marking current player
  - Board class shall not print; all printing done by UI.

R14. Exceptions:
  - Invalid board access / operations shall throw InvalidMoveException.
  - Drawing from empty deck throws DeckEmptyException.

## 2. Non-Functional Requirements

N1. Implementation language: C++17.

N2. Unit tests written with Google Test.

N3. Code comments and in-code text shall be in English.

N4. The game shall be resilient to human input errors — erroneous inputs do not end the player's turn.

## 3. Use Cases (concrete scenarios)

### UC1 — PlaceRandom successful
1. Player chooses PlaceRandom
2. System draws stone S, shows short desc.
3. Player chooses empty cell (r,c), confirms
4. System places S at (r,c); applies special effect (if any)
5. Turn ends

### UC2 — PlaceRandom but cancel
1. Player draws stone S
2. Player chooses cell but cancels confirmation
3. System returns S to bottom of deck
4. Player may choose next action (turn not consumed)

### UC3 — Flip on empty cell
1. Player chooses Flip and selects empty cell
2. System shows message "Cannot flip an empty cell" — allows retry (turn not consumed)

### UC4 — Peek on face-up
1. Player chooses Peek and selects face-up cell
2. System displays stone type and allows retry (turn not consumed)
### UC5 — Brag when board full
1. Player chooses Brag; board full
2. Player names all 9 types in order
3. System compares and assigns points (5 to bragger or to opponent)

(There are similar scenarios for Rune/Dragon/Crown special effects; they are described in the effect sections above.)
