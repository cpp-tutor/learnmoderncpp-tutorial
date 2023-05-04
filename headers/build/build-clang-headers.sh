#!/bin/sh

# This script will compile all files with .cpp extension in the parent directory
# Clang C++ headers version

failures=0
for PROGRAM in ../*.cpp ; do
  BASE="$(basename $PROGRAM)"
  echo "$BASE..."
  failed=""
  clang++ -std=c++20 -o ${BASE%.cpp} $PROGRAM >/dev/null 2>&1 || failed="y"
  if [ -n "$failed" ] ; then
    echo "Failed to compile $BASE"
    failures=$((failures+1))
  fi
done
echo "A total of $failures files failed to compile."
