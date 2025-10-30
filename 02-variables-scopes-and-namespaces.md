# Variables, Scopes and Namespaces

## Declarations, definitions and assignment

A variable is a named entity which can hold a value; thus it has *state*. As the name "variable" suggests, this value can, and often does, change during the entity's lifetime. A *declaration* can be thought of as introducing a variable to your program, as if it is saying: "I exist with this name and have such-and-such type, use me." On the other hand, a *definition* is **everything** a declaration is, plus asking: "Please reserve some memory for me here." Additionally, an *assignment* can be combined with a definition, thus stating "I have this initial value from now until (optional) later reassignment (unless I am a constant)." Defining a variable without giving it an initial value is usually best avoided, as the variable will likely contain random garbage (dereferencing an uninitialized variable causes undefined behavior in C++; your compiler can and often will warn of this). Declarations that are not also definitions are rare for variables of the built-in types, so we will omit further discussion of them here.

C++ is a statically typed language, meaning that the type of each variable is known at compile time (importantly, this is also true of variables defined with the keyword `auto`, see later). Due to the fact the types are known and fixed, the amount of memory needed for each variable is known at compile time too; this specific amount of memory is called the variable's *storage class*. (Storage class applies to **all** user-defined types, too.) This fact gives rise to the *One Definition Rule* (ODR) which states that a variable can be declared or assigned to multiple times, but must be defined **exactly** once. This is the key concept concerning memory usage of variables in C++, so remember the ODR. By default, C++ reserves space for new local (function or sub-scope) variables on the *stack*, which means that two variables of the same name can exist in different scopes (one scope enclosing the other); however the *address* of the variable which is always unique. The other place variables can be stored is on the *heap*, which is often preferable for large objects or arrays. Again these variables always have a unique address, but continue to use memory until it is explicitly deallocated, with the responsibility being the programmer's, not the C++ runtime.

The shortest possible name or *identifier* for a variable is a single letter, and these are often the name of choice for variables whose purpose is obvious (such as a loop counter); this convention also provides a symmetry with variable names in Mathematics. Variable names must start with a lower- or uppercase letter or an underscore, followed by an arbitrary number of lower- or uppercase letters, underscores or decimal digits in any order.

Reserved names that should not be used as identifiers are:

* Any of the C++ keywords (of which there are just under a hundred at the time of writing).
* Names beginning with an underscore followed by a capital letter (these are reserved for the Standard Library).
* Names containing adjacent double underscores (reserved for purposes such as name mangling).
* At **global scope** any name beginning with an underscore.

Use of top-bit-set characters (including UTF-8 sequences) **is** permitted in variable names with more recent compilers, including as the initial character; such sequences are also recognized by the preprocessor.

Unlike some programming languages, C++ does not mandate different uses of capital letters and so on for different types of entity, but your organization may well follow conventions such as constants in upper case, user-defined types in sentence case and member functions in camel case. The rules for identifiers are the same for `class`, `struct`, `enum` and `union` names, function names, namespace names and macro names. Different variable naming styles, the use of which may fall under coding standards requirements at your employer, are listed in the following table:

|   Naming Style   |     Example     |
|:----------------:|:---------------:|
|    Lower Case    |  avariablename  |
|   Sentence Case  |  AVariableName  |
|    Upper Case    |  AVARIABLENAME  |
|    Snake Case    | a_variable_name |
| Upper Snake Case | A_VARIABLE_NAME |
|    Camel Case    |  aVariableName  |

New variables are introduced (defined) by providing a type, an identifier and, optionally (but highly recommended) either an initial value after an equals sign (`=`), and/or within or a pair of braces `{` and `}` (which can be empty to assign the default value for the type). Use of equals is historical syntax, while use of braces (where the equals sign becomes optional) is called *uniform initialization* and is discussed on more detail later in this Chapter.

Braces are also used with strings passed to `print()` and `println()` indicating a point in the string where a variable's current value should be substituted. The number of brace pairs must equal the number of additional parameters passed to the functions. (To output a literal `{` or `}` use one of the escape sequences `{{` or `}}` respectively.)

The following program defines three variables but only assigns to two of them initially, despite the fact that it prints them all out twice:

```cpp
// 02-assign.cpp : assign to local variables

#include <print>
using namespace std;

int main() {
    int i = 1, j = 2;
    unsigned k;
    println("(1) i = {}, j = {}, k = {}", i, j, k);
    i = j;
    j = 3;
    k = -1;
    println("(2) i = {}, j = {}, k = {}", i, j, k);
}
```

Running this program produced the output:

```
(1) i = 1, j = 2, k = 16151149
(2) i = 2, j = 3, k = 4294967295
```

There are probably no surprises for the values of `i` and `j` as output the first and second time. Note that the statement `i = j` merely assigns the **current** value of `j` to `i` and does not imply that they point to the same object; the values of `i` and `j` can subsequently change **independently**.

The first time `k` is output its value is essentially random, an example of *undefined behavior* (UB); nothing can be guaranteed about its value other than it is within the valid range for the `unsigned` type. Assigning a negative number to an `unsigned` type is (perhaps surprisingly) legal C++, and if you are unsure of why the second output of `k` is what it is, you may want to do some research into "two's-complement" binary representation of integers (it's actually the number 2<sup>32</sup>-1 represented as a positive integer).

**Experiment**

* Fix this program by giving `k` an initial value. Experiment with positive and negative integers. What do you learn about the `unsigned` type?

* Now unfix it by no longer giving `j` an initial value. How is `i` affected at `(2)`?

* Now fix it again by adding the line: `int j{};` between `int i` and `unsigned k`. What else has to be changed? Is this the ODR manifesting itself?

## Casts and uniform initialization

The following program assigns an integer to a variable `a` of type `int`, and a real number to a variable `b` of type `double`. In case you're wondering, the name for the type of `b` comes from *double precision* as defined in the IEEE Standard for Floating-Point Arithmetic (IEEE 754), which defines how an (accurate) approximation of a real number is stored in 64 bits of memory. Single precision `float` uses 32 bits, and extended precision `long double` typically uses up to 96 bits (the storage class may be different from the number of precision bits used). The initial values of `a` and `b` are then reassigned to each other, meaning the second output line is different:

```cpp
// 02-swap.cpp : attempt to swap the values of an int and a double

#include <print>
using namespace std;

int main() {
    int a = 1;
    double b = 2.5;
    println("(1) a = {}, b = {}", a, b);
    a = 2.5;
    b = 1;
    println("(2) a = {}, b = {}", a, b);
}
```

Running this program produces the output:

```
(1) a = 1, b = 2.5
(2) a = 2, b = 1
```

The variable assignment statement `a = 2.5` is called a *narrowing cast* because of the reduction in precision and likelihood of information being lost. In this case the value is **automatically** *truncated* from `2.5` to `2`, as the decimal part cannot be represented in an `int`. Even though the term being assigned is floating-point (actually it's a double-precision literal, see later in this Chapter) the type of `a` **remains** as `int` (and this is why the fractional part is lost). In contrast, the statement `b = 1` is a *widening cast* with the assumption that there is no chance of information being lost; `b` remains of type `double` holding an integer value (which could be represented explictly as a literal `1.0`). Both of these casts are *implicit casts* becuase the compiler makes them happen automatically; the instruction to carry out the type casting is implicit. (We could have used a more verbose `static_cast<int>(2.5)` and `static_cast<double>(1)` to make the casts explicit, we'll see this later.)

**Experiment**

* Modify this program so that no narrowing casts occur.

* Now modify this program again to produce only integer outputs.

* Again, modify the original program to use `static_cast`. (Hint: don't worry if you don't fully understand the syntax yet.)

Implicit casts can happen with variable initialization-and-assignment too, however this is not always the behavior we want. To force the compiler to disallow (possibly unintentional) narrowing casts we can use *uniform initialization* which involves enclosing the assigned value in curly braces:

```cpp
// 02-uniform.cpp : avoid compiler error with uniform initialization and explicit narrowing cast

#include <print>
using namespace std;

int main() {
    // int c = { 2.5 };                 // Error: this does NOT compile
    int c = { static_cast<int>(2.5) };  // while this does
    double d = { 1 };                   // and so does this
    println("c = {}, d = {}", c, d);
}
```

It is important not to confuse a single value in curly braces with an initializer list containing one element when reading code like this; in practice here there is no ambiguity because if we had wanted to initialize an array of `int` a single element list we would have written `int c[] = {2.5,};` using a trailing comma inside the braces. Interestingly, the equals sign in uniform initialization is in fact **optional**, so we could have written `int c{2.5}` and `double d{1}`. Uniform initialization appears elsewhere in C++ so it is a good idea to become familiar with the syntax early on, and know the nuances of its behavior compared to using a time-honored C-style equals sign instead. In Modern C++, uniform initialization is probably considered better style, where you have the choice of the two.

**Experiment**

* Change `int c` to `float c` in the above code. Does this fix the problem? Are you surprised by this?

* Fix the code so that it compiles with `float c` (read on if not sure, and think "float literal").

* Now change `{1}` to `{1LL}`. Does the code still compile? Try to fix this.

## Numeric types and type inference

C++ has quite a lot of built-in types, most of them inherited from the C language; so far we've met `char`, `int`, `unsigned`, `float`  and `double`. On most platforms, integer types can be 8, 16, 32 or 64 bits *wide* in signed and unsigned types, while floating point types of 32, 64 and 96 bits wide are usually available. The table below lists many of the built-in types in C++ together with their typical properties (on most modern machines) and *numeric literal* forms:

|        Type        | Typical Bits |     Minimum Value    |     Maximum Value    |      Example Literal           |
|:------------------:|:------------:|:--------------------:|:--------------------:|:------------------------------:|
|     signed char    |       8      |         -128         |          127         |           '\x20'               |
|    unsigned char   |       8      |           0          |          255         |           '\xa0'               |
|        short       |      16      |        -32768        |         32767        |      n/a (as for int)          |
|   unsigned short   |      16      |           0          |         65535        |   n/a (as for unsigned)        |
|         int        |      32      |      -2147483648     |      2147483647      |       -1000, 0x7fff            |
|      unsigned      |      32      |           0          |      4294967295      |       1000U, 0xffffU           |
|        long        |   64 (32) +  |      -2147483648     |      2147483647      |      1L, 0x7fffffffL           |
|    unsigned long   |   64 (32) +  |           0          |      4294967295      |    10000000UL, 0xbbbfUL        |
|      long long     |      64 +    | -9223372036854775808 |  9223372036854775807 | -10000LL, 0x80000000000LL      |
| unsigned long long |      64 +    |           0          | 18446744073709551615 | 10000ULL, 0x7fffffffffULL      |
|      ssize_t       |   64 (32)    | -9223372036854775808 |  9223372036854775807 |              0Z *              |
|       size_t       |   64 (32)    |           0          | 18446744073709551615 |             0UZ *              |
|        float       |      32      |      1.17549e-38     |      3.40282e+38     |       0.f, 3.2e-10f            |
|       double       |      64      |     2.22507e-308     |     1.79769e+308     |      2.3, 1.2345e200           |
|     long double    |     128      |     3.3621e-4932     |     1.18973e+4932    |  100000000.5L, 0.0000345L      |

&#42; The "size types" `std::size_t` (unsigned) and `std::ssize_t` (signed) are from the Standard Library, and so require a header which defines them, such as `<cstddef>`. (Negative values for `std::ssize_t` are typically used to represent error values.)

&#43; On 32-bit machines `long`, `unsigned long`, `ssize_t` and `size_t` are usually 32 bits, and are usually 64 bits on 64-bit machines, while `long long` and `unsigned long long` are guaranteed to be (at least) 64 bits on all platforms.

The variable definition `double n{2.3};` should by now appear familiar and correct; it assigns a floating-point number (actually as shown in the table, a numeric literal) to a double precision variable. In other words it's an exact match between the declared type and the literal type. (If it were a narrowing cast, such as `double n{2.3L}` we would expect compilation to fail.)

The `auto` type specifier has a specific meaning in Modern C++: deduce the type of the variable being assigned **to** from the value, variable or expression being assigned **from**. This means, however, that the variable definition must also *always be an assignment* as uninitialized `auto` variables are not allowed. The reason for this is simple: C++ variables must have their type known at compile time, and this is no different for `auto` variables. I'll repeat this as it is so important; *C++ is a statically typed language, and every available use of* `auto` *does not change this*.

Some example usage of `auto` is shown here:

```cpp
int i = 1;     // both i and 1 are of type int
auto j = i;    // j is also of type int
auto k{ 1.0 }; // k has type double (using uniform initialization syntax)
auto q;        // Error: will not compile
```

Program can be (re-)written without any use of `auto`, however you will often encounter it in modern code so you need to be able to recognize and understand its meaning. It is especially useful where the type in question is overly verbose, such as when using types related to generic classes. Notice from the example shown here the use of uniform initialization syntax with `auto`-assignment for the variable `k`; this usage can be expected to become more common.

## Bool and byte

The boolean type can hold one of exactly two values: `true` and `false`; these map directly to `int` values of `1` and `0` respectively. (Note: **not** `-1`.) A variable defined as `bool` can be used to hold the result of a conditional expression (we'll meet conditions in the next Chapter).

```cpp
bool success{ true };
bool are_equal = (a == b);
```

The `byte` type, often referred to as `std::byte` as it is a type made available from within the Standard Library namespace (in order to avoid name clashes with existing code), designed to replace `unsigned char` where the variable (or array) contains (8-bit) binary data.

This type is actually implemented as an `enum class` (see Chapter 6) and only the bitwise operators are supported, so addition or subtraction of `byte` values is not allowed. A variable of type `byte` can be initialized with any value from `0` to `255` and converted back to an integer value with the function `to_integer()` (functions are covered in Chapter 4).

```cpp
std::byte b{ 254 };
auto i = std::to_integer<int>(b); // This is ugly but is shown here for reference
                                  // You can compare it with static_cast<T>()
```

## Literal prefixes and suffixes

Digits can be grouped, for example into groups of three for decimal numbers, using apostrophe (`'`) as the delimiter:

```cpp
auto million = 1'000'000;
```

This syntax is **only** for numeric literals embedded within code, not for numbers read from the keyboard or a file using stream input.

If some of the example literals in the last table look unfamiliar then the following two tables should help explain. Prefixes can be applied which specify the number base of the literal; `0` and `0b`/`0B` are for **integer** types only:

| Prefix |     Base    |
|:------:|:-----------:|
| 0b, 0B |    Binary   |
|    0   |    Octal    |
| 0x, 0X | Hexadecimal |

(Note: hexadecimal floating-point literals use `P` or `p` as the radix separator, while decimal floating point literals use an `E` or `e` to separate the exponent from the mantissa.)

Suffixes can apply to either integer or floating point literals (or to both in the case of `L`). Also, `U` and `u` can be combined with `L`, `l`, `LL`, `ll`, `Z` and `z`.

| Suffix |                  Meaning                 |        Usage       |
|:------:|:----------------------------------------:|:------------------:|
|  f, F  |          single-precision float          |    3.3f, -0.0123F  |
|  l, L  | extended precision float OR long integer |   100'000l, 3.3L   |
|  u, U  |             unsigned integer             |     65536u, -1U    |
| ll, LL |        long long integer (64 bits)       | 0ll, -1'234'567LL  |
| uz, UZ |    unsigned size type (std::size_t)      | 0uz, 4'294'967'296UZ |
|  z, Z  |      signed size type (std::ssize_t)     | 0z, -2'147'483'648Z |

Note there is no literal for `short int` and there is unlikely to ever be one, as the `s` suffix is used for seconds when using the `<chrono>` header (and `string` when used with the `<string>` header). Also, the integer literal suffixes don't ever actually need to be used in Modern C++, source-code literals in all bases are automatically *promoted* (widened) to a type that can hold the value of the literal.

To enable all the literal suffixes in the Standard Library after referencing the necessary header(s) use:

```cpp
using namespace std::literals;  // This is also implied by "using namespace std;"
```

Note: this is **not** necessary for suffixes of the built-in types, being `F`, `f`, `U`, `u`, `L`, `l`, `LL` and `ll`.

**Experiment**

* Make up some variable assignments from various literals. Use `auto`, and output the variables using `print()`. See if the output is what you expected.

* Now specify the correct built-in type instead of `auto`, such as `long long`. Check the tables above if you're not sure, and use uniform initialization. Try to avoid always using the biggest types `long long` and `long double` regardless of the value or calculation, as this may not be optimal in terms of memory footprint and performance.

## Local and global scopes

Variables defined outside of any function scope are called *global* variables, while those defined within functions (including `main()`) are called *local* variables. Global variables have memory reserved for them and are initialized before `main()` is entered, although the order in which they are initialized is **not** guaranteed across multiple translation units (these being approximately C++ source files, discussed later in this Chapter). Local variables have space reserved for their contents from the function stack when the function is entered, and are available for use after program flow reaches their definition within the function.

A local variable with the same name as a previously defined global variable temporarily takes precedence over, or *shadows*, the global variable until it goes *out of scope*. Variables defined within a function go out of scope at the end of the function, and the space reserved for them is then released.

It is also possible to nest scopes within functions up to an arbitrary level. The delimiters `{` and `}` are used for this purpose, mirroring their use to introduce a function scope. Code within *sub-scopes* is typically written indented to an extra level. (Sub-scopes which can contain scoped variable definitions are also introduced by a variety of C++ keywords including `if` and `while`.) Variable names which are re-defined within sub-scopes lose visibility at the closing brace and can no longer be referenced (the memory they use may not be released until the function exits, however).

The following program defines and initializes the variable `a` three times. This does not violate the One Definition Rule (ODR) because of one simple fact: *the three variables exist in different scopes*.

```cpp
// 02-scopes.cpp : define three variables with the same name in one program

#include <print>
using namespace std;

auto a{ 1.5f };

int main() {
    println("(1) {}", a);
    auto a{ 2u };
    println("(2) {}", a);
    {
        auto a{ 2.5 };
        println("(3) {}", a);
    }
}
```

Running this program produces the output:

```
(1) 1.5
(2) 2
(3) 2.5
```

**Experiment**

* Change the assignments to 1, 2, and 3 (using integer literals with `int` instead of `auto`). Does this still satisfy the ODR?

* Add `println("(4) {}", a);` between the two closing curly braces, just before `main()` exits. Is the output what you expected?

* Change the output command `, a)` to `, ::a)` in each of the three times it appears in the program. What appears to happen? (Explanation: the global scope resolution operator `::` selects the global `a` over any other `a` that may be visible.)

## Static and thread-local variables

Any global variables defined in the program are visible throughout the whole of the program, which unfortunately means that name clashes are possible in different and unrelated portions of code. The traditional way of getting round this problem, inherited from C, was to use the `static` keyword. All this does in the context of a global variable definition is make the variable local to the *translation unit*, which is the proper name for the each C++ source file with all the headers it `#include`s (which compiles to a single `.obj` or `.o` object file). The term *file static* can also be used to describe the visibility of such a variable, referring to the `.cpp` file it is defined in. Thus two `.obj` or `.o` files each with one or more `static` variables of the same name can be linked to form an executable, without generating linker errors.

```
static int i = 1000; // only visible within this translation unit
```

The `thread_local` keyword (added in C++11) can optionally be used at global scope and specifies a variable with global visibility which is created (and optionally initialized) when a new thread is launched:

```
thread_local size_t my_counter{ 0 }; // different variable initialized for each new thread
```

Further discussion of multi-threaded coding is beyond the scope of this Tutorial, but you should be aware that global `thread_local` variables may add semi-hidden *time-and-space* costs (lower run-time efficiency in CPU time and increased memory usage) to threaded programs because of the extra initialization that has to be performed whenever a new thread is launched.

The keywords `static` and `thread_local` have uses in other contexts too, as we will discover later (`static` local and class variables and `thread_local` variables in functions). A variable can also be both file `static` and `thread_local`.

**Experiment**

* Create two different `.cpp` files with the above definition of `i`, except using different assigned values. Can they be compiled and linked together with a third file containing a `main()` function? Which, if any, value of `i` can `main()` reference?

* Remove the `static` keyword from both files defining global `i`. What error message do you get trying to link all three files together?

* Now add the `static` keyword back to just one of the `.cpp` files defining `i`. Does the program now compile, and if so which `i` is output?

## Namespaces

The purpose of namespaces is to solve the problem of global names clashing with each other. (We have already encountered the `std` namespace which contains all of the Standard Library components.) Namespaces can only be introduced at global scope and are delimited with the by now familiar `{` and `}`. Namespaces **can** exist inside other namespaces, with the scope resolution operator `::` also used to separate nested namespace names. Entities (such as variables, functions and classes) defined within namespaces are still globally visible, and can be either made available with `using` statements or directives, or referenced using their *fully qualified names*.

The next program defines two global variables, each in different namespaces, which means they can exist in the same `.cpp` file. Notice that the namespace names have been written in sentence case with the variable names in snake case, both common conventions:

```cpp
// 02-height.cpp : define the same variable name in two different namespaces

#include <print>
using namespace std;

namespace Wonderland {
    auto alice_height_m{ 0.15 };
}

namespace VictorianEngland {
    auto alice_height_m{ 0.9 };
}

int main() {
    println("Alice\'s height varies between {}m and {}m",
        Wonderland::alice_height_m,
        VictorianEngland::alice_height_m);
}
```

**Experiment**

* Add the statement `using namespace VictorianEngland;` as the first line of `main()`. Does this change the output in any way?

* Now remove `VictorianEngland::` from the output call. Does the output change now? What do you learn about the connection between `using` directives and unqualified names?

Namespaces are *open*, that is elements can be added to a namespace from different parts of a program, even from different `.cpp` files. (This means it is technically possible to add to the `std` namespace, but doing so is strongly discouraged as it can create misleading code that may mysteriously fail to compile on other systems or platforms.)

Namespaces can be nested in two ways: by either using multiple `namespace` keywords, or using the scope resolution operator, as shown in the code fragments below:

```cpp
namespace Wonderland {
namespace Animals {
auto white_rabbit{ 1 };
}
}

namespace Wonderland::Animals {
auto mouse{ 2 };
}
```

The fully qualified names of both variables defined are very similar, they are: `Wonderland::Animals::white_rabbit` and `Wonderland::Animals::mouse`. Notice that the definitions within the `namespace` keywords have **not** been indented; this is common practice because of the nature of the code (functions and class definitions) that can often appear within namespaces, which reads better unindented.

Another feature of namespaces is the curiously named *unnamed namespace*. The syntax is simple, a `namespace` keyword followed immediately by `{`. The purpose of the unnamed namespace is to replace the use of `static` in definition of global names visible to just the current translation unit. The following code fragment defines and assigns a variable whose fully qualified name in the same translation unit is just `i`, and is not visible in any other.

```cpp
namespace {
int i = 3000;    // variable i is only visible later within this file
}
```

**Experiment**

* Create a program that uses the above fragment to output the value of `i` from within `main()`

* Now move `main()` to a separate file. Does the program still compile? What if there were more than one translation unit containing an unnamed namespace?

## Constants and references

Constants are named entities that have only one value during their lifetime, in other words their initial value remains unchanged. (I avoid the use of the word "variable" here, or worse still "`const` variable", to avoid confusion, but most of the rules of variables apply to constants too.) Constants are useful in many places in Modern C++ programs, and in some places they can be used where variables cannot, such as when specifying array sizes and template parameters. Similarly to `auto` variable definitions, constants **must** have their value specified when they are defined.

Constants are defined using the `const` keyword, **either** before or after the mandatory type specifier (or `auto`), as shown in the program below which defines a global constant and a local constant:

```cpp
// 02-constants.cpp : introducing the const keyword

#include <print>
using namespace std;

const double PI = 3.14159265358979;

int main() {
    auto const APPROX_E = 3;
    println("pi is almost exactly {}, while e is approximately {}",
        PI, APPROX_E);
}
```

Notice that the named constants have been specified using upper case, which is a common convention.

**Experiment**

* Try to re-assign to `PI` within `main()`. What error do you get?

* Try to output the result of adding the two constants together. Is this what you would expect for two variables of different types (implied in the case of `APPROX_E`)?

Constants can be assigned to a variable, and created from a variable at the point it is defined. Interestingly this implies that the value of a C++ constant *is not necessarily known* at compile-time; not all constants therefore can be used as array sizes, for example. (If a constant compile-time value is needed for this purpose, your compiler will refuse to compile such code.) Variables of many types can usefully be declared `const` where their value shouldn't be changed, or where changing them would make no sense. This stricter use of `const` is known as *const-correctness* and is an additional form of type safety which can often be very useful (of course, most uses of `const` are optional, as in the above program, but its consistent and correct use is strongly encouraged).

References are hugely important to C++ and the necessity of fully understanding them in order to become proficient in the language cannot be overstated. There are two types of references, the style that date back to the earliest versions of C++, now known as *l-value references*, and those introduced with C++11, known as *r-value references* (or sometimes as *forwarding* or even *universal* references). Only l-value references are discussed here.

A reference is an *alias* (an alternative name) for another variable **which must already exist**. It is (intentionally) difficult to make a reference outlive the variable it is *bound* to, managing to do so creates a *dangling* reference, which is undefined behavior. The primary use of references is to make variables visible from enclosed scopes to outer scopes from which they would not otherwise be accessible, as we shall discover later in the discussion of functions. Changing a reference changes the value of the variable to which it is bound, as shown in the program below:

```cpp
// 02-references.cpp : introducing l-value references

#include <print>
using namespace std;

int alice_age{ 9 };

int main() {
    println("Alice\'s age is {}", alice_age);
    int& alice_age_ref = alice_age;
    alice_age_ref = 10;
    println("Alice\'s age is now {}", alice_age);
}
```

**Experiment**

* Change both instances of `int` to `auto`. Does the code still compile?

* Make the global `alice_age` constant. Does the code compile now?

* Now make `alice_age_ref` constant instead. Does the code compile?

* Now remove the `&` on the second line of `main()`. Does this allow the code to compile? What is the output from running this modified program?

As shown above, the syntax for creating and initializing a reference is simple, a single ampersand between the type specifier and the variable name. This difference is subtle compared to a conventional definition, so you will need to be on the lookout for it whenever reading code.

The property of "reference-ness" and "const-ness" is stripped away from variables that are being assigned from. It is possible to initialize a constant from another constant when using `auto`, but this needs to be explicitly specified as a property of the entity being initialized:

```cpp
const auto a{ 10 };  // define a as constant
auto b = a;          // define b as variable copy of a
const auto c = a;    // define c as constant copy of a
```

It is also possible to explicitly (re-)specify the reference property on the assignee side, but attempting to change the value of a constant value through a non-`const` reference is not allowed:

```cpp
const auto d{ 11 };  // define d as constant
auto e{ 12 };        // define e as variable
const auto& f{ 12 }; // define f as constant reference (to a literal constant value)
const auto& g = d;   // define g as constant reference to d
auto& h = e;         // define h as reference to e
const auto& i = e;   // define i as constant reference to e
auto& j = d;         // define j as reference to d
auto& k = f;         // define k as reference to f
```

Of the above, only `b`, `e` and `h` are re-assignable.

**Experiment**

* Try the above definitions and assignment within a `main()` function. Can you get them all to output what you expect?

* Try assigning a new value to each of these eleven variables. What error messages do you expect?

## Constexpr variables

Another way of qualifying a definition is with the `constexpr` keyword. This is a stronger form of `const` which explicity causes evaluation of the initial (and only) value of the variable **at compile-time**. This keyword has uses in *metaprogramming*, which is essentially causing code to be generated and run at compile-time. Note that use of floating-point values **is** permitted; this is not the case in traditional C++ Template Metaprogramming (TMP) which has been around since C++98.

In fact, `constexpr` expressions can be complex with recent compilers, as long as all parts of the expression are themselves `constexpr`. The following program defines two constants, one of which is `constexpr`. Only the `constexpr` entity can be tested against `static_assert()`, which is a boolean truth test checked at compile-time. Don't worry if the inequality syntax is unfamiliar as this is covered in the next Chapter; the test `PI > 3.141 && PI < 3.143` evaluates the mathematical inequality `3.141 < PI < 3.143` in a way that is valid C++:

```cpp
// 02-constexpr.cpp : introducing the constexpr keyword

#include <print>
#include <cmath>
using namespace std;

// Note: currently, not all compilers mark `acos` as a
// constexpr function in cmath. The following line might
// not compile with `clang++` for example.
constexpr double PI1 = acos(-1.0);
constexpr double PI2 = 22.0 / 7.0;

static_assert(PI1 > 3.141 && PI1 < 3.143);
static_assert(PI2 > 3.141 && PI2 < 3.143);

int main() {
    println("PI1 = {}", PI1);
    println("PI2 = {}", PI2);
}
```

(Hint: this program is the first to require an additional header to `<print>`; you may need to add `-lm` to the compile command under Linux in order to link in the math library containing the `acos()` function.)

**Experiment**

* Try to make the second `static_assert()` fail by using an invalid inequality test.

* Now change the program to check the value of *e* at compile time. (Hint: use the expression `exp(1.0)` to get a good approximation of *e*.)

As can be seen from attempting to compile this program, `static_assert()` is a useful tool to have, and adds no run-time overhead cost. The `static_assert()` test can optionally take a second string literal parameter, this being the error message for the compiler to output if the assertion fails.

*All text and program code &copy;2019-2025 Richard Spencer, all rights reserved.*
