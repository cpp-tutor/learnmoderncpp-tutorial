#!/bin/sh

# This script will compile all files with .cpp extension in current directory
# Clang Version 12 (trunk) C++ modules version

failures=0
for PROGRAM in *.cpp ; do
  echo "$PROGRAM..."
  failed=""
  cat $PROGRAM | sed 's/\.core//' | clang++ -fmodules -std=c++20 -stdlib=libc++ -o ${PROGRAM%.cpp} -x c++ - >/dev/null 2>&1 || failed="y"
  if [ -n "$failed" ] ; then
    echo "Failed to compile $PROGRAM"
    failures=$((failures+1))
  fi
done
echo "A total of $failures files failed to compile."
