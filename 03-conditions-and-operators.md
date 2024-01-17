# Conditions and Operators

## Run-time user input

The programs we have seen in the previous two chapters have been a little predictable in how they run as they have a *linear execution path* through the `main()` function. Such simple programs have very little practical use. More complex programs, which alter their *control flow* based on *user input* fall into two types. *Batch programs* take all of their input at the beginning of their execution, usually from any or all of: program parameters, an environment variable, or an input file. *Interactive programs* enact a dialog with the *user* (the computer operator) while the program is executing. This dialog is often two-way as the user is not necessarily expected to know what input is required without being prompted. Interactive programs often use either a console or a *GUI* (Graphical User Interface, historically found on desktop computers, but more often found these days on tablets and smartphones). Interactive console programs often produce output to the console *interleaved* with user input, while batch programs ususally know all of their input at the beginning of their execution and produce all of their output following this with no further user involvement or action. As an example of a modern alternative, a purely voice-activated device (possibly without a screen) has an interface which interestingly has more in common with an interactive console program than with a GUI application.

As a complement to the stream output object `cout`, the stream input object `cin` (an abbreviation of "Character Input") overloads `>>` (the *stream extraction operator*) to allow variables to be set from user input. When a `cin` input expression is reached, the program waits (indefinitely) for the user to type some input and press Enter. The following program outputs a message inviting the user to enter a number, and then prints this number out again on the console. Before `cin` is used, the variable to be used to accept the input into must have already been defined so that the type of the required input can be deduced. Providing an initial value is preferred (empty braces give it a default value) in case the read by `cin` fails due to either invalid input, such as the user typing letters where digits were required, or end-of-input (Ctrl-D or Ctrl-Z):

```cpp
// 03-age1.cpp : get and then display an integer

#include <iostream>
using namespace std;

int main() {
    int alice_age{};
    cout << "Please enter your guess for Alice\'s age: ";
    cin >> alice_age;
    cout << "You guessed " << alice_age << "!\n";
}
```

Use of `cin` from the user's perspective has a few quirks. Perhaps usefully, whitespace (any spaces, tabs or preceding new-lines) is ignored, while perhaps not so usefully, non numerical input is (silently) evaluated to the number zero. Also, the program makes no checks on the range of the input, so numbers such as `200` and `-50` are accepted without complaint, and printed out. In fact, the variable `alice_age` can be set to any value that can be held by type `int`; however the number must (usually) be entered as a decimal; the prefixes for binary, octal and hexadecimal are by default only interpreted at compile-time for literals within program code.

## Conditions and if-else

The keyword `if` is followed by a *conditional expression* in (mandatory) parentheses, which always evaluates to `true` or `false` at run-time (these named boolean values are implicitly convertible both to and from integer `1` and `0` respectively). (To evaluate conditions at compile-time as well the construct `if constexpr` can be used; this is discussed later.) There are a number of symbols that are combined to represent mathematical conditions of equality, greater than, and so on. Some of these symbols together with their meanings are shown in the table below:

| Symbol |        Meaning        |
|:------:|:---------------------:|
|   ==   |         equal*        |
|   !=   |       not equal       |
|    >   |      greater than     |
|    <   |       less than       |
|   >=   | greater than or equal |
|   <=   |   less than or equal  |

&#42; Note: different from the assignment operator, which is single equals `=` (confusing the two is a common mistake for new C++ programmers).

Variables of any built-in type can be directly tested by an `if` expression; non-zero evaluates as `true` while zero evaluates to `false` (this is the case for both integer and floating-point types). The following program asks for an integer, and outputs `zero` or `nonzero` depending upon the value entered:

```cpp
// 03-zerotest1.cpp : test an integer value against zero

#include <iostream>
using namespace std;

int main() {
    cout << "Please enter an integer value: ";
    int n{};
    cin >> n;
    cout << "The value entered was ";
    if (n) {
        cout << "nonzero\n";
    }
    else {
        cout << "zero\n";
    }
}
```

Notice that the scopes for both the `if` and `else` *clauses* are delimited with `{` and `}`, and that indentation is used for the `cout` operations within them. Notice also that the `if` and the `else` keywords line up vertically, this style is recommended in order to enable in-editor code folding to work, amongst other reasons. In this program the braces for the `if` and `else` clauses are in fact optional because they comprise only a single statement each, however using braces even where not strictly needed is again strongly recommended in case extra code needs to be added to the clauses later (and because code folding often only works in editors where an opening brace exists). Braces for function **definitions**, including `main()`, are always mandatory, even in the case of single-statement or empty functions. Function **declarations**, by contrast, do not have braces; they are analogous to a C++ **statement** being followed by a semi-colon.

**Experiment**

* What happens if you press Ctrl-D (Ctrl-Z then Enter under Windows) when prompted? Can you explain why this is?

* Change the program to test against non-zero using the "not equal" operator and a `0`.

* Change the program again to test against zero, and change the output statements appropriately so the output remains correct.

* Now alter the original program to test a floating-point (`double`) variable as being zero or non-zero.

* Delete the braces surrounding the `if` and `else` clauses. Does the code still compile? What happens if you added a second statement line to the `else` clause? Or the `if` clause?

The `if` statement is a binary choice, however some decisions require more than two options. To enable this, `if` statements can be *chained* together. The following program chains a further `if` onto the tail of the first `else` clause. Note that in this special case, using braces for the first `else` clause is **not** recommended as this would indent the code. The combination `else if` (with mandatory space) is unambiguous to readers of your code; a second statement to the first `else` clause (which would necessitate braces) is unlikely to be needed as the (possibly itself chained) `if` which follows counts as a single statement.

```cpp
// 03-signtest.cpp : test an integer value for zero, positive or negative

#include <iostream>
using namespace std;

int main() {
    cout << "Please enter an integer value: ";
    int n{};
    cin >> n;
    cout << "The value entered was ";
    if (!n) {
        cout << "zero\n";
    }
    else if (n < 0) {
        cout << "negative\n";
    }
    else {
        cout << "positive\n";
    }
}
```

Notice that the conditional test `if (!n)` **reverses** the logic of the previous program, that is it tests `n` agains zero and then inverts the previous result, producing `true` for zero and `false` for non-zero. We could have used `if (n == 0)` to get the same result, however the idiom of testing `!n` is preferred as it also works with objects such as `std::ofstream`, leading to consistent syntax.

Also, notice that the final `else` clause catches everything that reached that point, without performing a further test. It is up to the programmer to ensure that by the time control flow reaches here all other possibilities have been tested for (failure to do so is a *semantic*, or logic error, which can't usually be caught by the compiler).

**Experiment**

* Modify the above program by removing the `else` clauses and make it instead perform three different `if` tests. Consider why this is usually seen to be poor style.

From Mathematics you will be familiar with equality conditions such as 0 ≤ *x* < 10 specifying that the variable *x* is between zero (inclusive) and 10 (exclusive). It is not possible to write such conditions directly in C++ as conditional tests are non-associative, however a close approximation usually can be found by combining condition tests with the keywords `and` and `or` (which operate the same way as `&&` and `||`, which are historically called *logical and* and *logical or*). The following is a variation on a previous program which asks the user to guess an age, and says whether or not it is a good guess:

```cpp
// 03-age2.cpp : get and then test an integer is within range

#include <iostream>
using namespace std;

int main() {
    int alice_age{};
    cout << "Please enter your guess for Alice\'s age: ";
    cin >> alice_age;
    if (6 <= alice_age and alice_age <= 11) {
        cout << "A good guess!\n";
    }
    else {
        cout << "Not a good guess.\n";
    }
}
```

**Experiment**

* Change the above program so that the test logic is inverted with the output remaining the same, in other words `alice_age` falling outside the range 6-11 results in a positive condition test. Hint: you will need to use the `or` keyword and change the order of the output statements.

* Now change `and` to `&&` in the original program. Does it still compile and run? Which style do you prefer?

* Now change `or` to `||` in the modified program. (Known as the *pipe* symbol, this is often Shift+Backslash on the keyboard.) Does it compile and run as expected?

## Conditions and switch-case

When a test for more than one constant integer value is required, a switch-case block can be employed. The *switch expression* follows the `switch` statement and is enclosed in (again mandatory) parentheses and must evaluate to a built-in integral type (that is, between `char` and `long long` in size, possibly with the `unsigned` qualifier). The possible values to test for are listed in a set of `case` statements that fall within the switch scope, delimited as usual by braces. This example program shows a simple desktop calculator with four arithmetic functions:

```cpp
// 03-calc.cpp : simple calculator with four functions

#include <iostream>
using namespace std;

int main() {
    int r{}, x{}, y{};
    char op{};
    cout << "Please enter a calculation (number op number, op is one of +-*/):\n";
    cin >> x >> op >> y;
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
    default:
        cerr << "Error: invalid op.\n";
        break;
    }
    cout << "Result: " << r << '\n';
}
```

Notice that "getting" multiple variables from `cin` allows for the input of three values together, optionally separated by whitespace or newlines. This permissiveness can be useful in some cases but doesn't handle erroneous input very well so is often unsuitable to be used in production code (as error recovery involves clearing the error state, possibly losing input in the process). The four `case` statements each check for a valid integer (actually a character literal) stored in `op` and program flow jumps to the one that matches, if any. The `break` statements are necessary and cause control flow to jump to the closing brace of the switch block; if they were not present flow would *fall through* to the next `case` statement, which is rarely desirable. The `default` case statement is optional, and program flow always continues here if none of the `case` statements match, if it is not present the compiler will often produce a warning.

Notice also the use of `cerr` to output error messages to the *standard error stream*; by default `cerr` echos to the terminal (the same as for `cout`) but this output can be redirected at run-time to a text file (or a null device). The `if` test for zero divisor should be familiar syntax by now and prevents a possible floating-point exception. In this case, and in the case of an error, the result variable contains the default value zero.

**Experiment**

* Change the type of input to `double` and make sure the program still compiles and runs correctly.

* Add a `case` clause for the exponentiation operator `'^'` which calls the function `pow(x,y)` (C++ has no built-in exponentiation operator, `'^'` in code actually means bitwise exclusive-or). Hint: you will need `#include <cmath>` and possibly also `-lm` on the link path.

* Go back to using `int` variables and add the modulo operator `%` to the list of valid operators. You will need to add a suitable `case` clause. Note that this operation gives the remainder from a division, so divide-by-zero needs to be caught here as well.

* Rewrite the case values as plain decimal integers, obtained from a table showing ASCII characteres against their numbers. Then try using hexadecimal values, and then octal values.

* Rewrite the whole switch-case block as multiple if-else-if statements.

The need for `break` statements at the end of each `case` clause has already been mentioned. Occasionally the behavior of program flow falling through to the next case can be useful. More often, multiple `case` matches using the same code is the desired behavior. The following program demonstrates the former of these:

```cpp
// 03-fallthrough.cpp : demonstrate case clauses without break

#include <iostream>
using namespace std;

int main() {
    cout << "Please enter an integer between zero and three:\n";
    int n{};
    cin >> n;
    switch (n) {
    case 0:
        cout << "Number is less than 1\n";
        [[fallthrough]];
    case 1:
        cout << "Number is less than 2\n";
        [[fallthrough]];
    case 2:
        cout << "Number is less than 3\n";
        break;
    case 3:
        cout << "Number is exactly 3\n";
        break;
    default:
        cout << "Number out of range!\n";
        break;
    }
}
```

Notice that `case 1:` falls through into `case 2:`, and `case 0:` falls through into both of these. Some compilers will warn where `break` is missing from a `case` clause as it is a common programming mistake; this warning can be suppressed by writing `[[fallthrough]]` (this is a C++ *attribute*) where the compiler is expecting to find `break` (immediately before the next `case`). Using this attribute in the way shown here provides clarity to both human reader and compiler, it is not necessary where `case` statements follow on immediately with no code between.

**Experiment:**

* See if you can correctly predict the output of this program with user input of `0` through `3`.

* Remove the attributes and try to compile this program. See if your compiler gives a warning; if not, try to enable a warning flag in your compiler options.

## Conditional expressions

The need to choose between two values based on a condition test is so common that C++ has a built-in operator to do exactly that. Consider the following condition test:

```cpp
if (condition) {
    value = first;
}
else {
    value = second;
}
```

The pseudocode shown here is indentical in meaning to the following *conditional expression*:

```cpp
value = (condition) ? first : second;
```

The parentheses around the condition in the conditional expression are in fact optional, because the *ternary operator* `?:` has lower precedence than the (in-)equality tests, however they are often included to aid code readability. Using `if` generates code which is in most cases equally efficient but sometimes a conditional expression is preferred style. Note that `first` and `second` need to be of the same type, or convertible to the same common type, as the type of the entity assigned to `value` needs to be determined at compile-time.

The program below is identical to `03-zerotest1.cpp` in operation except that it has been written using the ternary operator:

```cpp
// 03-zerotest2.cpp : test an integer value against zero and use conditional expression

#include <iostream>
using namespace std;

int main() {
    cout << "Please enter an integer value: ";
    int n{};
    cin >> n;
    cout << "The value entered was " << ( (n) ? "nonzero\n" : "zero\n" );
}
```

Note that the parentheses around the **whole** conditional expression **are** needed as `<<` has a higher precedence than `?:`.

**Experiment**

* Modify this program to remove the code duplication `"zero\n"`.

* Change the program to use two **nested** conditional expressions and produce the same output as `03-signtest.cpp` (this is quite tricky to get right).

## If and switch initializer expressions

An extension to the `if` and `switch` conditional expression syntax is to precede the conditional expression with an initializer and a semi-colon. In fact this is quite flexible, just about any legal C++ expression can be used. The scope of a variable defined in such an initializer has the scope of both the `if` **and** `else` clauses (if present) for an `if` statement, and the `switch` body when used with a `switch` statement.

The following example defines a variable within an `if` statement:

```cpp
// 03-ifinitializer.cpp : use of variable initializer in if statement

#include <iostream>
using namespace std;

int main() {
    cout << "Please enter a positive number:\n";
    unsigned n{};
    cin >> n;
    cout << "The least significant digit was ";
    if (auto m = n % 10; m < 5) {
        cout << "less than five (" << m << ")\n";
    }
    else {
        cout << "five or more (" << m << ")\n";
    }
}
```

The variable defined in the initializer can optionally be used in the condition test, as shown here.

**Experiment**

* Try to use `n` and `m` after the closing brace of the `else` clause.

* Rewrite this program to use a `switch` statement instead of `if`. Pay close attention to the conditional expression needed. The new program should correctly handle all inputs and produce identical output to the one shown.

## Constexpr if

The conditional expression following an `if` statement is evaluated at run-time. However, if the values and entities within the conditional expression are `constexpr` (see the previous article) then the if clause can be made to execute at compile-time, meaning that control flow at run-time is both known and fixed (and hence optimizations can be made).

```cpp
// 03-ifconstexpr.cpp : demonstrate compile-time if

#include <iostream>
using namespace std;

int main() {
    constexpr auto int_size = sizeof(int);
    if constexpr (int_size == 4) {
        cout << "32 bit ints\n";
    }
    else if constexpr (int_size == 8) {
        cout << "64 bit ints\n";
    }
    else {
        cout << "Man, you have weird ints!\n";
    }
}
```

Testing this program in the online Compiler Explorer results in only one of the three string literals actually being embedded in the assembly language output, therefore proving that it is a compile-time evaluation. The ability to perform an if-test at compile-time, as well as assign from `constexpr`-returning function calls, means that the `constexpr` functionality of C++ is in fact *Turing Complete*. It also allows floating-point numbers and even some user-defined types (with `constexpr` constructors) as well as Standard Library types to be used and evaluated at compile-time.

**Experiment**

* Rewrite the program testing &pi; from the previous Chapter to use `if constexpr` instead of `static_assert()`

## Operator precedence

C++ has quite a lot of operators, many of which are inherited from C and operate on the built-in types in exactly the same ways. Some are unary (operate on one value) while others are binary (operate on two values). Unary operators exist which are prefix (written before the object) or postfix (written after the object) and two (`++` and `--`) are both. Binary operators are exclusively infix (written between the two objects they operate on). There is also exactly one ternary operator (which we have seen in this Chapter, the conditional operator), which operates on three values. Some operators are left-to-right associative and others are right-to-left associative, except for the scope resolution operator and comparison operators which are non-associative.

The table below is intended to be a complete list, and as such introduces operators not previously covered; the highest precedence operators are listed first:

| Operator                                                                                                                                                                     | Associativity | Description                                                                                                                                                                                                                                                                                                                                                                                                                       | Pattern                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| ::<br> ::                                                                                                                                                                    | n/a           | global scope (unary)<br> namespace/class scope (binary)                                                                                                                                                                                                                                                                                                                                                                           | ::name<br> namespace_name::entity, class_name::member_name                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| ()<br> ()<br> ()<br> {}<br> type()<br> type{}<br> []<br> .<br> -><br> ++<br> \-\-<br> typeid<br> any_cast<br> const_cast<br> dynamic_cast<br> reinterpret_cast<br> static_cast | left to right | parentheses<br> function call<br> initialization<br> uniform initialization<br> function-style cast<br> function-style cast<br> array subscript<br> object member access<br> pointer to object member access<br> post-increment<br> post-decrement<br> run-time type information (RTTI)<br> cast back to type from any<br> cast away const<br> run-time hierarchical down-cast<br> cast pointers and integers<br>type-checked cast | (expression)<br> function_name(parameters)<br> type_name(expression)<br> type_name(expression)<br> new_type(expression)<br> new_type{expression}<br> pointer[expression]<br> object.member_name<br> pointer_to_object->member_name<br> lvalue++<br> lvalue\-\-<br> typeid(type) or typeid(expression)<br> any_cast&lt;type>(expression)<br> const_cast&lt;type>(expression)<br> dynamic_cast&lt;type>(expression)<br> reinterpret_cast&lt;type>(expression)<br> static_cast&lt;type>(expression) |
| +<br> -<br> ++<br> \-\-<br> !, not<br> ~, compl<br> (type)<br> sizeof<br> &<br> *<br> new<br> new[]<br> delete<br> delete[]<br>                                                            | right to left | unary plus<br> unary minus<br> pre-increment<br> pre-decrement<br> logical not<br> bitwise not<br> C-style cast<br> size in bytes<br> address of<br> dereference<br> dynamic heap memory allocation<br> dynamic array allocation<br> dynamic heap memory release<br> dynamic array release<br>                                                                                                                                    | +expression<br> -expression<br> ++lvalue<br> --lvalue<br> !expression<br> ~expression<br> (new_type)expression<br> sizeof(type) or sizeof(expression)<br> &lvalue<br> *pointer_expression<br> new type<br> new type[expression]<br> delete pointer<br> delete[] pointer                                                                                                                                                                                                                        |
| ->* <br> .*                                                                                                                                                                  | left to right | member pointer selector<br> member object selector                                                                                                                                                                                                                                                                                                                                                                                | object_pointer->*pointer_to_member<br> object.*pointer_to_member                                                                                                                                                                                                                                                                                                                                                                                                                               |
| *<br> /<br> %                                                                                                                                                                | left to right | multiplication<br> division<br> modulo (remainder from division)<br>                                                                                                                                                                                                                                                                                                                                                              | expression * expression<br> expression / expression<br> expression % expression                                                                                                                                                                                                                                                                                                                                                                                                                |
| +<br> -                                                                                                                                                                      | left to right | addition<br> subtraction                                                                                                                                                                                                                                                                                                                                                                                                          | expression + expression<br> expression - expression                                                                                                                                                                                                                                                                                                                                                                                                                                            |
| << <br> >>                                                                                                                                                                   | left to right | bitwise shift left<br> bitwise shift right                                                                                                                                                                                                                                                                                                                                                                                         | expression << expression<br> expression >> expression                                                                                                                                                                                                                                                                                                                                                                                                                                          |
| < <br> <=<br> > <br> >=<br>                                                                                                                                                  | none          | comparison less than<br> comparison less than or equals<br> comparison greater than<br> comparison greater than or equals                                                                                                                                                                                                                                                                                                         | expression < expression<br> expression <= expression<br> expression > expression<br> expression >= expression                                                                                                                                                                                                                                                                                                                                                                                  |
| ==<br> !=                                                                                                                                                                    | none          | test equality<br> test inequality                                                                                                                                                                                                                                                                                                                                                                                                 | expression == expression<br> expression != expression                                                                                                                                                                                                                                                                                                                                                                                                                                          |
| &, bitand                                                                                                                                                                   | left to right | bitwise and                                                                                                                                                                                                                                                                                                                                                                                                                       | expression & expression                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| ^, bitxor                                                                                                                                                                   | left to right | bitwise exclusive-or                                                                                                                                                                                                                                                                                                                                                                                                              | expression ^ expression                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| \|, bitor                                                                                                                                                                   | left to right | bitwise or                                                                                                                                                                                                                                                                                                                                                                                                                        | expression \| expression                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| &&, and                                                                                                                                                                      | left to right | logical and                                                                                                                                                                                                                                                                                                                                                                                                                       | expression && expression                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
| \|\|, or                                                                                                                                                                     | left to right | logical or                                                                                                                                                                                                                                                                                                                                                                                                                        | expression \|\| expression                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
| ?:<br> =<br> *=<br> /=<br> %=<br> +=<br> -=<br> <<=<br> >>=<br> &=<br> \|=<br> ^=                                                                                            | right to left | conditional ternary operator<br> assignment<br> multiplication assignment<br> division assignment<br> modulo assignment<br> addition assignment<br> subtraction assignment<br> bitwise shift left assignment<br> bitwise shift right assignment<br> bitwise and assignment<br> bitwise or assignment<br> bitwise exclusive-or assignment                                                                                          | expression ? expression : expression<br> lvalue = expression<br> lvalue *= expression<br> lvalue /= expression<br> lvalue %= expression<br> lvalue += expression<br> lvalue -= expression<br> lvalue <<= expression<br> lvalue >>= expression<br> lvalue &= expression<br> lvalue \|= expression<br> lvalue ^= expression                                                                                                                                                                      |
| throw                                                                                                                                                                        | right to left | exception throw expression                                                                                                                                                                                                                                                                                                                                                                                                        | throw expression                                                                                                                                                                                                                                                                                                                                                                                                                                                                               |
| ,                                                                                                                                                                            | left to right | comma sequencing operator                                                                                                                                                                                                                                                                                                                                                                                                         | expression, expression                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |

*All text and program code &copy;2019-2022 Richard Spencer, all rights reserved.*
