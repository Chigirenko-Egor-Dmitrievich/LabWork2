# Makefile for LabWork2 TellStones project
CXX = g++
CXXFLAGS = -g -Wall -Werror -Wpedantic -Iinclude
TESTFLAGS = -lgtest -lgmock -pthread

TARGET = run
TEST_TARGET = run_tests

# Sources for the main target
TARGET_SOURCES = src/main.cpp src/Game.cpp src/Board.cpp src/Deck.cpp src/Player.cpp src/TerminalUI.cpp

# Sources for the test target
TEST_TARGET_SOURCES = test/BoardTest.cpp test/DeckTest.cpp test/PlayerTest.cpp test/GameLogicTest.cpp src/Game.cpp src/Board.cpp src/Deck.cpp src/Player.cpp src/TerminalUI.cpp

TARGET_OBJECTS = $(TARGET_SOURCES:.cpp=.o)
TEST_TARGET_OBJECTS = $(TEST_TARGET_SOURCES:.cpp=.o)

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(TARGET_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET_OBJECTS)

$(TEST_TARGET): $(TEST_TARGET_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_TARGET_OBJECTS) $(TESTFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

format:
	astyle -A1 -s4 src/*.cpp include/*.hpp test/*.cpp

clean:
	rm -f $(TARGET_OBJECTS)
	rm -f $(TEST_TARGET_OBJECTS)

cleanall:
	rm -f $(TARGET_OBJECTS)
	rm -f $(TEST_TARGET_OBJECTS)
	rm -f $(TARGET)
	rm -f $(TEST_TARGET)

.PHONY: all test clean format
