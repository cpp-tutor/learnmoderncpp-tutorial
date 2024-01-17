# Functions

## Scopes

We have become familiar with the `main()` function, which is automatically called (or *entered*) when the program starts. Variables defined within `main()` have been called local variables because they are local to the scope of `main()`. Importantly they are **not** visible within any functions called by `main()`, even though they retain their state between such calls. The following program defines three variables and also three functions (one of which is `main()`); these three variables have the same name, but different types and values. The values of each of these variables are only accessible within the functions they are defined in, that is: the variables are only *visible* within their own defining function's *scope*.

```cpp
// 04-scope.cpp : demonstrate function scope rules

#include <iostream>
using namespace std;

int alice_height_m;

void victorian_england() {
    size_t alice_height_m{ 1 };
    cout << "In \"victorian_england()\", alice_height_m is " << alice_height_m << ".\n";
}

void wonderland() {
    double alice_height_m{ 0.15 };
    cout << "In \"wonderland()\", alice_height_m is " << alice_height_m << ".\n";
}

int main() {
    cout << "In \"main()\", alice_height_m is " << alice_height_m << ".\n";
    victorian_england();
    wonderland();
    cout << "Back in \"main()\", alice_height_m is still " << alice_height_m << ".\n";
}
```

There are plenty of new things to notice about this program:

* Both of the functions `victorian_england()` and `wonderland()` are defined before (or above) `main()`. This is neccessary for the checks the compiler needs to perform when the function call is reached; C++ function call syntax is the name of the function followed by (possibly empty) brackets and a semi-colon. 

* Both of these function definitions begin with the keyword `void`; these are known as `void` functions (analogous to *procedures* in other programming languages) because they do not return a value (unlike `main()` which always returns an `int`, more on this later in this Chapter).

* Program flow begins as usual in `main()` which produces output both before and after calling the two (previously defined) functions. If `main()` didn't call these two functions, there would be little evidence they even existed in the source code; they probably wouldn't even be *linked* into the executable binary.

* The global variable `alice_height_m` receives a default value because it has *static linkage* (being a global variable).

The output from running the program shouldn't surprise you, being:

```
In "main()", alice_height_m is 0.
In "victorian_england()", alice_height_m is 1.
In "wonderland()", alice_height_m is 0.15.
Back in "main()", alice_height_m is still 0.
```

**Experiment**

* Change all of the variables to type `float`. Does this change the output of the program? Is this what you expected?

* Now give the variables different names, and change the lines beginning with `cout` accordingly. Does this make the program code clearer or less so?

* Now try removing variable definitions from each of the functions in the original program, one by one. Does this change the behavior of the remaining variables?

Local variables with the same name (but not necessarily the same type) as one in the *global scope* (or any *enclosing scope*) temporarily *hide* the other variable for the duration of their own lifetime. After this point, the original variable can be referenced again using the same name.

## Return value

Functions are declared or defined with a type known to the compiler before the function name, the keyword `auto`, or the keyword `void` if there is none. This type can be a user-defined type as we shall discover later, or perhaps more commonly one of the built-in types such as `int`, `double` and so on. The value thus returned is known as the *return value*; its type is the *return type* of the function.  In case of `auto`, the return type is deduced from the entity (entities) after the `return` statement(s); if there is more than one they must return values of the same type. The `return` keyword is implicit at the end of a `void` function; it can also be explicitly used (for example in an `if` clause) to exit from the function early.

The `main()` function is always defined to return an `int` (it can also be `void` in C but this is not legal C++). Uniquely to `main()`, a `return 0;` statement is implicit at the function's closing brace. This causes a return value of zero (which indicates successful execution) to be returned to the calling environment or process; this value is sometimes called the *return code* of a program. Other values are used to indicate different error conditions encountered; a return code of either zero or non-zero is allowed at any point within `main()`, including at the end.

The `return` keyword is mandatory at the end of any non-`void` function other than `main()`, together with a return value which is convertible to the return type of the function. The following program defines a function called `abs_value()` which always returns a positive number:

```cpp
// 04-absolute1.cpp : return the absolute value of a global variable

#include <iostream>
using namespace std;

int value;

int abs_value() {
    if (value < 0) {
        return -value;
    }
    return value;
}

int main() {
    cout << "Please enter a positive or negative integer: ";
    cin >> value;
    auto a = abs_value();
    cout << "The absolute value is: " << a << '\n';
}
```

In fact, the call of `abs_value()` yielding its return value could be used directly in the second `cout` call, which means a named variable `a` is not needed. Using a (temporary) variable to store the return value of a function could be seen as unnecessary if the value is used only once, however if the return value of a function is needed more than once and is not stored in a variable, the function must be called multiple times which could become inefficient.

**Experiment**

* Modify `main()` so that the variable `a` is not needed.

* Modify `abs_value()` so that the keyword `else` is used. Does this make the code any more obvious in intent? Do you get a warning about there being no `return` keyword outside of the `if`-`else` clauses? What happens if you add a third `return` statement just before the function's closing brace?

* Rearrange the order of the definitions (all beginnning with `int`). What errors do you get?

## Parameters by value

Having the function `abs_value()` refer to a global variable is clumsy and error prone, does not scale to larger programs, and is very bad C++ style. What is far better is for the function to have its own local state to operate on, while accepting and returning the desired values. The following program shows how this can be achieved:

```cpp
// 04-absolute2.cpp : return the absolute value of a local variable

#include <iostream>
using namespace std;

int abs_value(int v) {
    if (v < 0) {
        return -v;
    }
    else {
        return v;
    }
}

int main() {
    int value{};
    cout << "Please enter a positive or negative integer: ";
    cin >> value;
    auto a = abs_value(value);
    cout << "The absolute value is: " << a << '\n';
}
```

The local variable `v` inside `abs_value()` is a **copy** of `main()`'s `value`, whose lifetime is (exactly) the length of the function call to `abs_value()`. Its type and name appears between the parentheses after the function name where the function is defined, thus `v` is defined in the function's *parameter list*. The name of another variable, or possibly a constant value, appears between the parentheses where the function is called. Thus `v` is the *parameter* (or *formal parameter*) variable of function `abs_value()`, and this function is called with *argument* (or *actual parameter*) `value` from `main()`. Parameters can also be declared with `auto`, but be aware that the function then becomes a *generic function* (see Chapter 10) and must always be defined in full, not merely declared.

**Experiment**

* Again, modify `main()` so that the variable `a` is not needed.

* Modify `abs_value()` so that the parameter variable is called `value` (instead of `v`), like in `main()`. Does the program still work correctly?

* Modify `abs_value()` to use the conditional operator (`?:`). Can you make this into a one-line function?

* With `abs_value()` as a one-line function, are the braces surrounding the function body still necessary?

The way the variable `value` is passed from `main()` to `abs_value()` is described as *pass by value*. When passed in this way, a copy of the variable is made that can be changed (or *mutated*) by the function accepting the parameter **without** the original value being changed. In this example we have set the return value of the function to the absolute value of the parameter variable, however there is another common way of extracting a modified variable from a function, which is where it is *passed by reference*.

## Parameters by reference

As we have seen, variables which are defined as references are not copies of existing variables, instead they are an alternative name, or *alias*, of a variable **which already exists**. References become particularly useful when defining them in a **different** scope to the variable they reference. As we have seen, a *callee* function cannot access local variables within the *caller* function, instead it can only reference global variables and variables passed as parameters.

Parameter variables can be defined as references by using a single ampersand (`&`) between the type and the variable name in the parameter list. This small and subtle change completely changes the semantics of the function. Changes to a **parameter** variable defined as a *pass by reference* will change the **argument** variable in the calling function, as shown in the following program:

```cpp
// 04-absolute3.cpp : modify a parameter to become its absolute value

#include <iostream>
using namespace std;

void abs_value(int& v) {
    if (v < 0) {
        v = -v;
    }
}

int main() {
    int value{};
    cout << "Please enter a positive or negative integer: ";
    cin >> value;
    abs_value(value);
    cout << "The absolute value is: " << value << '\n';
}
```

This time, `abs_value()` has been defined as a `void` function, with reference parameter `int& v`. This variable is then reassigned (negated) if it tests as less than zero. When the function `abs_value()` returns, the value of `v`, modified or not, is also returned to `main()`'s argument variable `value`. This version of the program is the briefest we have seen so far.

**Experiment**

* Remove the `&` from the parameter list of `abs_value()`. Does the program still compile? Does it work as expected with positive and negative numbers as input?

* Can the sequence `<< value <<` be replaced with `<< abs_value(value) <<` in this program? Why do you think this is?

* Modify `abs_value()` so that the last change above works. Can you see a possible problem with this?

## Forward declarations

We have become used to global variables and functions used by `main()` being written above (*defined before*) the `main()` function. For our simple programs this requirement hasn't presented a problem, however it doesn't scale well to larger projects.

The rule for declarations is that an object can be declared multiple times if all of the declarations are **identical**. (This doesn't violate the ODR, which is to do with definitions.) A declaration implies that an entity is available, at global or local scope depending on the scope of the declaration, without saying where it is defined. (This is left to the linker to resolve; unfortunately, linker errors are often less easy to correct than other, compile-time, errors because the compilation stage has been completed and therefore the source-code is unavailable.)

A function prototype (or *forward declaration*) is the minimum syntax that needs to have been "seen" before the function can be called. The syntax is simple, the return type, function name and types from the parameter list (the variable names are actually optional, but are often included) each with an optional default value, followed by a semi-colon. This declaration must match *exactly* with the function definition (apart from the presence of default values) for the code to compile and link correctly. The forward declaration of the most recent variant of `abs_value()` is simply:

```
void abs_value(int& v); // Function declaration only, not a definition
```

**Experiment**

* Rewrite the four programs introduced so far in this chapter with `main()` as the first function defined, providing suitable function prototypes to forward declare the other functions called. This shouldn't take too long as you can use copy and paste. Hint: don't forget the semi-colons after the forward function declarations.

* For the first two programs, write the global variable **definition** below `main()`. To enable compilation, it is necessary to provide a global variable **declaration** before the function(s) which use the global variable; this declaration takes a form similar to: `extern int i;`. Write the necessary global declarations with the correct type and variable name near the start of the program.

* Now try making these declarations local to a function. Does the code compile and link? How is it possible to (deliberately) cause a linker error?

* What happens if the wrong type is used as return type or parameter in a function declaration? Or the wrong type for a global variable declaration? Consider why this strict behavior might be useful.

## Default arguments

Providing the wrong number of arguments in a function call always results in a compile-time error. (You may also get errors if the number of parameters in a function definition, or their types, don't match those in a previous function declaration. Unless the name, number of parameters, and their types match **exactly** they will be assumed to be different functions.) C++ provides a way for any or all of the parameters in a function call to be optional, and if not present in the argument list are substituted with default values provided in the function declaration only. (Providing them in the function **definition** is not sufficient or even allowed, for technical reasons, unless defined **before** the *call site* with no declaration used).

The following program uses *head recursion* to print out a number in any base up to 16 (defaulting to base 10):

```cpp
// 04-base-n.cpp : print out a number to given base

#include <iostream>
using namespace std;

void print_base_n(unsigned long long num, unsigned base = 10);

int main() {
    cout << "Please enter a number (in decimal): ";
    long long n{};
    cin >> n;
    cout << "Please enter the required base (2-16): ";
    int b{};
    cin >> b;
    if ((b >= 2) and (b <= 16)) {
        print_base_n(n, b);
        cout << '\n';
    }
    else {
        cerr << "Base not in range.\n";
    }
}

void print_base_n(unsigned long long num, unsigned base) {
    if (num >= base) {
        print_base_n(num / base, base);
    }
    cout << "0123456789abcdef"[num % base];
}
```

This is the most complex program we have seen so far, although it does not contain much that is new.

* The function **declaration** for `print_base_n()` contains `= 10`. This is the *default value* for the second argument, which is substituted at the appropriate point in the parameter list, if necessary. For example, a function call `print_base_n(1021)` is substituted by `print_base_n(1021, 10)`; this substitution takes place at compile-time. 

* The *recursive* function `print_base_n()`, so called because it conditionally calls itself, checks whether or not we are dealing with the **most** significant digit, calling itself **without** the **least** significant digit otherwise (and also with the second parameter it received). In Modern C++, recursive functions can be used without a prototype having already been seen.

* The `cout` line outputs a single character which is an index into a string literal of the **least** significant digit (square brackets `[` and `]` are the array index operators, and we are indexing a string literal as if it were an array, which is perfectly legal C++).

If you're struggling to follow the control flow through the recursion then imagine the function call `print_base_n(9)`, and then `print_base_n(89)`, and then `print_base_n(789)`. (Recursion makes use of the fact that each call of the function retains its own private copy of the parameter variables as well as any other local variables.)

**Experiment**

* Remove the variable names `num` and `base` from the declaration of `print_base_n()`. Does the program still compile? What happens if you choose other names instead?

* Make sure the program works correctly by checking with binary, octal and hexadecimal **literals**, and bases 2, 8 and 16 **at run time** respectively.

* Modify the program again, so that numbers printed out in up to base 64 are supported.

* Now modify the program so that `num` being **signed** `long long` is supported.

## Implicit narrowing casts

We have seen that variable initialization using uniform initialization syntax disallows implicit narrowing when defining a new variable. Calling a function can also imply a narrowing cast, and this **is** allowed, as demonstrated in the following program:

```cpp
// 04-no-narrow.cpp : calling a function with different types of arguments and parameters

#include <iostream>
using namespace std;

void f(int i) {
    cout << "f(): received int: " << i << '\n';
}

void g(double d) {
    cout << "g(): recieved double: " << d << '\n';
}

int main() {
    f(1);
    g(1);
    f(2.5);
    g(2.5);
}
```

Running this program produces the output:

```
f(): recieved int: 1
g(): recieved double: 1
f(): recieved int: 2
g(): recieved double: 2.5
```

Notice that the call `g(1)` promotes the `int` argument to `double` silently, although this is not apparent when printing the number (it doesn't print as `1.0`, but could be made to with stream formatting manipulators, see Chapter 8). Also, notice that the call `f(2.5)` narrows the `double` argument to `int`, so the fractional part is lost.

It is possible to write code that disallows narrowing casts by using universal references and perfect forwarding but demonstrating this is beyond the scope of this Tutorial. You should be aware that in general functions calls may silently produce narrowing effects, however some implicit conversions (such as pointer to integer or floating-point number) are not allowed.

**Experiment**

* Add a third function `h()` which takes parameter `unsigned u`. What happens when you call it with a negative integer or floating-point value? Does this surprise you?

## Function overloading

C++ allows multiple definintions of functions with the **same** name if the parameter(s) is/are of **different** types. (This works at the level of the linker by use of name mangling, whereby the name of the function is augmented by its parameter list. It is possible to disable function name mangling by declaring *C linkage*; such functions are declared with `extern "C"` and can also be called from C code.) The following program declares two functions again, this time both called `f()`:

```cpp
// 04-overload.cpp : calling a function with different types of arguments and parameters

#include <iostream>
using namespace std;

void f(int i) {
    cout << "f(): int: " << i << '\n';
}

void f(double d) {
    cout << "f(): double: " << d << '\n';
}

int main() {
    f(1);
    f(2.5);
}
```

Running this program produces the output:

```
f(): int: 1
f(): double: 2.5
```

The function to be used is determined at compile-time from the usage at the call site, as the types of the arguments are always known. A best-match is performed in the case of no exact match, so for example `f('a')` would call `f(int)` while `f(0.5f)` would call `f(double)`.

**Experiment**

* Add a third overload `f(unsigned u)`. How can you cause this function to be called?

## Static and thread-local

Variables declared `static` inside a function body are in fact global variables with visibility limited to function scope. They are initialized when the program starts, although conceptually they are given an initial value when the function is first called, which is then preserved between function calls. The following program demonstrates this:

```cpp
// 04-static-var.cpp : preserving function state in a static variable

#include <iostream>
using namespace std;

void f() {
    static int s{1};
    cout << s << '\n';
    ++s;
}

int main() {
    f();
    f();
    f();
}
```

The output from running this program is:

```
1
2
3
```

Static local variables are slightly deprecated in C++ because they are not *thread-safe*; different threads calling the same function that has a `static` variable will lead to unpredictable results. In real code there will almost always be a better way of doing things than using a static variable.

**Experiment**

* Modify this program so that it counts from `10` down to `0` and then outputs `Blastoff!`. (Don't use a loop, even if you're tempted to. Loops are covered in the next Chapter.)

* Modify the same program to use a file-`static` variable instead of a function-`static` one (this is a small change to the code, but you should try to understand the difference).

Variables declared `thread_local` within a function have a new copy of the variable created upon launching a new thread, which is independent from others within the calling thread or any other thread. Since the way in C++ to launch a new thread is to specify a function to be called, this behavior is useful in multi-threaded programs. Further discussion of *parallelism* is beyond the scope of this Tutorial. (Variables can also be declared both `static` and `thread_local`.)

Functions can be declared `static` by prefixing the return type in the function declaration and definition with the keyword `static`. As with global variables, this reduces the visibility of the function to the translation unit it is defined within. More useful in most cases are `inline` functions, described later.

## Structured bindings

You may be interested to learn that the return type of any function other than `main()` can be declared and defined with `auto` (this includes implicitly `void` functions). As mentioned above, functions that are defined with `auto` as the return type must use the same type for all of their `return` statements for the return type to be correctly deduced.

Use of `auto` return type becomes especially useful when returning two or more values from a function. Such a return type is called an *aggregate*, which is unpacked into single variables using a *strutured binding*. The following program returns a `double` and an `int` from a function `get_numbers()`:

```cpp
// 04-aggregate.cpp : calling a function with different types of arguments and parameters

#include <iostream>
#include <utility>
using namespace std;

auto get_numbers() {
    cout << "Please enter a float and an integer: ";
    double d{};
    int i{};
    cin >> d >> i;
    return pair{ d, i };
}

int main() {
    auto [ a, b ] = get_numbers();
    cout << "You entered " << a << " and " << b << '\n';
}
```

There are three main new things to notice about this program. 

* The function `get_numbers()` is declared with `auto` return type.

* The last line of this function returns a Standard Library `pair`, which is initialized with uniform initialization syntax.

* This `pair` is *unpacked* into the variables `a` and `b` in `main()` using structured binding syntax, which again uses `auto`. The types of `a` and `b` are determined (at compile-time) from the aggregate return type of `get_numbers()`.

**Experiment**

* Make `get_numbers()` return three variables, the third being `unsigned`. Hint: you will need to use `return tuple{ d, i, u };` or similar, use `#include <tuple>`.

* Rewrite `get_numbers()` to accept and modify two reference parameters, and return results to `main()` in this way.

## Inline functions

Functions can be declared as inline functions by using the keyword `inline` before the return type in the function definition. The main aim of declaring a function `inline` is to remove the time overhead of a function call; the code is replicated for each function call *in place* at the call site(s). Functions declared with `inline` must be present (and identical) in each translation unit that uses them, hence they often appear in header files; this is a special relaxation of the ODR. Overuse of inline functions can lead to *code-bloat*, so they are best reserved for very short functions. The following program demonstrates use of the `inline` keyword:

```cpp
// 04-inline.cpp : use of an inline function

#include <iostream>
using namespace std;

inline void swap(int& x, int& y) {
    auto z = x;
    x = y;
    y = z;
}

int main() {
    int a = 1, b = 2;
    cout << "(1) a = " << a << ", b = " << b << '\n';
    swap(a, b);
    cout << "(2) a = " << a << ", b = " << b << '\n';
}
```

Running the above code produces:

```
(1) a = 1, b = 2
(2) a = 2, b = 1
```

The `swap()` function swaps over two `int`s *in-place* by using reference parameters and a local variable. (In real code you would want to use the Standard Library's `std::swap()` template, rather than writing your own version.)

**Experiment**

* Remove the `inline` keyword from the above program. Does it still compile? Experiment with the online Compiler Explorer to see if it produces more efficient code when present.

* Now try moving the `swap()` function to below `main()`, adding a function declaration before `main()`. Can the function be made `inline` again?

* Modify the program `04-abs2.cpp` so that `abs_value()` is an `inline` function. (This change is trivial to make.) Does it compile as expected? Does it still run correctly?

## Constexpr functions

Functions can be defined with the `constexpr` keyword before the return type in the function definition. Like `constexpr` variables and `if constexpr`, this allows the compiler to generate and run code at compile-time. The following program shows how compile-time `static_assert()` can be used with the return value of a `constexpr` function:

```cpp
// 04-constexpr.cpp : use of a constexpr function with static_assert

#include <iostream>
using namespace std;

constexpr int factorial(int n) {
    if (n < 2) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

static_assert(factorial(0) == 1);
static_assert(factorial(5) == 120);

int main() {
    cout << "Please enter a number: ";
    int n{};
    cin >> n;
    cout << n << "! = " << factorial(n) << '\n';
}
```

Note that it is **not** necessary (or even possible) to use `if constexpr` for the condition test within the function; the `constexpr` function is nevertheless able to be evaluated at compile-time as well as run-time. A constexpr function is **not** allowed to modify global state (such as `cout`), amongst other restrictions.

**Experiment**

* Experiment with invalid input (ie. negative numbers, overly large numbers or Ctrl-D/Ctrl-Z). Consider how you could modify the program to deal with this.

* Write a program to calculate the N-th Fibonacci number, where *fib(0) = 0*, *fib(1) = 1* and *fib(n) = fib(n-1) + fib(n-2)* for *n >= 2*. Hint: utilize tail recursion again.

## Non-returning and noexcept functions

It is possible to write a function which never returns, for example using an infinite loop. Another example might be a function that causes an abnormal early exit from the running program; the Modern C++ way of doing this is to throw an exception, or even call `std::terminate()` directly (the C Standard Library also provides `abort()`, `exit()` and `quick_exit()` but these do not deallocate all global objects correctly). The way to indicate this property to the compiler is to use the `[[noreturn]]` attribute when declaring the function, as shown in this example program:

```cpp
// 04-noreturn.cpp : program which does not return from main()

#include <iostream>
using namespace std;

[[noreturn]] void report_fatal_error(int e) {
    cerr << "Fatal error code: " << e << '\n';
    terminate();
}

int main() {
    cout << "Entering main()\n";
    cout << "Calling report_fatal_error()\n";
    report_fatal_error(-1);
    cout << "Leaving main()\n";
}
```

A function declared with `[[noreturn]]` should be a `void` function (as having a return type is meaningless if the function never returns). The compiler should warn if any code path can achieve a natural return from such a function.

The keyword `noexcept` is used to declare that a function is guaranteed to not throw an exception. This guarantee is preserved over function calls, thus a non-`noexcept` function called by a `noexcept` function is implicitly `noexcept`. The motivation behind this keyword is that the compiler and run-time do not have to support stack unwinding used by the keyword `throw`, which can add a significant time and space advantage to your code.

**Any** exception thrown by an explicitly or implicitly `noexcept` function, or any library routine it may call, causes a call to `std::terminate()` as above. The following program demonstrates this:

```cpp
// 04-noexcept.cpp : a noexcept function throwing an exception

#include <iostream>
#include <stdexcept>
using namespace std;

int throw_if_zero(int i) noexcept {
    if (!i) {
        throw runtime_error("found a zero");
    }
    cout << "throw_if_zero(): " << i << '\n';
}

int main() {
    cout << "Entering main()\n";
    try {
        throw_if_zero(1);
        throw_if_zero(0);
    }
    catch(...) {
        cout << "Caught an exception!\n";
    }
    cout << "Leaving main()\n";
}
```

**Experiment:**

* Remove the `noexcept` keyword. Does the program compile? What is the output when run?

*All text and program code &copy;2019-2022 Richard Spencer, all rights reserved.*
