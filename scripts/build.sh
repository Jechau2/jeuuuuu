#!/bin/sh
set -e

BUILD_DIR="$(dirname "$0")/../build"
TYPE=${1:-Debug}

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
cmake -DCMAKE_BUILD_TYPE=$TYPE ..
cmake --build .
