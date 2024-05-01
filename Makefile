CXX = gcc
CXX_FLAGS = -std=c++17 -Wall -Wextra -Os
LD_FLAGS = -lraylib -lstdc++

all: compile run

compile:
	$(CXX) -o ./out/sandit ./src/main.cpp $(CXX_FLAGS) $(LD_FLAGS)

run:
	./out/sandit