.PHONY: all build rebuild check clean launch

all: clean check build

BUILD_DIRECTORY = build

TARGET_COVERAGE = [789]

BUILD = ./scripts/run_build.sh
CHECK = ./scripts/run_linters.sh
LAUNCH = ./build/project/Archiver

launch:
	${LAUNCH}

clean:
	rm -rf build

check:
	${CHECK}

build:
	${BUILD}

rebuild: clean build
