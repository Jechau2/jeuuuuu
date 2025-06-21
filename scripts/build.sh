#!/bin/sh
set -e

RUN_EXEC=false
if [ "$1" = "-r" ]; then
  RUN_EXEC=true
fi

mkdir -p build
cd build
cmake ..
make

if [ "$RUN_EXEC" = true ]; then
  ./jeuuuuu
fi
