#!/bin/sh

# This script will compile all files with .cpp extension in current directory
# GCC C++ headers version

failures=0
for PROGRAM in *.cpp ; do
  echo "$PROGRAM..."
  failed=""
  g++ -std=c++20 -o ${PROGRAM%.cpp} $PROGRAM >/dev/null 2>&1 || failed="y"
  if [ -n "$failed" ] ; then
    echo "Failed to compile $PROGRAM"
    failures=$((failures+1))
  fi
done
echo "A total of $failures files failed to compile."
