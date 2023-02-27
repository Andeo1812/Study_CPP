.PHONY: all launch

all: build launch

# Example: make TARGET=Base/challenge/binary_search/binary_search.cpp
build:
	g++ -g --std=gnu++23 -Wall -Wextra -Werror -Wpedantic ${TARGET} -o task

launch:
	./task

check:
	./scripts/run_linters.sh
