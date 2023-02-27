.PHONY: all launch

all: build launch

# Example: make TARGET=Base/challenge/binary_search/binary_search.cpp
build:
	g++ -g --std=gnu++20 -Wall -Wextra -Werror -Wpedantic ${TARGET} -o task

launch:
	./task
