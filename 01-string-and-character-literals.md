# String and Character Literals

## Introducing a Modern C++ program

Convention dictates that a first program should output the programmer's cry of "Hello, World!" to the screen, and do no more (or less). This is useful in order to test that the compilation environment is fully functional in terms of executable paths, header files, link libraries etc. The C++ version of this program is shown below:

```cpp
// 01-hellow.cpp : prints a line of text to the console

#include <iostream>
using namespace std;

int main() {
    cout << "Hello, World!" << '\n';
}
```


If you prefer not to cut-and-paste, this source file is included in the zip archive linked from this site.[^1] Having seen what this program does (admittedly not that much), let's explore how it is put togther:

* The first line is a comment; syntax of comments are discussed in more detail later in this Chapter. I've chosen to repeat the filename of the source code file in the comment, and also to summarize the purpose of the program. This summary is intended to be useful to anybody who later reads the code, including possibly the original author!

* Then comes some *boilerplate* code, that is common code that we'll see again in future programs we write. The *include directive* is a command interpreted by the *pre-processor* which pastes the entire contents of the relevant *header file* (and any other files it `#include`s) at that point. These directives are being phased out of Modern C++ in favor of the `import` keyword (which has the potential to speed up compilation times significantly), but it is likely the transition will take years to complete. Both Clang/LLVM and MSVC implement `import` although currently extra command-line switches are needed.

* The next line `using namespace std;` is another directive which makes available all of the elements of the Standard Namespace (abbreviated as `std`) available to the global scope (that is, the scope in which the directive appears). Many experienced programmers would consider this *namespace pollution* bad form, preferring instead to use the *fully qualified names* of the individual components, however I have chosen to use it in all of the the example programs we will see in this Tutorial. The name "Standard" comes from the definition of the C++ Library's classes, functions and other facilities as defined by the ISO Standardization Committee. Programs can use any part of the Standard Library and be expected to compile on any compiler/platform combination without modification.

* Next we have a function definition, which is for the `main()` function; here the *parentheses*, or brackets, indicate an unused (or empty) *parameter list*. Every executable C++ program has to have exactly one `main()` in order for it to be able to be linked into an executable binary, and this is where execution begins when the program is run. (This is almost true since global *objects*, if any, will have their constructor functions called before `main()` is entered.)

* The `int` is the *return type* of `main()`, although specifying `return` within the function body is optional; failing to specify it causes a value of zero (indicating successful completion) to be returned to the calling environment or process as the *system return code*.

* Curly braces `{` and `}` are used to delimit a *block* of code, in this case the *body* of the `main()` function. The convention of putting the opening brace `{` at the end of the line instead of on a line by itself follows the "One True Brace Style" (or *1TBS* for short) popularized for the C programming language. I use it both here and in future example programs because it saves on vertical space, and works better with code-folding modes found in many text editors. Some people feel very strongly about whitespace and formatting conventions in their code; your organization will almost certainly have its own coding standards (which you will have to follow even if you don't agree with them!) I highly recommend the [Clang-Tidy](https://clang.llvm.org/extra/clang-tidy/)[^2] utility, which exists as a plugin to many IDEs and can be used to automatically reformat source code to a pre-defined set of rules.

* The next line, within the body of `main()`, uses the `cout` object from the Standard Library (the name is an abbreviation of "Character Output", and is analogous to C's `stdout`). This is followed by the *stream insertion operator* `<<` and a *string literal* followed by a *character literal* (with an additional stream insertion operator between them). A string literal is delimited by a matching pair of double quotes (`"`) on the same line, and can contain any number of printable and escaped non-printable characters. A character literal is delimited by a matching pair of single quotes (`'`) and contains exactly one printable or escaped non-printable character. To be used **within** any literal, both of these types of quotes need to be *escaped* by preceding them with a backslash (`\`). Certain other codes have to be *escape sequences* as well, with `\n` representing new-line; for a complete list see the table later in this Chapter.

So, you wanted to learn about C++'s *Object-Oriented Programming* (OOP) capabilities? Well, we've already used `cout`, which is a C++ *object*. Maybe you've heard about *Operator Overloading* (OO) too? We've used that too; the `<<` operator is *overloaded* to perform stream output. As we have seen even in this simple program, entities can be *chained* so `cout` can handle more than one entity to be output at once, which is implemented just as in composed arithmetic operations. Maybe you've heard about C++ supporting *generics* through the `template` keyword? You'll be pleased to learn that the Library functions selected to correctly handle output of, firstly, a pointer to a string literal, and secondly, a character literal value, are selected at compile-time (as opposed to run-time) for maximum performance and reliability. Hopefully, it soon becomes apparent that complex capabilities can lead to easily comprehensible client code compared with leaner ("simpler") programming languages, such as C.

**Experiment:**

* Adapt the above program (perhaps calling the modified version `01-hellow2.cpp`) to print the new-line character from within the string literal, removing the character literal and the now unneeded second stream insertion operator from the code. Is the output identical?

* Now go back and change `\n` to `endl`. Does the program produce the same output? Is there still a need for a semi-colon at the end of the line?

* Now modify the program to print `Hello` using only *character* literals. Can you get this to compile first time, without making a typo? (Hint: syntax highlighting will help you a lot.)

* Move the using-directive in the original program to within `main()`, and make sure the program still compiles. Does its position within `main()` matter?

* Now use a using-statement `using std::cout;` *instead* of `using namespace std;`. Are there any other changes you need to make to the code?

* Change all occurrences of `cout` to `cerr` and rerun the program. Can you find any difference in how the program performs? (Hint: `cerr` is the error logging stream and is unbuffered, unlike `cout`; try using shell redirection commands eg. `01-hellow > output.txt` under Windows, `./01-hellow > output.txt` under Linux/MacOS.)

* Finally, go back to the version using `cout` and try omitting any `using` statement at all, and prefix `cout` with `std::`. Check this code compiles, and then consider whether you prefer this use of *fully qualified* Standard Library entities. Personally I feel that for new C++ programmers, fully qualified names in code look too similar to each other, making it harder to learn to recognize the individual names as different.

## Special characters

Some characters cannot be easily entered into string or character literals within code, this may be because they are ASCII *control* characters (also known as non-printable, in the range 0-31) or *top-bit-set* characters (in the range 128-255) not available on your keyboard, or because they have special meaning. Some of the more common control and other special characters have single-letter short forms; we've already encountered `\n` for new-line; the others are listed in the table below. Note: a backslash followed by an *octal* (base 8) number up to three digits (between `\0` or `\377`) can be used for any character in the range 0-255 (decimal), as can a backslash followed by `x` and one or two *hexadecimal* (base 16) digits (such as `\xa` or `\xA3`) up to `\xFF`.

| Escape sequence |     Description    |
|:---------------:|:------------------:|
|       \\n       |       newline      |
|       \\t       |   horizontal tab   |
|       \\v       |    vertical tab    |
|       \\b       |      backspace     |
|       \\r       |   carriage return  |
|       \\f       |      form feed     |
|       \\a       |    alert (bell)    |
|       \\\\      |      backslash     |
|       \\?       |    question mark   |
|       \\'       |    single quote    |
|       \\"       |    double quote    |
|      \\ooo      |    octal (0-377)   |
|      \\xhh      | hexadecimal (0-ff) |
|     \\uhhhh     | Unicode sequence (0-ffff) * |
|   \\Uhhhhhhhh   | Unicode sequence (0-10ffff) * |

&#42; Note: not all Unicode sequences are allowed in 8-bit string or character literals, however these escape sequences are more useful with *Unicode string literals*, explained later in this Chapter.

Any escape sequence can be used within single quotes to represent exactly one character literal (including zero `'\0'`). Zero has a special meaning, as it is the string literal termination character. C++ inherits its string literals from C, and C-strings (as they are sometimes known, and as referred to in this Tutorial) were a bit of an afterthought to the C language of the 1970s. String literals can be thought of as a **read-only** array of characters with an automatically added zero terminator; the space needed to store the string literal `"Hello"` is six bytes, and not five as might be assumed.

When outputting a string literal via `cout`, the zero byte, or *null terminator*, is not outputted, but must be present to stop further raw memory being seen to be part of the string. Other terms you may encounter for string literal are *NTMBS* (null-terminated multi-byte string), `zstring` (a common *typedef* to implement the type of zero-terminated string), and `czstring` (`const`ant zero-terminated string, which is immutable as it is stored read-only).

It is an oversimplification to say that any valid character can fit into a character literal; a character literal is simply a 8-bit type (possibly signed or unsigned) called `char` (pronounced "car", at least in the US) and this can thus hold one of 256 possible values. Historically, the first 128 characters of *ASCII* (American Standard Code for Information Interchange) were the same on any platform (this was also known as 7-bit ASCII, or more recently UTF-7), while the second 128 ("top-bit-set") characters could change according to the specification of the chosen *code page* (also known as *extended ASCII*). With the advent and near-universal adoption of UTF-8 (Unicode encoded in an eight-bit octet stream), all top-bit-set characters begin a two-, three- or four-character sequence, which also all have their top bits set.

The good news is that despite the complexity of implementation of UTF-8, if your editor is set to edit text in UTF-8 (optionally with an identifying *magic number* BOM at the start) and your shell uses a UTF-8 *locale*, then your programs should output code to the console exactly as you type it into your editor. To repeat: string literals containing raw UTF-8 sequences entered into string literals within the code should display correctly in the console when the program is run. (On Windows it may be necessary to enter `chcp 65001` at the shell prompt once for every shell session before running your program; this will change the code page to UTF-8, instead of the most likely default Windows-1252, which is an eight-bit encoding. Alternatively, you may wish to use UTF-16 in your editor and *wide character* literals and streams, see later in this Chapter.)

**Experiment:**

* Modify `01-hellow.cpp` to output each word on a new line indented by one tab-stop, using only one string literal.

* Modify the part reading `Hello,` to `Hello\0`, and run the program. Are you surprised by this change?

* Now go back to the original `01-hellow.cpp` and try outputting the character literal `\0` at the end instead of `\n`. What do you discover?

* Now try to create a program that can output: `$(USD) £(GBP) €(EUR)` Hint: The Dollar symbol should be on your keyboard, and the Pound and Euro symbols may well be too, but if not use a character picker such as Character Map and a UTF-8 encoding in your editor (and on the console, remember `chcp 65001` for Windows).

* Use Character Map (or similar) to enter a pi symbol into your text editor, and make the program output: `π has the value 3.14159...`

## Raw string literals

String literals are interpreted at compile time and any escape sequences are translated then. The resultant *raw string* is then stored in read-only memory, and the running program uses a pointer to the first character. This pointer is in fact a variable (as opposed being a constant) however the string data itself is constant and attempting to change it (for example through subscript assignment) is a compile time error. With these facts in mind, try to predict the output from changing the `cout` operation in `01-hellow.cpp` to: `cout << "Hello, World!\n" + 7;` Surprised? (Some compilers warn about shifting a pointer with "pointer arithmetic" in this way.)

Now consider the usefulness of being able to insert whitespace (particularly tabs and newlines) and unescaped backslashes (particularly in regular expressions, or "regexes") into string literals *without* the need for escape characters. Such an entity is called a *raw string literal*, and takes the format: `R"(a \raw\ string literal)"`

The start of a raw string literal is a capital letter "R" followed by a double quote and opening regular parenthesis, none of which form part of the stored or output string. A raw string literal is ended with a closing regular parenthesis and double quote. In the (unlikely) event that a raw string literal is required to *contain* a closing parenthesis followed by a double quote, this can be achieved by putting a unique sequence (often a word, or one or more asterisks) betweeen the double quote and parenthesis *at both ends*, for example: `R"*(can contain )" here)*"`

*Pointer arithmetic* combined with raw string literals can serve a useful purpose, as shown in this next example program `01-title.cpp`:

```cpp
// 01-title.cpp : output the title page of a well-known book

#include <iostream>
using namespace std;

int main() {
    cout << 1+R"(
                   Alice's
                Adventures In
                 Wonderland

                     by
                LEWIS CARROLL
)";
}
```

Compile and run this program following the same process as before. Notice that the `1+R"(` *idiom* omits a blank line before the output, thus the first line output is the correct number of spaces followed by `Alice's`. Using a raw string literal means we don't have to litter the output string with escape characters for new lines, and can begin the output **unindented** as the `1+R"(` skips the first character, which is (intentionally) a new line in the source file. The raw string literal is in this case (again intentionally) terminated at the start of a blank line, separate from the indentation of `cout` within `main()`; this is preferable to including "invisible" trailing whitespace in the output string.

**Experiment:**

* Change the program above to output the first stanza from the rhyme at the beginning of the same book (shown below), indenting **even-numbered** lines by eight spaces.

```
All in the golden afternoon
Full leisurely we glide;
For both our oars, with little skill,
By little arms are plied,
While little hands make vain pretence
Our wanderings to guide.
```

* Now use a (non-raw) string literal for each line and a single call to `cout` with suitable escape characters. What happens if you remove all of the stream insertion operators *except* for the first? (Explanation: adjacent string literal concatenation is automatically performed by the pre-processor.)

* Modify `01-title.cpp` to output the title of your favorite book or film centered on the console window (assume an 80 character fixed width, and change the size of the console window if different).

## Wide characters

Although very popular, and supported in most modern programming languages, UTF-8 encoded string literals are not the only way to manipulate and display characters outside the range of seven or eight-bit ASCII. We've discussed `char` as being the *underlying type* of string and character literals in C++, and there is also the `wchar_t` (possibly pronounced "dub-car-tee") type associated with *wide character* stream objects and strings (the names of which also start with "w") and these predate Unicode support in the C++ Standard Library. Wide character support is platform-specific, in particular the size of `wchar_t` in bits is not standardized; on many systems it is 32 bits but on Microsoft Windows it is 16 bits (and encodes Unicode UTF-16). If you think you need to use wide character support, and want to find out if it is suitable for your needs, consult your platform's documentation.

As well as the eight-bit type `char` there is now also `char8_t` which is useful for explicitly specifying that a string is UTF-8, and usefully can encode all UTF-8 code points when using `\u` and `\U`, unlike plain `char`. It also removes the uncertainty of whether `char` is signed or unsigned, which can cause programs to work differently on different platforms in some cases. Also available are `char16_t` and `char32_t` designed to be the correct size for holding a single UTF-16 or UTF-32 Unicode code point, respectively. Whilst these types are built into the language, converting strings between these types is a complex task and requires use of either the Standard Library, or third-party libraries (such as ICU[^3]), further discussion of which is beyond the scope of this Tutorial.

The following table lists C++ types, sizes, target encodings, literals and objects used with normal and wide character sets:

|   Type   |  Bits | Encoding | String Literal | Character Literal | Raw String Literal | String Type | Stream Output |
|:--------:|:-----:|:--------:|:--------------:|:-----------------:|:------------------:|:-----------:|:-------------:|
|   char   |   8   |   ASCII  |     "abcd"     |        'a'        |      R"(abcd)"     |    string   |      cout     |
|  char8_t |   8   |   UTF-8  |    u8"abcd"    |       u8'a'       |     u8R"(abcd)"    |   u8string  |      cout *   |
| char16_t |   16  |  UTF-16  |     u"abcd"    |        u'a'       |     uR"(abcd)"     |  u16string  |      n/a      |
| char32_t |   32  |  UTF-32  |     U"abcd"    |        U'a'       |     UR"(abcd)"     |  u32string  |      n/a      |
|  wchar_t | 16/32 |   n/a +  |     L"abcd"    |        L'a'       |     LR"(abcd)"     |   wstring   |     wcout     |

&#42; An explicit cast to type `char` in `operator<<` may be required.

&#43; The `wchar_t` encoding and streams under Windows are 16-bit and support UTF-16.

## Code comments

C++ has two types of comments: single line comments which begin anywhere on a line (except inside a quoted string literal) with `//` and continue to the end of the same line, and multi-line comments which are delimited with `/*` at the beginning and `*/` at the end. A variation on this is that multi-line comments can instead have **both** delimiters on the same line, thus only commenting a part of that line.

```cpp
// This is a single line comment, ignored by the compiler.

/* This multi-
   line comment
   is also ignored.
*/

int main( /* this is parsed as empty parentheses */ ) {}
```

Modern C++ code favors the `//` style, with multiple lines of comments possible by started each one with `//`. Temporarily *commenting out* a block of code, thus preventing it from being compiled, can be achieved by putting `/*` at the beginning and `*/` at the end. Nesting multi-line comments is not possible as the comment always ends at the first `*/` reached; single line comments within a multi-line block are fine, however.

Comments are like strings in that they do not contain program code, instead they are written in natural language (usually English) using the same character encoding of the source program file. The content of comments is not formalized, unless you wish to employ a tool such as [Doxygen](https://www.doxygen.nl/manual/docblocks.html)[^4], which generates HTML documentation from source code by reading custom mark-up within comments. Comments within code that comprise paragraphs of text are often formatted to a fixed width, for example 77 characters (the standard for plain text email).

Learning when and how to comment code comes with experience; typically you shouldn't duplicate information that can be inferred from the program code itself. Comments such as "This is correct" aren't particularly helpful either, instead you should try to be relevant and concise, aiming at the ability level of a fellow programmer (or even yourself in the future) who reads your code. When reading other people's code remember the time-honored adage: if code and comments disagree, then both are wrong.

**Experiment:**

* Going back to `01-hellow.cpp` add a single-line comment sequence to the line beginning `cout`. Does this program compile and run?

* Uncomment this line and use a pair of multi-line delimeters to comment out the whole of `main()`. Does this program compile and run?

* Now change the position these delimiters so that no new-line is printed by the line beginning `cout`. (They will necessarily be on the same line.) How does this affect the readability of the code, especially with syntax highlighting enabled in your editor?

[^1]: https://learnmoderncpp.com/2019/08/03/welcome/
[^2]: https://clang.llvm.org/extra/clang-tidy/
[^3]: http://site.icu-project.org/home
[^4]: https://www.doxygen.nl/manual/docblocks.html

*All text and program code &copy;2019-2022 Richard Spencer, all rights reserved.*
