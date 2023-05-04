# About this Tutorial

## Why (Modern) C++?

C++ is a living programming language. What began as Bjarne Stroustrup's research project at Bell Labs in the late 1970s has grown into an ISO-Standardized language and library, with regular new releases co-ordinated by an ISO Committee. During that time countless over-hyped programming languages have appeared (and disappeared), whilst C++ has continually "borrowed" new ideas from other contemporary or newer languages.

The main reasons for C++'s success story are speed and stability; well-written programs compile to efficient code and are reliable after deployment. C++ is an AOT (ahead-of-time) compiled language, and usually compiles straight to the machine language of the target processor; this means that full (re-)compilation must take place for each deployment to a new platform architecture. The source-code must be available, under either a closed- or open-source license, in order to compile to a specific platform; also it is not possible to recreate C++ source code by reverse-engineering an executable (or library) binary object. C++ is scalable and runs on everything from 32K RAM Arduino up to supercomputers, supporting small, compact programs with little link-time overhead as well as projects containing millions of lines of source code.

Modern C++ is a massive improvement over earlier versions. It is in many ways unrecognizable to the C++ of the late 1980s and early 1990s when the reference compiler, called "Cfront", was written entirely by Stroustrup and compiled C++ to C, not assembly language. Since C++ ceased to be a largely one-man effort in the mid-1990s there have been numerous ISO Standards published; these are commonly known as C++98, C++03, C++11, C++14, C++17 and C++20, with the next release expected to be called C++23. Of these, C++11 and C++20 have seen the biggest changes to the language, and have caused the most work for compiler writers.

Of course, it is far easier to add features to a language than remove them (this phenomenon is known in the industry as "feature creep"), and the later versions of C++ are almost entirely a feature superset compared to previous versions (with some redundant features deprecated or removed). "Remember the Vasa!" is something Stroustrup is quoted as saying comparatively recently (referring to the wooden Swedish battleship that capsized and sank on its maiden voyage) and it is clear that he would be wary of continuing to promote a top-heavy, Christmas-wishlist-featured language. The good news is that almost all C++ programs written in the last twenty-or-so years will compile with few or no modifications using the latest compilers. Also, Modern C++ adds features that are useful even in comparatively simple programs, making them easier to comprehend; cleaning up overly verbose and non-intuitive syntax has been a major focus for newer versions of C++.

## Why this Tutorial?

I have been learning and using C++ since around 2002, and Modern C++ is the language I wish had been available to me back then; I believe it is an easier language to learn to use productively than older versions. Of course, there have been many books written about C++ over the years, but unavoidably most of these will be (badly) out-of-date. Even [Stroustrup's](https://stroustrup.com) "The C++ Programming Language" (Fourth Edition)[^1] only covers up to and including C++11.

This online self-study course has been put together as a personal project designed to be accessible and comprehensible to anyone without any previous experience of programming in compiled languages; hopefully, no material is presented without suitable context and explanation. The format is a conversational-tone introduction to a topic followed by an example program (in many cases intended to be compiled and run, with all source code [available on GitHub](https://github.com/cpp-tutor/learnmoderncpp-examples/)[^2]). Then a list of points-of-interest follows the code, often followed by a number of possible modifications that you (the reader) are invited to make in order to cement your understanding. Each Chapter introduces several related topics.
 
Most people "learn by doing" (kinesthetic learning) and for decades it has been recognized that the only way to become proficient in a programming language is to write working programs in it. There are dozens (hundreds?) of C++ video tutorials available elsewhere on the Web, and if these are more suited to your learning style, then great! However, I believe that written information is more likely to be taken in than spoken, both at first reading and in review. The course materials (this Tutorial) have been made freely available and are intended to be improved over time. Spelling, technical and other errors will be present, and I welcome feedback and suggestions for improvement; please leave a comment or drop me an email, thanks!

## Which compiler should I choose when learning C++?

The best-known C++ compilers are Microsoft Visual Studio C++[^3] (MSVC, cl), the FSF GNU Compiler Collection[^4] (GCC, g++) and Apple's Clang/LLVM[^5] (clang++). All of these aggressively follow the progress of the ISO Standard and are under (ongoing) heavy development. If you are programming under Windows, you may want to seriously consider Microsoft's Visual Studio, which comes with an IDE and C++ compiler (the latter as an optional component, this needs to be selected in the installer) and has cost-free variants for students and individuals; it is also possible to use Clang (via the installer) as a drop-in replacement within Visual Studio (clang-cl). If you're a Mac user, you'll probably want to install Xcode, which includes Clang/LLVM. Linux users probably have both GCC and Clang packaged for their distribution, and Clang's libc++ may be available too. Also, Stephan T. Lavavej (primary architect of MSVC) makes MinGW (g++ for Windows) available from his [personal website](https://nuwen.net/mingw.html)[^6] (note: this does not require Visual Studio to be installed, but can coexist on the same machine).

Any of these compiler/OS combinations are suitable for new C++ coders, with Clang giving possibly the most user-friendly error messages, which could be an important factor. In fact to start learning C++, you don't even need to install a compiler on your system if you can't, or don't want to; head to the [Compiler Explorer](https://godbolt.org)[^7] which provides just about every available C++ compiler (and versions including trunk development), and can even execute your program code (although interactive programs are not supported).

Learning any (programming) language is hard, and of course you will make many errors when starting out. Don't forget, the error messages your compiler gives you are designed to help you write correct code. In a coding/debugging session it can often feel as if you are "fighting the compiler", which can at times be frustrating. Try to think of it this way: if coding is musicianship, the compiler is your instrument. Treat it carefully, learn its nuances, and listen to it with the experience that comes from practice.

## Compiling your first program

Plain text C++ *source code* files must be translated into a binary form understood by the hardware in order to be *executed*, or run. This translation process is called *compilation*, and has to be repeated every time the source code is modified. It is assumed you have a C++ compiler installed and working; for the purposes of testing the code examples in this Tutorial I used Microsoft Visual C++ 16.7.6 (later versions should work too). Under Windows it is possible to use the command line and the installer should have created Start Menu entries called "x64 Native Tools Command Prompt for VS 2022", or similar, so simply select this and a Command Window (shell) should open showing a message such as `[vcvarsall.bat] Environment initialized for: 'x64'`. Under Linux and MacOS simply open a new shell and navigate with `cd` to wherever the source file is located.

The simple programs we will introduce and create will consist of just one source file each, as in the first example program `01-hellow.cpp` available from GitHub[^2] and also listed in full in the first Chapter of this Tutorial. To compile this program use one of the following:

* **MSVC**: `cl /EHsc /std:c++latest 01-hellow.cpp` 
* **GCC**: `g++ -o 01-hellow -std=c++20 01-hellow.cpp`
* **Clang**: `clang++ -o 01-hellow -std=c++20 -stdlib=libc++ 01-hellow.cpp`

Note: Different options are used with the different compilers and when using `import` instead of `#include`.

Successful compilation produces an *executable binary* called `01-hellow.exe` (under Windows) or `01-hellow` (MacOS or Linux). This can be run by typing `01-hellow.exe` (or just `01-hellow`) into a Windows console (see graphic below), or by typing `./01-hellow` into a MacOS or Linux Terminal (both assuming that the executable is located in the current directory). I don't recommend running the program by double-clicking it in an Explorer or File Manager window as any output may be lost as the program exits, so your program may not actually appear to do anything! 

![Output from running the above program under Windows 10](https://learnmoderncpp.files.wordpress.com/2023/02/compile-console.png)

[^1]: https://stroustrup.com
[^2]: https://github.com/cpp-tutor/learnmoderncpp-examples/
[^3]: https://visualstudio.microsoft.com
[^4]: https://gcc.gnu.org
[^5]: https://clang.llvm.org
[^6]: https://nuwen.net/mingw.html
[^7]: https://godbolt.org

*All text and program code &copy;2019-2022 Richard Spencer, all rights reserved.*
