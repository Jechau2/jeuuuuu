.PHONY: all build run clean

all: build

build:
	./scripts/build.sh

run:
	./scripts/run.sh

clean:
	rm -rf build bin
