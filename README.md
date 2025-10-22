# learnmoderncpp-tutorial

## Contents

All of the source Markdown pages for the Modern C++ Tutorial on https://learnmoderncpp.com/ plus complete, working programs machine-extracted from the course text.

**Note:** Some Chapters have had significant changes made to update them to C++23, and not all programs compile successfully yet. In particular, use of `std::println()` with `import std;` does not compile. In case of issues with your compiler please see the Releases page for the C++20 version of the Tutorial.

**New:** Jupyter Notebooks have been auto-generated from the source Markdown files and are located in the `jupyter-notebooks` directory. You will need the executable `jupyter-lab` available with suitable C++ kernels, see output from running `jupyter kernelspec list` (tested with kernel `cpp23`, which needs to be set on first load).

The "headers" subdirectory contains C++ programs with legacy header `#includes`, whilst the "modules" subdirectory contains the same programs using the `import` keyword instead. See https://learnmoderncpp.com/2020/09/05/where-are-c-modules/ for more details about C++ compilers which have support for modules.

The "scripts" subdirectory contains a C++ program which extracts all programs from the Markdown source to the above two folders.

## Compiling under Windows

Most programs compile successfully under Windows with Visual Studio 2022 (v17.8 or later), some of the modules versions (as noted above) do not currently compile.

The supplied batch scripts `build-vs2022-headers.bat` and `build-vs2022-modules.bat` can be used to compile all of the programs within a Visual Studio command prompt, simply run:

```
C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat
```

or similar in a command window, or create a desktop link, and then run either of the build scripts.

Alternatively, to compile individual programs from within a Visual Studio command prompt, run either (modules):

```
cl /EHsc /std:c++latest /MTd 00-example.cpp
```

or (headers):

```
cl /EHsc /std:c++latest 00-example.cpp
```

substituting the correct file for `00-example.cpp` in either case. Note that the modules versions need file `std.obj` in the current directory, see the build script for how to create this.

## Compiling under Linux

To compile individual programs in the "headers" subdirectory under Linux, use:

```
g++ -std=c++23 -o 00-example 00-example.cpp
```

or:

```
clang++ -std=c++23 -o 00-example 00-example.cpp
```

substituting both occurrencies of `00-example` with the correct file name.

Alternatively, run one of the supplied shell scripts `build-gcc-headers.sh` or `build-clang-headers.sh` which are supplied in the "headers/build" subdirectory, or `build-clang-modules.sh` found in the "modules/build" subdirectory.
