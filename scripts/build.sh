#!/bin/sh
set -e

if [ "$1" = "-r" ]; then
  make makerun
else
  make
fi
