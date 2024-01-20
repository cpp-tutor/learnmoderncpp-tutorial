# Arrays, Pointers and Loops

## Number and character arrays

A C++ array can be described as a collection of entities *of the same type* arranged *contiguously* in memory. C++ inherits its *built-in array* syntax from C, sometimes these are referred to as *C-style* arrays. Uniform initialization syntax can be used to assign the contents of an array at the point it is defined (and **only** at this point). This is called *aggregate initialization* using a *braced initializer* (the equals sign shown below is in fact optional):

```
int numbers[] = { 1, 2, 3, 4, 5 };
```

Notice that the type is `int[]` ("array of `int`"), however the square brackets *bind* to the variable name, in this case `numbers`, not to the type specifier, in this case `int`. The optional number between the square brackets (which must be a **constant** known at compile-time) is the length of the array; this is fixed at compile-time and cannot be changed at run-time. If no value is provided here then it is calculated from the number of *elements* which make up the initializer (in this case the value is 5). The array size must be **at least** as large as the initializer being assigned from, otherwise a compile-time error is produced. If the size of the array is given as greater than the number of elements in the initializer, the remaining elements are default-constructed (zeroized for the built-in types).

The array variable `numbers` is writable through subscripting syntax using square brackets `[` and `]`. The array index starts at **zero** (`[0]`) for the first element. Attempting to read or write beyond the last element is undefined behavior, as is use of negative indices.

```
numbers[4] = 6;       // ok, numbers[] is { 1, 2, 3, 4, 6 }
numbers[5] = 99;      // not ok, compiles but yields undefined behavior
auto i = numbers[0];  // ok, i is 1
auto j = numbers[-1]; // not ok, compiles but yields undefined behavior
```

A string literal can be thought of as simply an array of characters, thus a string literal can be used to initialize an array of `char`:

```
char name[] = "Dinah";
```

This type of array is modifiable, so individual letters can be changed using array indexing syntax. (Actually fact the variable contents are writable is not without overhead; the string literal used to initialize the array is stored in a read-only part of the executable binary and is copied into the newly-allocated array at run-time.) A terminating zero-byte is also added to the array, so the array length implicit inside the square brackets is 6, not 5.

A braced initializer can also be used with character literals as elements, so the same result could be achieved by using:

```
char name2[] = { 'D', 'i', 'n', 'a', 'h', '\0' );
```

This time the terminating zero-byte has to be explicitly specified, if it is desired; both `name` and `name2` are safe to be put to streams such as `cout` as they each have this terminating zero-byte. A single element of each of these variables could also be output, and would produce the same output as a character literal:

```
cout << name << '\n'; // outputs "Dinah" followed by new-line
cout << name[0];      // outputs "D"
```

Due to the fact that the size of an array is known to the compiler, this size can be used in code. The Standard Library *function templates* `std::size()` and `std::size_bytes()` can be used to provide the number of array elements and amount of memory used, respectively. The value returned from either of these functions can be used in expressions declared with `constexpr`.

Here, `size(name)` would return 6, while `size_bytes(numbers)` would return 20, assuming 32-bit `int`s. Older variants of C++ only provided the built-in `sizeof()` operator, which returns the same as `size_bytes()`.

## Range-for

We've previously seen that string literals can be output using `cout` without concerning ourselves with the details. The built-in `for` command can be used over a *range of values* applying the same operation(s) to each one in turn. This type of `for` statement is known as a *range-based for loop*, or range-for for short.

A range-for statement can have two or three parts enclosed by parentheses. The initializer statement (the same as for `if` and `switch` statements) is the optional first part, and is followed, if present, with a **semi-colon**. Then follows the *for-loop variable* definition, which can be declared with either `auto` or with an explicit type, and with optional `const` (constant) and `&` (reference) or `&&` (universal reference) semantics. Then a **colon** separates this from the expression to be *iterated* over, known as the *range expression*. This program demonstrates simple use of a two-part range-for (without an initializer):

```cpp
// 05-range-for.cpp : print a string literal vertically

#include <iostream>
using namespace std;

int main() {
    for (auto c : "Dinah") {
        cout << "- " << c << '\n';
    }
}
```

Here the for-loop variable `c` is deduced (due to the use of `auto`) to be of type `char`, the type of a single element of the range expression `"Dinah"`. The contents of the variable is actually a *copy* of a single element in the range expression; if `auto&` were used instead it would be a reference to a single element within the range expression. The for-loop variable is then sent to `cout` as a single character literal.

**Experiment**

* Does this program produce any unwanted output? Find two different ways of fixing this.

* Change `auto` to `char` and try to note any changes. Change this again to `int`. What is the output now?

* Now change back to use of `auto` and try using the other types of string literal (recall the prefixes `u8`, `u` and `U`). Does the program still compile and produce the correct output? What about when non-UTF7 characters are used in the string literal?

* Add an initializer statement of type `bool` and make the program output `D,i,n,a,h` using the same range expression. Hint: you might need to use `if` statements

* Now declare a separate variable as an array of `char` and use this named variable as the range expression.

* Declare `c` as a reference variable. Does the program still compile? What could be the use of this when using a writable range expression?

In fact, range-for loops can be used with any type of array or container which supports `std::begin()` and `std::end()`, not just built-in types. However, further discussion of creating your own types which can be iterated over in this way is beyond the scope of this Tutorial.

## Pointers

We have learned that subscripting syntax can be used with string literals and built-in arrays. You may be surprised to learn that subscripting also works with pointers. So what exactly is a pointer in C++?

A pointer is a variable that holds a machine address, therefore on most modern machines it is a 64-bit value. Pointers can be `const` or point to `const` data, or both; they can also be typed or untyped (subscripting only works on typed pointers). In addition they can hold the value `nullptr` instead of a (hopefully valid) memory address.

Assigning a string literal directly to a variable declared with `auto` actually assigns a pointer to the first character of the (read-only) string literal. Thus the following two assignments are identical:

```
auto s1 = "Dinah";
const char *s2 = "Dinah";
```

In each case subscripting syntax can be used, in this case from zero up to five, and individual elements can be compared or output. Directly comparing the values of the two pointers, compares the memory addresses, not the value(s) they point to, as shown here:

```
if (s1[0] == s2[0]) { /*...*/ } // condition test evaluates to true
if (s1 == s2) { /*...*/ }       // condition test (probably) evaluates to false
                                // (your compiler may optimize the two data entities into one)
```

Pointer variables are defined using an asterisk in all cases (it is optional when using `auto`). An asterisk is also used to *dereference* a pointer, that is access the value it "points to". The following program defines a variable `i` and a pointer `p` that points to it (that is `p` holds `i`'s machine address). The type of `i` is `int` while the type of `p` is `int*`. A variable `j` is used to hold user input:

```cpp
// 05-pointer.cpp : write a variables value through a pointer

#include <iostream>
using namespace std;

int main() {
    int i{ -1 }, j{};
    int *p;          // define p as an int*
    p = &i;          // set p to address of i
    cout << "(1) p = " << p << ", *p = " << *p << ", i = " << i << '\n';
    cout << "Please enter an integer: ";
    cin >> j;
    *p = j;          // assign the value of j to the variable p points to
    cout << "(2) p = " << p << ", *p = " << *p << ", i = " << i << '\n';
}
```

Running this program produced the following output, with the input value of `j` being `10`:

```
(1) p = 0x7ffd3082cf04, *p = -1, i = -1
Please enter an integer: 10
(2) p = 0x7ffd3082cf04, *p = 10, i = 10
```

In this program the definition `int *p;` makes `p` a pointer to an `int`. At this point in the program it has not been assigned to, and is therefore an *uninitialized pointer*. The syntax `&i` means address-of `i` (the memory address of **any** variable can be obtained by preceding it with an ampersand in this way) and this value is assigned to `p`. Be careful not to confuse this with the definition of a reference, where the ampersand is on the opposite side of the equals sign.

The value of the entity `p` points to can be output by sending `*p` to `cout`. Changing `*p` also changes `i`; this behavior might surprise you, it's almost as if `i` has changed without permission. As can be seen from the output of this program, `p` has the same value throughout, while `*p` and `i` change together.

**Experiment**

* Modify this program so that `p` is defined on the same line as `i` and `j`.

* Now modify the program so the variable `j` is not needed. Is the output the same?

* Now modify the program again so that p is initialized on the same line as `i`. The `main()` function should now comprise of just 5 lines.

## While loops

We have tested for a condition being true or false at a single point during the program, using the `if` statement. Often, it is desired for an operation to continue for as long as a certain condition is met. The `while` statement begins a loop with a *pre-condition test*, where the body is only ever executed if the condition evalautes to `true`. The condition is written within parentheses and the test is done **before** the loop is entered, thus it is perfectly legal and possible for a `while` loop to execute zero times.

The following program shows a `while` loop being used to iterate over the contents of an array of `char`, which has been entered by the user, as long as the element pointed to by `p` is non-zero:

```cpp
// 05-while.cpp : print a user-entered string vertically

#include <iostream>
using namespace std;

int main() {
    char str[20];
    cout << "Please enter a string (up to "
         << size(str) - 1 << " characters):\n";
    cin.getline(str, size(str));
    const char *p = str;
    while (*p) {
        cout << "- " << *p << '\n';
        ++p;
    }
}
```

A few new things to notice about this program:

* The size of the array called `str[]` is set by an integer constant, and this value is needed twice more in the program where it is accessible as `size(str)`, a compile-time value. An alternative way would be to use a constant or macro at each point the value is needed, and this is the only way to avoid repeated *magic constants* in older versions of C++ which did not provide `std::size()`.

* The function `cin.getline()` (actually the dot `.` indicates that `getline` is a *member function* of `cin`, more on these later) is called to read keyboard input into `str[]`. This reads input directly into the memory location provided by the first argument up to a maximum number of characters (including the zero terminator) as set by the second argument. A new-line character ('\n') is never stored and any extra input which doesn't fit into `str[]` is saved for future calls to `cin`.

* The pointer `p` is set to the first character of `str[]`, and the type `const char *` specifies that we do not wish to modify it. In fact assigning an array to a (correctly typed) pointer is an implicit conversion, known as *array decay* because the size attribute is "lost". This also occurs when calling a function using an array as an argument, to either an array **or** pointer parameter. (In the same manner as `i` and `j` for temporary `int` variables, `p` is a common name for a pointer.)

* The **dereferenced** value `*p` is checked against zero by the `while` loop condition test, and if it is non-zero then it is sent to `cout` by the body of the `while` loop. The increment of `p` (actually a pre-increment, the one you should prefer given a choice) is necessary to prevent an infinite loop outputting the first character of `str[]`. This changes the value of `p` by one in order to point it towards the next character (of `str[]`), a process which repeats until the terminating zero-byte is reached. Importantly, `str[]` is left unchanged and remains able to be used again; this is the motivation for assigning `str` to a different (mutable) pointer variable `p`.

**Experiment**

* Enter a blank line as input. Is there any output produced? Why is this?

* Swap the lines starting `cin.getline` and `const char *p`. Does the program still compile? Why do you think this is?

* Change the while loop to be a single line, by moving the `++` operator into the `cout` statement. Hint: you will have to use `p++` instead of `++p`; do you understand why?

* Now remove the braces from the body of the `while` loop. Does the code still compile? What would happen if another line were added to the body of the loop?

## For loops

A standard `for` loop is similar to a `while` loop in that it has a pre-condition test. A common historical use for `for` loops is to iterate over an array using subscript syntax, rather that pointers. A `for` loop has three parts enclosed within parentheses, any of which can be empty, each part separated by a semi-colon. The first part is an initializer, as in a three clause range-for loop. This typically initializes a single variable known as the *loop counter*, whose scope is the body of the `for` loop (only). The second part is the condition test, which functions exactly the same way as that in a `while` loop; if empty it evaluates to `true`, which causes an *infinite loop*. The third part is an iteration statement to be executed **after** each time the body of the loop has been executed.

The following program defines and assigns to an array of `int` called `a`, and outputs each element in turn (on the same line), by subscripting the array with loop counter `i`:

```cpp
// 05-for.cpp : output an array using for

#include <iostream>
using namespace std;

int main() {
    int a[]{ 9, 8, 7, 6, 5, 4 };
    for (int i{ 0 }; i != 6; ++i) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}
```

Output from this program:

```
9 8 7 6 5 4 
```

Notice that the *loop counter* `i` is initialized to zero and has this value on the first pass through the `for` loop. The test `i != 6` is true exactly `6` times (with `i` having values in turn of: `0`, `1`, `2`, `3`, `4`, `5`); this matches **all** of the the valid array indices of `a[]`. Use of `i != 6` in this way is considered better C++ programming style than `i < 6`, or even worse `i <= 5` (neither of which is actually any safer in practice). This program produces trailing space in its output, which isn't ideal, but we'll ignore this defect for now. The last statement in `main()` outputs a newline, and being outside of the body of the loop is executed only once.

**Experient**

* Change both the size of `a[]` and the number in the condition test to `10`, without altering the braced initializer. What do you notice about the output? Can this be relied upon?

* Now change the condition test to automatically track the size of the array. Hint: use `size(a)`.

* Rewrite the program to use a `while` loop instead of `for`. What similarities do you notice?

* Write a program to accept five `double`'s as user input into a suitable array and then print them out on separate lines. Hint: use two (non-nested) `for` loops

* Now write a program to output a countdown from `10` to `0` inclusive, printing `Blastoff!` at the end. Hint: use a suitable condition test and iteration statement with a `for` loop.

Loops in production code are often more difficult to decipher than the one shown above, partly because the simplest cases are handled by range-for. The following program has two loop counters, either of which could be tested in the condition test part of the `for` loop:

```cpp
// 05-christmas.cpp : calculate total number of gifts from the popular song

#include <iostream>
using namespace std;

int main() {
    int gifts{ 0 };
    for (int i{ 1 }, j{ 12 }; i <= 12; ++i, --j) {
        gifts += i * j;
    }
    cout << gifts << " gifts in total.\n";
}
```

A few things to note about this program:

* The variable `gifts` is defined and initialized outside of the `for` loop and is able to be referenced after the loop has completed.

* There are two variables defined and initialized in the loop initializer, therefore there is no clear distinction as to which, if either, is the loop counter.

* The construct `++i, --j` uses the *sequencing operator* (comma) to sneak two operations in where only a single statement is allowed. This use of comma is rare; another possible use is in ternary expressions.

* The add-assign operator (`+=`) is used as a shorthand for an assignment to self followed by an addition. It is often used in C++, as well as other operator-assign expressions.

**Experiment**

* Find two different variants of the condition test (`i <= 12`) that continue to work correctly.

* Find a way to dispense with the variable `j`. Consider whether this version is clearer to understand.

## Do-while loops

A `do`-`while` loop is unique in having a *post-condition test*; thus the loop body is guaranteed to execute at least once. The loop begins with the `do` keyword followed immediately by the loop body (which would usually be delimited by braces). The loop ends with the `while` keyword followed by the loop post-condition test in parentheses and then a (mandatory) trailing semi-colon.

Do-while loops are similar to "repeat-until" loops of other languages, except that the post-condition test is logically inverted. Use of `do` and `while` has been criticised in the past, mainly because the indentation of the body of the loop is visually misleading; it is always executed but could be interpreted as not being so from a casual glance. A better result can usually be achieved using a `while` loop and some duplication of code.

The following program asks for input from the user repeatedly until the input provided is valid:

```cpp
// 05-do-while.cpp : use of post-condition loop to validate user input

#include <iostream>
using namespace std;

int main() {
    int i{};
    do {
        cout << "Please enter a negative number: ";
        cin >> i;
    } while (i >= 0);
    cout << "You entered: " << i << '\n';
}
```

The variable `i` is defined before the loop, so it is still in scope after the loop completes. The `do`-`while` loop then repeats indefinitely until a negative number has been entered. To provide a comparison, this is an exactly equivalent program, written with a regular `while` loop instead:

```cpp
// 05-not-do-while.cpp : alternative to post-condition loop

#include <iostream>
using namespace std;

int main() {
    int i{};
    cout << "Please enter a negative number: ";
    cin >> i;
    while (i >= 0) {
        cout << "Please enter a negative number: ";
        cin >> i;
    }
    cout << "You entered: " << i << '\n';
}
```

Notice that this pre-condition test (after the `while` keyword) is identical to the previously used post-condition test. Also, the regular `while` loop version offers the opportunity for an addition message such as `"Invalid input! Please try again: "` to be printed in order to aid the user should they get the first input wrong.

**Experiment**

* Write a program to output a count-down from a user-entered positive integer down to zero using two `do`-`while` loops.

## Break and continue

All of the loop constructs we have met so far have repeated predictably so long as a condition is met (either a boolean condition with `while`, `for` and `do`-`while`, or until the range expression had been iterated over fully in the case of range-for).

Similar to its use with `switch`, `break` allows us to *break out of* a loop early; typically it is used within an `if` clause. When encountering a `break` statement, control flow jumps immediately to the first statement **outside** of the loop body, which causes an early exit from the loop into its immediately enclosing scope.

The `continue` keyword is used to *jump back* to the beginning of the loop, again it is typically used within an `if` clause. When encountering `continue` in a `while` loop, control flow returns to the condition test. With regular `for` the same happens, but the iteration statement is executed too. For `do`-`while` loops control flow jumps to the `do` statement, while for range-for the for-loop variable gets the value of the next element of the range expression.

In the case of nested loops, use of `break` may not operate as required as it only breaks out of the innermost loop. In this case a `goto` statement inside the loop, and a target label after the end the outermost loop can be used, although this is very rarely needed.

The following program shows `break` and `continue` operating in what would otherwise be an infinite loop:

```cpp
// 05-break-continue.cpp : use of control flow commands in loop

#include <iostream>
using namespace std;

int main() {
    for (;;) {
        int i{};
        cout << "Please enter a positive number (zero to quit): ";
        cin >> i;
        if (i == 0) {
            break;
        }
        if (i < 0) {
            continue;
        }
        cout << "You entered: " << i << '\n';
    }
    cout << "Program ended\n";
}
```

Notice that no output is produced when entering a negative number, and that the only way to quit the program is to enter `0`. The `for (;;)` loop (read as "forever") iterates repeatedly because the empty condition test always evaluates to `true`, as mentioned previously.

**Experiment**

* Write a program which uses a regular `for` loop with an empty condition test, and an increment operator as the iteration expresssion, which outputs all the even numbers between zero and 20 (inclusive)

* Write a program which asks for a positive integer, and outputs all positive even numbers between zero and this number (inclusive, if the input is even).

## Array decay and pointer arithmetic

It is possible for a function to accept built-in array as a parameter, however any size information previously known to the compiler is lost. Therefore there is no advantage in declaring the parameter as an array type, as opposed to a pointer type. The following program demonstrates two functions which are equivalent:

```cpp
// 05-array-decay.cpp : demonstrate equivalence of pointer vs array parameters

#include <iostream>
using namespace std;

void print_arr(const char s[]) {
    while (*s) {
        cout << *s++;
    }
    cout << '\n';
}

void print_ptr(const char *s) {
    while (*s) {
        cout << *s++;
    }
    cout << '\n';
}

int main() {
    print_arr("Hello");
    print_ptr("World");
}
```

A couple of things to note about this program:

* As a constant string literal is passed, both functions need the parameter to be qualified with `const`. This means that the variable `*s` cannot modify what it points to, although it can itself be modified (for example, by being incremented as shown here). It is possible for the pointer to be non-modifiable too, by utilizing a second `const` as in: `const char * const s`.

* The "array" variable accepted by `print_arr()` is able to be dereferenced and incremented in exactly the same way as the pointer accepted by `print_ptr()`. Once either has been modified, the original reference is lost; notice that the bodies of both functions are identical.

It should be clear that when passing an array to a function, only a pointer to the first element is in fact passed. Thus it is similar in concept to pass-by-reference, that is a function which modifies an array passed to it also modifies the same entity as visible in the calling function.

**Experiment**

* Remove the `const` qualifiers and modify `main()` so that the program still compiles. Hint: use built-in arrays instead of string literals.

* Now try to modify the first letter within either function. Does this change the array within `main()`?

Should the length of an array be needed in the callee function, then this needs to be passed as a separate parameter. Both pointer and array parameters can be indexed using either square brackets or *pointer arithmetic*, as shown in this example program:

```cpp
// 05-pointer-index.cpp : demonstrate array indexing and pointer arithmetic

#include <iostream>
using namespace std;

void print_arr(const char s[], size_t n) {
    for (int i = 0; i != n; ++i) {
        cout << s[i];
    }
}

void print_ptr(const char *s, size_t n) {
    for (int i = 0; i != n; ++i) {
        cout << *(s + i);
    }
}

int main() {
    print_arr("Hello, ", 7);
    print_ptr("World!", 6);
    cout << '\n';
}
```

**Experiment**

* What happens if the length argument passed to the function is too small? Or too large?

* Swap the bodies of the two functions over. Does the program still compile?

* Add a second `const` qualifier to `s` in `print_ptr()`. Does the program still compile? Does this surprise you?

It is important to understand that there is **no difference** between `array[0]` and `*array`, nor between `array[n]` and `*(array + n)`. Pointer arithmetic works by adding *n times sizeof element* to the array or pointer variable, which itself is a machine address. (The only type of pointer that does not support this is `void *`.)

## Environment

We have met the concept of the return value of `main()` being passed back to the calling environment. A different definition of `main()` accepts arguments from the calling environment, as a pointer to a list of pointers to string literals, as well as the length of this list. Of course, you are free to name these variables how you wish, but by convention they are called `argv` and `argc`.

The following program prints out all of the arguments it is called with at run-time:

```cpp
// 05-args.cpp : print out all arguments

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    for (int i{ 0 }; i != argc; ++i) {
        cout << "Argument " << i << ": " << argv[i] << '\n';
    }
}
```

A few things to note about this program:

* A range-for loop cannot be used here, as `argv[]` contains no size information within `main()` (array decay).

* The second parameter can instead be declared as `char **argv` with no change in meaning.

* Each string literal is accessed as `argv[N]`, the first character of which would be `argv[N][0]`. The memory holding the string literals should be regarded as read-only. (It is possible, and common, to declare `argc` and `argv` as `const`.)

* The string literal `argv[0]` is the name of the program as called when run, while `argv[argc]` is always a null pointer.

**Experiment**

* Run the program with no arguments. Is there any output? What is the value of `argc`?

* Now try multiple arguments inside double quotes (`"`). How are these handled?

* Now try options beginning with `-`, `--` or `/`. Could you construct a program which recognizes these as run-time option switches?

## The begin() and end() family

We have seen the traversal of an array by comparing a pointer against zero (as you will recall a string literal is a read-only zero-terminated array of `char`) using a `while` loop, and have iterated over an array using a `for` loop and index variable with array syntax, and have also used range-for. There is another way which does not require the use of a special sentinel value at the end of the array, nor a loop counter. It does, however, require the use of pointers and comparison of **addresses**. (In fact, this is how range-for operates "under the hood".)

The following program outputs a list of integers stored within an array:

```cpp
// 05-begin-end.cpp : demostration of the use of begin() and end()

#include <iostream>
using namespace std;

int main() {
    int numbers[] = { 3, 4, 1, 5, 6, 2 };
    for (auto p = begin(numbers); p != end(numbers); ++p) {
        cout << "- " << *p << '\n';
    }
}
```

A couple of things to note about this program:

* The `for`-loop is not range-for, however it almost reads like English.

* There is no loop counter, only the pointer `p`, which is dereferenced to provide a single element for output.

**Experiment**

* Change the type of `numbers[]` to double. Is this the only change needed? Add some fractional values to the array. Do they print out correctly? What does this tell you about the preservation of type information in pointers?

* Rewrite the `for`-loop without using `auto`, `begin()` or `end()`. Hint: don't change the body, and use `double*` in the initialization and `numbers + size(numbers)` in the condition test.

In fact, `begin()` and `end()` return pointer values for built-in arrays, these pointers actually contain the address of the first element and the address of "one past the last" element. When referencing arrays which are constant, `cbegin()` and `cend()` can be used, which return `const` pointers. The family is complemented with variants which access a "reversed" array.

The following table lists all eight members of the `begin()`/`end()` family, where `array[]` is the name of a built-in array with elements of any type, and `N` is `size(array)` (the number of elements). Note that `&array[N]` and `&array[-1]` **are** legal pointer values, but they must **never** be dereferenced.

|    Function name    | Index Syntax | Pointer Syntax  |
|:-------------------:|:------------:|:---------------:|
|  begin(), cbegin()  |   &array[0]  |    array        |
|    end(), cend()    |  &array[N]   | (array + N)     |
| rbegin(), crbegin() |  &array[N-1] | (array + N - 1) |
|   rend(), crend()   |  &array[-1]  |  (array - 1)    |

**Experiment**

* Print out `numbers[]` backwards. Is the use of `++p` still correct? Does this surprise you? Hint: use `rbegin()` and `rend()`.

* Now try to fill `numbers[]` with all `1`s. What error message do you get when using `cbegin()`/`cend()`?

* Now modify the program so that only the last element of the array is printed out, whatever size the array is.

*All text and program code &copy;2019-2024 Richard Spencer, all rights reserved.*
