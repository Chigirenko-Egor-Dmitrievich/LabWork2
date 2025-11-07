# TellStones — Terminal C++ Implementation (OOP)

## Overview

This project is a terminal-based, object-oriented (C++17) implementation inspired by the TellStones mini-game.  
The game is played on a 3×3 board by two players that alternate turns. On a turn a player must choose one action. The goal is to reach 5 points.

### Stones (types)
- Crown (CRN)
- Rune (RUN)
- Dragon (DRG)
- Hammer (HAM)
- Sword (SWR)
- Shield (SHD)
- Anvil (ANV)
- Quill (QLL)
- Scroll (SCR)
- Scales (SCL)
- Egg (EGG) — not present initially in the deck; produced by Dragon effect.

Each stone has a face orientation (face_up / face_down).

### Actions (player can choose exactly one per turn)
0. PlaceRandom — draw a random stone from the deck and attempt to place it face-up in a chosen cell.
1. Flip — flip a stone in a chosen cell (face-up ↔ face-down).
2. Swap — swap two cells on the board.
3. Peek — look at a face-down stone (reveal it to the player).
4. Challenge — challenge the opponent to name the stone in a selected cell.
5. Brag — if the board is full, attempt to name positions of all stones (success = auto-win; failure = opponent gains 5 points).
6. GiveUp — surrender; opponent immediately wins.

### Special stone effects (applied immediately after placement)
- Crown: player must peek one *other* face-down stone if any exist; if none exist, effect is skipped.
- Rune: player must swap two stones; if rune is the only stone on board, player may swap the rune with any empty cell (move rune).
- Dragon: player must replace any stone on board with an Egg; if there are no other stones, the dragon is replaced by an Egg.

### Victory conditions
- First player to reach ≥ 5 points wins.
- Brag success grants 5 points to the bragger (instant win).
- GiveUp grants the opponent enough points to reach victory immediately.

## Structure (selected files)
- include/ — public headers (Board.hpp, Deck.hpp, Game.hpp, Player.hpp, Stone.hpp, TerminalUI.hpp, Action.hpp, Exceptions.hpp)
- src/ — implementation .cpp files
- tests/ — Google Test unit tests
- make/Makefile — build/test helper

## Notes
- TerminalUI is the only module that prints the board and messages; Board is purely a data and logic model (no printing).
- Interactive operations (Game run-loop, apply_special_on_place) are intentionally interactive and therefore not fully covered by unit tests; for full automation a test harness or mock UI is required.
