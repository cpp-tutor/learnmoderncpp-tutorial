#!/bin/sh

# This script will compile all files with .cpp extension in the parent directory
# Clang version 16 (or newer) C++ modules version

if [ -z "$CLANG_PREFIX" ] ; then
  CLANG_PREFIX="/usr"
fi

if [ -z "$CLANG_PCM" ] ; then
   CLANG_PCM="./std.pcm"
fi

CLANG="$CLANG_PREFIX/bin/clang++"

if [ ! -f "$CLANG_PCM" ] ; then
  echo "Compiling library module..."
  if [ ! -f "$CLANG_PREFIX/share/libc++/v1/std.cppm" ] ; then
    echo "Error: Could not find file $CLANG_PREFIX/share/libc++/v1/std.cppm"
    echo "Please set environment variable CLANG_PREFIX and re-run script"
    exit 1
  fi
    LD_LIBRARY_PATH="$CLANG_PREFIX/lib":"$CLANG_PREFIX/lib/x86_64-unknown-linux-gnu" \
      "$CLANG" -std=c++23 -stdlib=libc++ -Wno-reserved-identifier -Wno-reserved-module-identifier \
      --precompile -o "$CLANG_PCM" "$CLANG_PREFIX/share/libc++/v1/std.cppm"
fi

failures=0
for PROGRAM in ../*.cpp ; do
  BASE="$(basename $PROGRAM)"
  echo "$BASE..."
  failed=""
  LD_LIBRARY_PATH="$CLANG_PREFIX/lib":"$CLANG_PREFIX/lib/x86_64-unknown-linux-gnu" \
    "$CLANG" -fmodule-file=std="$CLANG_PCM" -std=c++23 -stdlib=libc++ -o ${BASE%.cpp} $PROGRAM || failed="y"
  if [ -n "$failed" ] ; then
    echo "Failed to compile $BASE"
    failures=$((failures+1))
  fi
done
echo "A total of $failures files failed to compile."
