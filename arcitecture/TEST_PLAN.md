# Test Plan — TellStones

## Scope
Unit tests will cover non-interactive, deterministic classes and logic:
- Board: placement, flip, swap, take, bounds, empty_cells, all_cells_filled
- Deck: initialization (10 stones), draw_random, return_to_bottom, empty behavior
- Player: name and scoring
- Exceptions: thrown types
Interactive parts of Game (CLI loop and apply_special_on_place flows) will be covered via manual tests or separate integration tests that simulate stdin/stdout.

## Test strategy
- Unit tests (Google Test) for each class.
- For Board and Deck, include negative tests (ensure exceptions thrown on invalid input).
- For Game interactive behavior, prepare manual test scenarios (playthroughs) and optional integration tests that replay scripted stdin.

## Test cases (summary)
### Board
- Place stone in empty cell (success)
- Place in occupied cell (throws)
- Flip toggles face_up (success)
- Flip on empty cell (throws)
- Swap two occupied cells (success)
- Swap occupied with empty (success)
- Swap two empty cells (throws)
- take_stone returns and clears
- empty_cells returns expected list
- all_cells_filled returns true when board full

### Deck
- init_standard() results in size == 10
- draw_random reduces size and returns a Stone
- drawing until empty then drawing again throws DeckEmptyException
- return_to_bottom places stone back into deck (increases size)

### Player
- Player constructed with name; add_point increments score

### Game (programmatic)
- brag_programmatic with correct sequence awards 5 points to current player
- brag_programmatic with incorrect sequence awards 5 points to opponent

> NOTE: apply_special_on_place and Game::run are interactive; unit tests should not call these interactive loops. Integration tests that emulate stdin can exercise these flows later.

## Test environment
- Linux or macOS with g++ (supporting C++17)
- Google Test installed (libgtest-dev) or vendored
- Build via provided Makefile target test which links -lgtest -lgtest_main -lpthread

## Test metrics
- All unit tests must pass.
- Exceptions for invalid operations must be covered by tests.
