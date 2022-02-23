# learnmoderncpp-tutorial

Complete, working programs from the C++ tutorial hosted at https://learnmoderncpp.com/course-details/

## Usage

The "headers" directory contains C++ programs with legacy header `#includes`,
whilst the "modules" directory contains the same programs but using the `import` keyword instead.

All programs compile successfully under Windows with Visual Studio 2019 (v16.8 or later).

The supplied batch scripts `build-vs2019-headers.bat` and
`build-vs2019-modules.bat` can be used to compile all of the programs within a Visual Studio command prompt terminal; simply run:
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"
or similar in a command window, or create a desktop link.

To compile individual programs under Linux, use:

```
g++ -std=c++20 -o prog prog.cpp # (for the headers versions)
```

or
```
clang++ -std=c++20 -o prog prog.cpp # (again for the headers versions)
```

Alternatively, run the supplied shell scripts which are supplied in both the "headers" and "modules" subdirectories.

**Contact:** cpptutor@outlook.com

