# Files and Formatting

## Formatting values and variables for output

We have seen how values and variables can be put to output streams using `<<`, and how `print()` and `println()` can be used to output subsequent parameters using curly braces in the format string. For further control over the way these are output, such as field width, accuracy etc. we can specify this using stream manipulators (when outputting to streams) or extra information in the *format string* (when using `print()`/`println()`). Manipulators are covered later in this Chapter, what follows is a discussion of how to use *format specifiers* with `print()`, `println()` and `format()`/`format_to()`.

The following program demonstrates use of format specifiers for some common types:

```cpp
// 08-format1.cpp : Basic usage of format string

#include <print>
#include <string>
using namespace std;

int main() {
    string s{ "Formatted" };
    auto d{ 10.0 / 3.0 };
    auto i{ 20000 };
    println("{0:20}:{2:8}, {1:12.11}", s, d, i);
}
```

This program outputs the text `Formatted` followed by sufficient spaces to pad up to a width of 20 characters, then a colon present in the format string, then the value `20000` right-aligned to a width of 8 characters, then the comma and space present in the format string, and finally the value 3.3333333333 at a "precision" of 11 figures (plus decimal point) padded to a width of 12 characters (only padding, as opposed to truncation, is possible).

**Experiment**:

* Try printing the three parameters in a different order, by changing the numbers before the colon within the curly braces.

* Is it possible to achieve the same results when removing these numbers altogether?

* What happens if you repeat one of `s`, `d`, or `i` in the parameter list? Or take one away?

The format string, and its associated format specifier(s), are evaluated at compile-time for maximum performance. It must therefore be a string literal, not a string-type variable (unless it is `constexpr`). The values of the subsequent parameters referenced by the format specifier(S) can (and probably will) change during the run of the program.

## Format specifiers

As well as describing the field width and precision for all of the built-in types (plus several Standard Library types), format specifiers offer fine-grained control over the output. In fact, all format specifiers are made up of eight optional parts, all of which (if used) appear in order after the colon in the format string. These are listed in the table below:

| Field          | Description                                         | Example | Result                   |
|----------------|-----------------------------------------------------|---------|--------------------------|
| Fill-and-align | Optional fill character then: <, >, or ^            | {:@>10} | @@@@1233456              |
| Sign           | One of: +, - (default), or space                    | {:+}    | +1.23                    |
| #              | Use alternate form                                  | {:#}    | 0x12a, 3.0               |
| 0              | Pad integers with leading zeros                     | {:06}   | 000123                   |
| Width          | Minimum field width                                 | {:10}   | "abc       "             |
| Precision      | FP-precision, maximum field width                   | {:.7}   | 3.333333, "Formatt"      |
| L              | Use locale-specific setting                         | {L}     | 12,345, 1.234,56, "faux" |
| Type           | One of: b, B, d, o, x, X, a, A, e, E, f, F, g, G, ? | {:8.7a} | 1.aaaaaabp+1             |

It is also possible to write custom formatters which operate on arbitrary format specifiers and user-defined classes. An alternative method would be to create a public `toString()` method in the class and simply invoke this on a parameter of this type (after the format string, which would use plain `{}`).

The format specifiers listed above work with `print()` and `println()` as well as other functions from the `<format>` header (which include wide-character variants). Here is a complete list:

| Function      | Description                                     | Parameters                     | Return value                    |
|---------------|-------------------------------------------------|--------------------------------|---------------------------------|
| `print()`       | Output to `stdout`, `FILE*` or `std::ostream` | [dest, ] fmt, ...              | None                            |
| `println()`     | As for `print()` with trailing newline        | [dest, ] fmt, ...              | None                            |
| `format()`      | Create a string from (wide) format string     | [locale, ] fmt, ...            | `std::string`, `std::wstring`   |
| `format_to()`   | Write to a (wide) output iterator             | iter, [locale, ] fmt, ...      | `out` member is `std::iterator` |
| `format_to_n()` | As for `format_to()` with size limit          | iter, max, [locale, ] fmt, ... | `out` member is `std::iterator` |

In choosing between the above functions, the aim would be to choose the most performant for the task. The following program outputs different format strings and parameters utilizing a variety of these functions:

```cpp
// 08-format2.cpp : Various format string-using functions

#include <print>
#include <format>
#include <string>
#include <iostream>
#include <iterator>
#include <array>
#include <cmath>
using namespace std;

int main() {
    string world{ "World" };
    print(cout, "Hello, {}!\n", world);
    println("{1} or {0}", false, true);
    
    constexpr const char *fmt = "Approximation of π = {:.12g}";
    string s = format(fmt, asin(1.0) * 2);
    cout << s << '\n';
    
    constexpr const wchar_t *wfmt = L"Approximation of pi = {:.12g}";
    wstring ws = format(wfmt, asin(1.0) * 2);
    wcout << ws << L'\n';
    
    format_to(ostream_iterator<char>(cout), "Hello, {}!\n", world);
    wstring ww{ L"World" };
    array<wchar_t,9> wa;
    auto iter = format_to_n(wa.begin(), 8, L"Hello, {}!\n", ww);
    *(iter.out) = L'\0';
    wcout << wa.data() << L'\n';
}
```

A few things to note about this program:

* The use of `print()` is straightforward and simply outputs `Hello, World!` on a single line, using the variant that prints to a `std::ostream`, in this case `cout`.

* The call to `println()` reverses the order of its subsequent parameters and outputs them textually: `true or false`. You should be aware that this prints to the C standard output (`stdout`); mixing C++ stream and C output can sometimes cause buffering issues.

* The uses of `format()`, firstly with a 8-bit, and secondly with a wide-character format string, create a temporary (wide-)string and then put this to the (wide-)character output stream.

* The function `format_to()` is called with `ostream_iterator<char>(cout)` which is boilerplate for creating a suitable output iterator from a stream object.

* The use for `format_to_n()` is more involved as it uses a fixed size `std::array` to hold the wide-character output string. The first parameter is the (writable) iterator pointing to the start of the array, and the second is the maximum number of characters to write. The return value has an `out` data member which is the iterator pointing to the next character in the array, which needs to be set to zero in order to allow putting (`std::array`'s, not `std::string`'s) `data()` to `wcout`.

**Experiment:**

* Modify this program to use different field widths. Do they work with wide characters?

* Try some of the different format specifiers from the table above, together with different built-in types such as `long long` and `double`.

## Simple file access

All of the programs we have seen so far lose their internal state, together with any user input, when they exit. A program which can save and/or restore its state makes use of *persistence*. The way this is usually achieved, of course, is to enable saving to and loading from a disk file, stored on a hard-drive, memory card or network server.

C++ file access using the Standard Library header `<fstream>` is designed to be analogous to use of `cin` and `cout`, using the stream extraction (`>>`) and insertion (`<<`) operators. File access using the C Library's `<cstdio>` header is also possible, and a suitable `FILE *` pointer can be passed as the first parameter to `print()` and `println()` to switch output to that file.

The following program reads from a previously created file and echoes the content to the console. (The filename is provided at run-time as the first environment parameter after the executable name.) This program is only safe to use with text files, so fire up your favorite editor and create a test file to use, including some whitespace such as spaces, tabs and newlines.

```cpp
// 08-file1.cpp : echo disk file to console

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cerr << "Syntax: " << argv[0] << " <text file name>\n";
        return 1;
    }
    ifstream infile{ argv[1] };
    
    int c = infile.get();
    while (c != ifstream::traits_type::eof()) {
        cout << static_cast<char>(c);
        c = infile.get();
    }
}
```

A few things to note about this program:

* A sanity check is made on the number of environment parameters in order that executing the program without a filename argument won't cause a null-pointer dereference. The value in `argv[0]` is the name the program was executed as.

* A `std::ifstream` object called `infile`, which encapsulates the functionality of an input file stream as a class, is created by providing a filename as its constructor argument.

* An explicit call to close the input file is not needed, this happens automaticalls whien `infile` goes out of scope.

* The only parts of this class we use is the member function `get()`, which confusingly returns an `int`, not a `char` as you might expect, and `ifstream::traits_type::eof()`. The `int` returned by `get()` can be any of the valid range of `char` (usually 0 to 255, or -128 to 127 if `char` is signed) plus a special marker value outside this range to indicate that the *end-of-file* has been reached and no more characters can be read. (If the double-double-colon syntax confuses you don't worry, this boilerplate can be used without a detailed knowledge of the makeup of the stream classes. Using it is better style than relying on C's `EOF` macro from `<cstdio>`.)

* The `while`-loop body uses a cast to convert the variable `c` from an `int` to a `char` in order to ensure that is output as a character and not as a number.

**Experiment:**

* Try removing `static_cast<char>` and see what happens. Consider whether this could ever be desirable.

* What happens if you change the same line to `cout.put(c);`?

* Rewrite the loop to be a `for`-loop. Can you remove the need for any statements in the loop body?

The above program can be modified to no longer need the check against `ifstream::traits_type::eof()`. This involves use of a `char` variable and the stream extraction operator `>>`, as shown in the following program:

```cpp
// 08-file2.cpp : echo disk file to console

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cerr << "Syntax: " << argv[0] << " <text file name>\n";
        return 1;
    }
    ifstream infile{ argv[1] };

    char c;
    while (!infile.eof()) {
        infile >> noskipws >> c;
        cout << c;
    }
}
```

A few differences to note about this program:

* There is no read operation before the loop body.

* The member function `eof()` is used to check for end-of-file; this returns a boolean.

* A *stream manipulator* called `noskipws` is used to prevent skipping of whitespace (such as tabs) from the input file.

* No cast is needed to output `c`.

**Experiement:**

* Remove the stream manipulator and one of the `>>`'s. What do you notice when the input file contains spaces, tabs etc?

* Add the standalone statement line `infile >> noskipws;` before the `while`-loop, and use plain `infile >> c;` within it. What do you notice now? (The entity `noskipws` is actually a *manipulator* which modifies the stream it is put to.)

* Rewrite the loop as a `for`-loop. Can you again remove the need for any statements in the body?

## Files as streams

The member functions `get()` and `put()` are adequate for simple character access to C++ streams but are not easily extensible. (Think of the complexity involved in reading a `std::string` or a`double` using only these member functions.) When reading input files, the stream extraction operator is overloaded for all of the built-in types, as well as `std::string`. Similarly, the stream insertion operator is overloaded for files being written to, and works identically to the use of `cout` and `cerr` we are familiar with. We will see that you can write your own custom input and output overloads fairly easily, too.

Saving the state of a program (possibly in binary format) is sometimes called *serialization*, while loading it back is called *deserialization*. Of course, there are no guarantees that the same platform is being used to load the previously serialized state back in, so considerations such as *endian-ness* (big versus little) and *address width* (32 versus 64 bit) can come into play. A way round this issue is to use plain text representation (solely), and in our example programs we will be using text files exclusively.

The following program is our calculator program from previously, modified to read calculations to be performed from a text file. These are read one by one, and the results are output. When all of the input file has been read, the program exits. The functionality which has been seen before is contained in the `calc()` function, with the addition of support for exponent:

```cpp
// 08-calc.cpp : read from a file and perform calculations

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double calc(char op, double x, double y) {
    double r{};
    switch (op) {
    case '+':
        r = x + y;
        break;
    case '-':
        r = x - y;
        break;
    case '*':
        r = x * y;
        break;
    case '/':
        if (y) {
            r = x / y;
        }
        else {
            cerr << "Error: divide by zero.\n";
        }
        break;
    case '^':
        r = pow(x, y);
        break;
    default:
        cerr << "Error: invalid op.\n";
    }
    return r;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cerr << "Syntax: " << argv[0] << " <input file name>\n";
        return 1;
    }
    ifstream infile{argv[1]};

    while (!infile.eof()) {
        double x, y;
        char op;
        infile >> x >> op >> y;
        if (infile.fail() || infile.bad()) {
            cerr << "Error in input.\n";
            break;
        }
        auto r = calc(op, x, y);
        cout << x << ' ' << op << ' ' << y << " = " << r << '\n';
    }
}
```

**Experiment:**

* Does it matter if the last line of the input file is blank? Follow the logic of the main loop of the program and try to understand why this is.

* Put all of the calculations on one line, with a space between each one (instead of a newline). Does the program still produce the same output? Why do you think this is?

* Modify the program to write its output to a `std::ofstream` called `outfile`, initialized with `argv[2]`. (Remember to check for `argc` being exactly three.) What happens if there is an error in the input file?

It is also possible to use the stream extraction operator to read a `std::string`. The following program demonstrates this:

```cpp
// 08-string.cpp : read a string using the stream extraction operator

#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "Please enter your first name:\n";
    string name;
    cin >> name;
    cout << "Hi, \'" << name << "\', nice to meet you!\n";
}
```

**Experiment:**

* What happens if your input contains whitespace at the beginning or end?

* What happens if your input contains whitespace in the middle (eg. you enter your full name)?

* Modify the program to accept a first name and surname, in that order. Can you see any limitations with that approach?

You may be tempted to use `noskipws` to help you enter a line of text containing whitespace, however this only includes preceding whitespace in the input string.  The requirement of getting a line of input, possibly containing whitespace, is a common one, and we'll cover this next.

## Lines and buffers

So far we have seen byte (8-bit character) raw input as well as formatted input. However, programs (especially interactive ones) often get their input line-by-line. Lines of input can often be evaluated for errors and processed more reliably than relying on the stream extraction operator and repeatedly checking against `fail()` and `bad()`. In the case of a line of input being found to be invalid, the program can prompt the user to try again.

The following program uses the `getline()` **member** function to obtain a line of input from the console. This function takes two parameters: the address of a C-style array, and its size in bytes. Care must be taken to provide both a valid array address and correct length. The line of text **can** include spaces and is stored in the array **without** a newline and **with** a trailing zero-byte character.

```cpp
// 08-line1.cpp : obtain a line of input from the user and display it

#include <iostream>
using namespace std;

int main() {
    cout << "Please enter your full name:\n";
    char line[32];
    cin.getline(line, size(line));
    cout << "You entered: \'" << line << "\'\n";
}
```

**Experiment:**

* Try entering a blank line (just press Enter); does the program cope well with this? How does this differ from program `08-string.cpp`?

* Now try reducing the size of the array to something less than the text you will type in; how well does the program cope?

* Try checking `cin.fail()` after typing in something bigger than the size of the array.

As can be found from experimentation, any characters that do not fit into the C-style array are left in the input buffer and are left unprocessed; also the *fail-bit* is set in the input stream's flags, meaning any further calls to `getline()` will return an empty string. The stream fail-bit for `cin` can be unset with `cin.clear()`, after which the unprocessed characters can be read with further call(s) to `getline()`. Optionally, the `ignore()` member function can be used to skip one or more input characters.

There is also a **non-member** function which we met in Chapter 7, perhaps confusingly also named `getline()`, which reads directly from an input stream object into a `std::string`. There is no restriction to the length of the input which can be stored in the `std::string`, and the input ends with a newline (which is not stored). The following program demonstrates the use of this function, with minimal changes from the previous one:

```cpp
// 08-line2.cpp : obtain a line of input from the user, store it in a string variable and display it

#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "Please enter your full name:\n";
    string s;
    getline(cin, s);
    cout << "You entered: \'" << s << "\'\n";
}
```

A couple of things to note about this program:

* The `std::string` variable `s` grows to the length of the input from non-member `getline()` dynamically, limited only by available memory.

* Input is terminated by entering a new-line, which is discarded (not appended to `s`).

* This `getline()` function can work in this way as it takes both of its parameters by reference, giving it the ability to modify them.

**Experiment:**

* Modify the program (taking parts from others seen recently) to copy a text-file line by line from one disk file into another, so that they are identical. Compare the input and output files with a binary editor, checksum, or similar.

* Try the same program on a binary file (such as an executable). Are the input and output files identical? Hint: under Windows it is necessary to open both input and output files in binary mode; this is achieved by providing `ios_base::binary` as the second parameter to both `std::ifstream` and `std::ofstream` constructors.

The non-member `getline()` has a third parameter, which is the character value which terminates input (this defaults to `'\n'`). This is less commonly used, but setting it to `'\0'` can enable reading of an entire text-file at once (so long as it does not contain any NUL-byte characters). The following program demonstrates this:

```cpp
// 08-line3.cpp : read a text file into a string variable and display it

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cerr << "Syntax: " << argv[0] << " <text file name>\n";
        return 1;
    }
    ifstream infile{argv[1]};

    string s;
    getline(infile, s, '\0');
    cout << s;
}
```

**Experiment:**

* Does the program cope with whitespace, and control characters such as BEL (`'\a'`)?

* Adapt this program to copy a binary input file to an output file, making sure they are identical. (Hint: Binary files can, and often do, contain NUL-byte characters, so this needs to be catered for.)

* Modify this program to use the stream **member** functions `read()`, `gcount()` and `write()` instead of `getline()` and `cout`. Hint: these functions work with C-style arrays and fixed-size binary data; look up further details in an online resource or reference book.

## String streams

The concept of string streams is a simple one: read from or write to a `std::string` as if it were a file or stream object. There are three types of string stream:

* *Input string streams* are created from a `std::string`, and can subsequently read values into previously defined variables using the stream extraction operator.

* *Output string streams* are created empty, and can be written to using the stream insertion operator, with the resulting `std::string` available from its `str()` member function.

* A third string stream type which combines both of the above sets of functionality.

There are a number of possible advantages to using string streams as opposed to reading from or writing to files or stream objects directly:

* Performance may be better when caching line(s) of output (or input) in memory when writing to (or reading from) a disk file or network socket.

* Flags set (or manipulators used) on string stream objects don't affect global `cin`/`cout`/`cerr` or `std::ifstream`/`std::ofstream` formatting states.

* For output string streams the buffer grows dynamically so there is no risk of either buffer overflow or truncation.

* For input string streams that set the fail-bit or bad-bit, backtracking and/or error recovery may be quicker and easier.

Output string stream functionality is encapsulated in the `std::ostringstream` class. Firstly a default constructed object is defined, which is then written to with variables or constants using the stream insertion operator in exactly the same way as for `cout`. When the `std::ostringstream` is complete (all values have been written to it), the underlying `std::string` object can be extracted with the `str()` member function. The following simple program demonstrates this, writing its output to `puts()` (a function from the C Standard Library which accepts a `const char *`):

```cpp
// 08-stringstream1.cpp : write to string stream

#include <sstream>
#include <iomanip>
#include <cstdio>
using namespace std;

int main() {
    ostringstream oss{};
    oss.precision(3);
    oss << fixed << 1 << '+' << 3.2 << " = " << 1 + 3.2;
    puts(oss.str().c_str());
}
```

A few things to note about this program:

* There is (deliberately) no call to `cout`, but the syntax to write to the output string stream will be familiar.

* The member function `precision()` and manipulator `fixed` are used to tune the formatting; these are explained further soon.

* The *chained method call* `oss.str().c_str()` is used to avoid explicitly defining a `std::string` variable (recall that `c_str()` is the method on a `std::string` object, in this case the return value from `str()`, which returns a zero-terminated C-string.)

In the case of a function whose purpose is to define a `std::ostringstream`, the resulting `std::string` from its `str()` member function whould usually be the return type of the function. Don't be tempted to write a `std::ostringstream` to `cout` directly; the correct form would be: `cout << oss.str();`.

Input string stream functionality is encapsulated in the `std::istringstream` class. An object is constructed from a `std::string`, which may have been read using `getline()` (or similar) from either user input or a file. This is then proccessed using the stream extraction operator, reading values into previously defined variables, until the member function `eof()` returns `true`. The following program demonstrates use of an input string stream, however it doesn't actually perform the calculation:

```cpp
// 08-stringstream2.cpp : validate input to calculator function

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string s;
    double a, b;
    char op;
    for (;;) {
        cout << "Please enter a calculation to perform (Number Operator Number):\n";
        getline(cin, s);
        if (s.empty()) {
            break;
        }
        istringstream iss{s};
        iss >> a >> op >> b;
        if (iss.fail() || !iss.eof()) {
            cout << "Bad input!\n";
        }
        else {
            cout << "Input read successfully.\n";
        }
    }
}
```

A few things to note about this program:

* Whitespace is handled as if reading from `cin` (it **is** present in `s` but is **not** read from `iss`.)

* Entering a letter instead of a number (for example) causes `fail()` to return `true`.

* Extra input at the end of the line causes `eof()` to return `false`, and flag a "Bad input" error.

**Experiment:**

* Write a program which creates a times-table in the form: `1 x n = ` up to `12 x n =` writing each line to a `std::ostringstream`. Try to find a way to line up the multiplication signs correctly, and output the resulting `std::string` to both the console and a disk-file.

* Modify the calculator program in `08-calc.cpp` to validate its input using a `std::istringstream`.

## Manipulators and flags

So far we have encountered `noskipws` which is a *stream manipulator* that works on input streams. The exact details of how this, and other, manipulators work is unimportant for the purposes of using them, however in general they are put to the stream object with either `<<` or `>>`. *Stream flags* can also be explicitly set or cleared using the member functions `setf()` and `unsetf()`, and *stream parameters* can be set using named member functions such as `width()` and `precision()`.

Getting formatted output to "look right" is quite tricky and relies to a great extent on trial-and-error combined with (tedious) manual checking of program's output. For some performance-critical code, using C++ streams and manipulators may not be practical or desirable. Also, providing localization (*l10n*) to the user's language and other settings can be difficult when using interleaved manipulators and messages. For these reasons, considering use of the `print()` and `format()` family in preference is recommended.

The following program produces a simulated cash-till receipt formatted to a width of 20 characters. This program is longer than most of the ones we've seen, and uses `struct` and `std::vector` introduced in previous Chapters. All of the text formatting functionality is in the `main()` program, so try and run the program and compare its output with the multiple uses of `cout` in the code (note that any product descriptions inputted may not contain spaces):

```cpp
// 08-receipt.cpp : output a till-receipt from user input

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Entry {
    string product;
    size_t quantity;
    double unit_price;
    inline static double total{};
};

Entry add_entry(const string& input) {
    Entry e;
    istringstream iss{ input };
    iss >> e.product >> e.quantity >> e.unit_price;
    if (iss.fail()) {
        cerr << "Bad entry.\n";
        e.quantity = 0;
    }
    else {
        Entry::total += e.quantity * e.unit_price;
    }
    return e;
}

int main() {
    vector<Entry> sales;
    cout << "Please enter: PRODUCT QTY PRICE (eg. \'Apple 6 0.50\')\n";
    string s;
    getline(cin, s);
    while(!s.empty()) {
        sales.emplace_back(add_entry(s));
        cout << "Please enter: PRODUCT QTY PRICE (blank line to finish)\n";
        getline(cin, s);
    }

    cout << "====================\n";
    auto f = cout.flags();
    auto p = cout.precision(2);
    cout.setf(ios_base::fixed, ios_base::floatfield);
    for (const auto& line : sales) {
        if (line.quantity) {
            cout.setf(ios_base::left, ios_base::adjustfield);
            cout.width(11);
            cout << line.product;
            cout.unsetf(ios_base::adjustfield);
            cout.width(3);
            cout << line.quantity;
            cout.width(6);
            cout << line.unit_price << '\n';
        }
    }
    cout << "====================\n";
    cout << "Total:";
    cout.width(14);
    cout << Entry::total << '\n';
    cout.flags(f);
    cout.precision(p);
}
```

A few things to note about this program:

* A `struct Entry` has three fields `product`, `quantity` and `unit_price` as well as a `static` variable `total`. The `static` variable `total` is declared `inline` so that it can both have a non-`const` value and not need to be defined outside of the `struct` (recall that `struct` and `class` definitions can often be found in headers, and that the ODR must not be violated.)

* The *factory function* `add_entry()` makes an `Entry` object from a `std::string` using a `std::istringstream`. In case of error, the `quantity` field is set to zero, meaning that the `total` is unchanged. The parameter is passed as `const std::string&` in order to save the overhead of copying a `std::string` object.

* The return value of this function is appended to the `vector` of `Entry`s called `sales`; `emplace_back()` is used because the `Entry` is a temporary (as opposed to a named variable). Your compliler should support Return-Value Optimization (RVO) and move semantics meaning that a copy operation should not be needed.

* When a blank line is entered program flow moves on to the part of `main()` which formats the input data into a receipt. The current state of (all of) `cout`'s formatting flags are read into the variable `f`, and the floating-point precision into `p` while setting it to `2`. These variables are stored because changing `cout` has a global effect, so it is good practice for a part of a program which modifies them to always restore their previous values.

* Before the range-for loop `cout.precision(2)` sets the number of digits for floating-point numbers, while `cout.setf(ios_base::fixed | ios_base::left)` sets the default formatting of all fields to both left-aligned and exactly two digits after the floating point. See the table below for a complete list.

* Inside the loop `cout.width()` is used to set the field width of (only) the immediately following field, while `cout.setf(ios_base::right)` sets right-aligment and `cout.unsetf(ios_base::right)` resets this.

**Experiment:**

* Add a `static` member variable `lines` of type `size_t` to `struct Entry` in order to keep a tally of the total number of lines sold, and print this out with the total.

* Remove the need for the two `static` member variables. Is this an improvement to the code or not?

* Output the prices with your regional currency symbol (or `$`), while keeping the formatting width the same. (Hint: this is slightly more complicated than it may at first seem; for example you need to find a way to treat `$1.99` as a single entity to be right-aligned.)

There are quite a lot of stream formatting flags and parameters available, most of which have an equivalent stream manipulator. All of these modify the state of the stream for all subsequent output, with the exception of member function `width()` and stream manipulator `setw()`, which only modify the immediately following output field. This table is intended to be a reference to the more common member functions, flags and manipulators; the best way to learn about formatting variants is to write (small) test programs and observe their output.

|          Manipulator              |                            Member function                                 |                     Action                     |
|:---------------------------------:|:--------------------------------------------------------------------------:|:----------------------------------------------:|
|           s<<setbase(b)           |                                     n/a                                    |            Output integers in base b           |
|           s<<setfill(c)           |                                  s.fill(c)                                 |      Use c as fill character when padding      |
|         s<<setprecision(p)        |                               s.precision(p)                               |    Set default precision for floating-point    |
|             s<<setw(n)            |                                 s.width(n)                                 |       Set pad width for next output field      |
|            s<<showbase            |                         s.setf(ios_base::showbase)                         |      Prefix octal numbers with '0' and...      |
|           s<<noshowbase           |                        s.unsetf(ios_base::showbase)                        |        ...hexadecimal numbers with '0x'        |
|            s<<showpoint           |                         s.setf(ios_base::showpoint)                        |    Always show decimal point for floats, 12.   |
|           s<<noshowpoint          |                        s.unsetf(ios_base::showpoint)                       |      Never show trailing point for floats      |
|             s<<showpos            |                          s.setf(ios_base::showpos)                         |      Show preceding + for positive numbers     |
|            s<<noshowpos           |                         s.unsetf(ios_base::showpos)                        |             Never show preceding +             |
|            s<<uppercase           |                         s.setf(ios_base::uppercase)                        | Output hex and floats in uppercase, 0XA2 1.2E3 |
|           s<<nouppercase          |                        s.unsetf(ios_base::uppercase)                       | Output hex and floats in lowercase, 0xa2 1.2e3 |
|             s<<unitbuf            |                          s.setf(ios_base::unitbuf)                         |        Flush after each output operation       |
|            s<<nounitbuf           |                         s.unsetf(ios_base::unitbuf)                        |           Use stream default flushing          |
|            s<<internal            |             s.setf(ios_base::internal,<br>ios_base::adjustfield)           |        Pad between sign and numeric value      |
|              s<<left              |               s.setf(ios_base::left,<br>ios_base::adjustfield)             |               Pad after the value              |
|              s<<right             |              s.setf(ios_base::right,<br>ios_base::adjustfield)             |              Pad before the value              |
|               s<<dec              |                s.setf(ios_base::dec,<br>ios_base::basefield)               |           Output integers in decimal           |
|               s<<hex              |                s.setf(ios_base::hex,<br>ios_base::basefield)               |         Output integers in hexadecimal         |
|               s<<oct              |                s.setf(ios_base::oct,<br>ios_base::basefield)               |            Output integers in octal            |
|              s<<fixed             |               s.setf(ios_base::fixed,<br>ios_base::floatfield)             |     Output floating-point values as ddd.dd     |
|           s<<scientific           |            s.setf(ios_base::scientific,<br>ios_base::floatfield)           |    Output floating-point values as d.ddddEdd   |
|            s<<hexfloat            | s.setf(ios_base::fixed\|<br>ios_base::scientific,<br>ios_base::floatfield) |    Use hexadecimal for exponent and mantissa   |
|          s<<defaultfloat          |                       s.unsetf(ios_base::floatfield)                       |  Floating point format depends upon precision  |
|   s<<boolalpha<br> s>>boolalpha   |                         s.setf(ios_base::boolalpha)                        |  Booleans output or input as 'true' or 'false' |
| s<<noboolalpha<br> s>>noboolalpha |                        s.unsetf(ios_base::boolalpha)                       |     Booleans output or input as '1' or '0'     |
|             s>>skipws             |                          s.setf(ios_base::skipws)                          |            Skip preceding whitespace           |
|            s>>noskipws            |                         s.unsetf(ios_base::skipws)                         |           Don't skip input whitespace          |

**Experiment:**

* Change the last program to use manipulators on `cout` instead of member functions. (Hint: You will need `left`, `right`, `fixed`, `setw()` and `setprecision()`, and possibly the header `<iomanip>`.)

## User-defined types and I/O

It is possible, and sometimes desirable, to define how user-defined types are formatted when put to output streams with `<<`. This is done by overloading the global `operator<<`, which, despite appearances, is actually the **name** of the function for which you must write an overload. Sadly, the syntax is ugly, unlike in some other programming languages where you merely provide a `tostring()` method, or similar.

The following program reintroduces the `Point` type and defines an *overloaded* stream output function (overloaded becuase the function already exists with a different second parameter for other built-in and user types):

```cpp
// 08-point1.cpp : a Point class with ostream formatter

#include <iostream>
using namespace std;

struct Point {
    int x{}, y{};
};

ostream& operator<< (ostream& os, const Point& p) {
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}

int main() {
    Point p{ 1, 2 };
    cout << p << '\n';
    cout << Point{ 3, 4 } << '\n';
}
```

A few of things to note about this program:

* Custom stream output functions are often trivial to write, in this case only three significant lines of code. They are **always** global functions.

* The object being output should be passed as a `const`-reference to the stream output function. The function will often need to access the internals of the object, so in the case of a `class` with `private` members the function chould either be a `friend` (see Chapter 9), or rely on getters.

* The return type of `operator<<` is a reference to the (newly modified) `std::ostream` object passed as the first parameter. This is important as it allows chaining of output operations. (If the return type used were `void`, `cout << p;` would be legal but `cout << p << '\n';` would not be.)

**Experiment:**

* Modify this program to output `Pixel`s in the format: `red@(0,0)`, using the version of `Pixel` that derives from `Point`. Hint: you will need to use a `switch` statement, and a `static_cast<const Point&>()` to avoid code duplication.

* Define `operator<<` for `Entry`s and use `cout << line << '\n';` in `main()`'s for-loop in the program `08-receipt.cpp` above.

Less common, but sometimes necessary, is allowing input of user-defined types from input streams using the stream extraction operator. Care must be taken the allow for incorrect or invalid input, setting the stream state to "bad" in this case. Also, the stream flags and parameters should not be modified unless care is taken to reset them (all) before returning the modified `std::istream` object.

The following program reads `Point`s from `cin` in an infinite loop, informing the user whether or not the input was successful. Notice that this user feedback is provided in the **calling** function (in this case `main()`) and not the overloaded `operator>>` function. The second parameter to `operator>>` is **not** declared `const` as it is modified by this function (in order to return its newly read value to the caller function).

```cpp
// 08-point2.cpp : read Points from input stream

#include <iostream>
using namespace std;

struct Point {
    int x{}, y{};
};

istream& operator>> (istream& is, Point& p) {
    char a{}, b{}, c{};
    int px, py;
    is >> a >> px >> b >> py >> c;
    if (is.good()) {
        if (a == '(' && b == ',' && c == ')') {
            p.x = px;
            p.y = py;
        }
        else {
            is.setstate(ios_base::failbit);
        }
    }
    return is;
}

int main() {
    cout << "Please enter Points, in the form \'(2,-3)\'\n";
    Point p;
    while (!cin.eof()) {
        cin >> p;
        if (cin.good()) {
            cout << "Point read successfully!\n";
        }
        else {
            cout << "Error in input!\n";
            cin.clear();
        }
    }
}
```

**Experiment:**

* Try entering multiple points on one line. Does the program work as expected?

* Deliberately enter some invalid data, followed by valid `Point`s. Does error recovery work as expected?

* Modify this program to check each input field as entered and act on any incorrect input. Hint: you will need five successive uses of `is >>`. Does error recovery work in the same way?

* Modify this program to read `Pixel`s.

*All text and program code &copy;2019-2025 Richard Spencer, all rights reserved.*
