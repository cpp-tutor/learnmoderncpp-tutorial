# learnmoderncpp-tutorial

Complete, working programs from the C++ tutorial hosted at:

https://learnmoderncpp.com/course-details/

## Usage

The "headers" subdirectory contains C++ programs with legacy header `#includes`, whilst the "modules" subdirectory contains the same programs but using the `import` keyword instead. See https://learnmoderncpp.com/2020/09/05/where-are-c-modules/ for more details about C++ compilers which have support for modules.

## Compiling under Windows

All programs compile successfully under Windows with Visual Studio 2019 (v16.8 or later).

The supplied batch scripts `build-vs2019-headers.bat` and
`build-vs2019-modules.bat` can be used to compile all of the programs within a Visual Studio command prompt, simply run:

```C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat```

or similar in a command window, or create a desktop link, and then run either of the build scripts.

Alternatively, to compile individual programs from within a Visual Studio command prompt run either (modules):

```
cl /EHsc /std:c++latest /experimental:moodule /MD 00-example.cpp
```

or (headers):

```
cl /EHsc /std:c++latest 00-example.cpp
```

substituting the correct file for `00-example.cpp` in either case.

## Compiling under Linux

To compile individual programs in the "headers" subdirectory under Linux, use:

```
g++ -std=c++20 -o 00-example 00-example.cpp
```

or:

```
clang++ -std=c++20 -o 00-example 00-example.cpp
```

substituting both occurrencies of `00-example` with the correct file name.

Alternatively, run one of the supplied shell scripts `build-gcc-headers.sh` or `build-clang-headers.sh` which are supplied in the "headers" subdirectory, or `build-clang-modules.sh` found in the "modules" subdirectory. (The last of these needs to change `import std.core;` to `import std;` for each source file before compilation, using the `sed` utility.)
