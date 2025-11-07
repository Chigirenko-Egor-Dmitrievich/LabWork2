# Test Report — TellStones (LabWork2)

Date: 01.11.2025  
Author: Chigirenko Egor  
Note: The tests in the report are unit tests using Google Test, covering non-interactive classes. Interactive scenarios are tested via manual integration tests or input/output scripts.

---

## 1. Test Environment

- OS: Ubuntu 20.04 / 22.04 (GitHub Actions uses ubuntu-latest)
- Compiler: g++ (>= 9), C++17
- Build: make (Makefile in the directory)
- Unit testing framework: Google Test (libgtest-dev)
- Commands:
  - Build project: make
  - Build tests: make
  - Run tests: ./run_tests

---

## 2. Test Coverage

Unit tests cover the following modules:
- Board — placement, flipping, swapping, taking stones, boundary checking, empty_cells, all_cells_filled.
- Deck — standard deck initialization (10 stones), draw_random, return_to_bottom, behavior when empty.
- Player — player name, score management.
- Logical part brag is tested through equivalent non-interactive tests.

Interactive parts (CLI loops, Game::run, apply_special_on_place) are not automated in the current unit tests. It is recommended to write separate integration tests using mock UI or scripts emulating stdin/stdout.

---

## 3. List of Tests (Files)

- tests/BoardTest.cpp
  - PlaceAndAt — placement and reading cell
  - PlaceOccupiedThrows — attempt to occupy an already filled cell
  - FlipToggle — flipping a stone toggles face_up
  - FlipEmptyThrows — flipping an empty cell throws exception
  - SwapOccupied — swapping two occupied cells
  - SwapEmptyAndOccupied — swapping occupied and empty cell
  - SwapTwoEmptyThrows — swapping two empty cells is prohibited
  - TakeStone — taking a stone clears the cell
  - EmptyCellsAndAllFilled — behavior of empty_cells and all_cells_filled

- tests/DeckTest.cpp
  - InitStandardSize10 — deck initialized with 10 stones
  - DrawRandomReducesSize — draw_random reduces size
  - DrawUntilEmptyThrows — drawing until deck is empty throws exception
  - ReturnToBottom — returning stone to bottom of the deck

- tests/PlayerTest.cpp
  - NameAndScore — verifying player name and adding points

- tests/GameLogicTest.cpp
  - BragEquivalentSuccess — equivalent of successful brag (board full, correct answers)
  - BragEquivalentFail — equivalent of failed brag
