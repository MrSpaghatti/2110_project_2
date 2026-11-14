# Smart Campus Navigation and Facility Analytics System -- Makefile
#
# The compile line below is the SAME command documented in README.txt under
# BUILD, kept byte-identical on purpose: one build recipe, two ways to run it
# (typing the command, or `make`).
#
# Usage:
#   make        build the project -> campus
#   make check  syntax-check every source file without linking
#   make run    build, then run against the default data/ directory
#   make clean  remove the binary and object files (campus is git-ignored)

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude
SRCS     = $(wildcard src/*.cpp)
TARGET   = campus

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

check:
	$(CXX) $(CXXFLAGS) -fsyntax-only $(SRCS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) src/*.o

.PHONY: all check run clean