#!/bin/sh
set -e

ROOT_DIR="$(dirname "$0")/.."
FILES=$(find "$ROOT_DIR/src" "$ROOT_DIR/include" -name '*.cpp' -o -name '*.h')

if command -v clang-format >/dev/null 2>&1; then
  clang-format -i $FILES
else
  echo 'clang-format not installed' >&2
  exit 1
fi
