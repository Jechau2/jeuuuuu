#!/bin/sh
set -e

BIN_DIR="$(dirname "$0")/../bin"

if [ ! -f "$BIN_DIR/jeuuuuu" ]; then
  echo "Binary not found. Build the project first." >&2
  exit 1
fi

"$BIN_DIR/jeuuuuu" "$@"
