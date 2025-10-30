# Templates, Exceptions, Lambdas, Smart Pointers

## Types as parameters

The use of the word *generics* usually implies two things: types as parameters and compiler-generated code. We have already met this concept without introducing it in detail; in the following definition, the type specified within angle-brackets is the *class template type parameter* for `std::vector`, which is used to describe the element type for the container:

```cpp
vector<double> vd;   // vd is an empty vector with its element type fixed
```

What is not necessarily apparent is that the Standard Library does not actually contain a *specialization* of `vector` for the element type `double`. The code required for the *instance* `std::vector<double>` is generated automatically by the compiler, and this code is then compiled. Whilst it is true that the type parameter is optional in some circumstances, it must still be able to be deduced somehow at compile-time in order for the *template* (the code for generic `std::vector`) to be *instantiated* (turned into compilable code) and then itself compiled:

```cpp
vector vi{ 0, 1, 2, 3, 4 };  // vi is actually a vector<int>, as deduced by the compiler
```

Note that the types of all the elements in the `std::initializer_list` used to create `vi` must be the same, so that this type can be deduced unambiguously.

Another way to understand generics is to compare them with other features that the language offers, such as function overloading. Consider a simple function called `average()` which returns the result of two `double`s (its two function parameters) added together and divided by two:

```cpp
double average(double a, double b) {
    return (a + b) / 2.0;
}
```

We can overload this function for `int`s without violating the ODR:

```cpp
int average(int a, int b) {
    return (a + b) / 2;
}
```

Notice that if we call `average()` with two `double`s, the return type is `double`. If we call it with two `int`s, the return type is `int`, possibly leading to rounding:

```cpp
auto a1 = average(3.5, 3.0);  // a1 is a double with value 3.25
auto a2 = average(3, 4);      // a2 is an int with value 3
```

This can become unwieldy if averages of many different types are required (a new function needs to be written out for each one), and is inflexible (there is no way to specify the return type; this is not part of the function signature and so cannot be used to select which overloaded function is to be called).

Let us rewrite `average()` as a function template (this code is probably not for production use as the Standard Library provides `std::midpoint`, although with this function the return type is always the same as for the parameters):

```cpp
template <typename T, typename U = double>
U average(const T& a, const T& b) {
    return (a + b) / U{ 2 };
}

auto a3 = average(3.5, 3.0);       // a3 is a double with value 3.25 (as for overloaded function)
auto a4 = average(3, 4);           // a4 is a double with value 3.5 (change from overloaded function)
auto a5 = average<int,int>(3, 4);  // a5 is an int with value 3 (as for overloaded function)
auto a6 = average<double>(3.5, 3); // a6 is a double with value 3.25 (as for overloaded function)
```

A couple of things to note about this syntax:

* The use of `int` or `double` as function parameter types is replaced by the *template type parameter* `T`; this can be deduced from the input parameter types. (Template type parameters are often named: `T`, `U`, or `V`, or sometimes `T1`, `T2`, and so on.)

* The use of `int`or `double` as the return type is replaced by the template parameter `U`, which defaults to type `double`; it does not need to be specified explicitly in the call to the template function.

* Both `a` and `b` **must** be of the same type unless the type is specified, otherwise the template specification is ambiguous. They are passed by `const`-reference in case they need to be used with (large, expensive to copy) user-defined types in the future (this type of usage should be anticipated when the generic form of the function is written).

* The calculation is very similar to those in the non-template versions, except for the *constructor syntax* `U{ 2 }`, which forces promotion to be applied to the division if `U` is of floating-point type.

## Variable, function and class templates

The simplest type of template is the variable, here is an example:

```cpp
template <typename T = long double>
constexpr T pi{ 3.1415926536897932385L };  // note: long double literals end with L

auto circ = pi<float> * 2.0f * 1.5f;  // circ is of type float
auto area = pi<double> * 1.5 * 1.5;   // area is of type double
auto pi2 = pi<> * 2.0L;               // pi2 is of type long double
```

Notice that triangular brackets are **always** necessary when dereferencing template variables (which may be empty if a default type is specified as it is here), however explicit narrowing casts are not needed. The specializations `pi<float>` and `pi<double>` are useful where automatic promotion of the floating-point type in an expression is not desired.

Template functions can be specified with one or more type parameters, as we have seen. Here is an example function `minimum()`, which returns the smallest of two values (production code could use `std::min` from the Standard Library):

```cpp
template <typename T>
T minimum(const T& a, const T& b) {
    return (a < b) ? a : b;
}

auto m1 = minimum(3, 2.5);        // Error! minimum<int> or minimum<double>?
auto m2 = minimum(-2, 1);         // m2 is an int with value -2
auto m3 = minimum(-5.5, -6.5);    // m3 is a double with value -6.5
auto m4 = minimum<double>(3.0, 4) // m4 is a double with value 3
```

Notice that we do not have to specify a type for `T` explicitly unless the deduction from the supplied arguments would be ambiguous (which is the case if the types of the two function arguments are different).

Template classes typically have one or more members of the template type. Here is an example class which holds a type `T` (as a member variable) and a `bool` (which indicates whether the value is valid).

```cpp
template <typename T = char>
class Opt {
    bool valid{ false };
    T value;
public:
    Opt() = default;
    Opt(const T& value) : value{ value }, valid{ true } {}
    Opt& operator= (const T& new_value) {
        value = new_value;
        valid = true;
        return *this;
    }
    bool hasValue() const {
        return valid;
    }
    const T& get() const {
        if (!valid) {
            throw;
        }
        else {
            return value;
        }
    }
};

auto o1 = Opt{ 1.2 };    // T = double, valid = true
auto o2 = Opt{ 3 };      // T = int, valid = true
auto o3 = Opt{};         // T = char, valid = false
auto o4 = Opt<size_t>{}; // T = size_t, valid = false
```

Some things to note about this program:

* A default type for `T` is required as we make use of a defaulted default-constructor; `char` was chosen as the smallest type (`void` may be in theory preferrable, but cannot be used as the compiler would encounter the construct `void value` when instantiating the class and produce an error).

* The other constructor matches `T` from the type of `value`, storing this in the member variable `value`, and also sets `valid` to `true`.

* The definition of `operator=` allows us to (re-)define a value (but not its type) that the `Opt` class will hold.

* Calling member function `hasValue()` is always safe, yielding a `bool`. Calling `get()` on an `Opt` with no value immediately terminates the program (the keyword `throw` is explained later in this Chapter).

Of course, this simple class is of limited practical use; if you need a type to be considered optionally valid without using a "special" value to indicate this, then making use of `std::optional<T>` from the Standard Library is recommended.

Member functions can be template functions, too. The following program defines a `Stringy` class with a `std::string` member, which can be initialized from another `std::string`, a `std::string_view` or a `const char *`:

```cpp
class Stringy {
    string str;
public:
    template <typename T> explicit Stringy(T&& str)
        : str{ str } {}
    string get() const { return str; }
};

Stringy sy1{ "Star" };       // initialize from const char *
Stringy sy2{ "Wars"s };      // initialize from std::string
Stringy sy3{ "Trilogy"sv };  // initialize from std::string_view
Stringy sy4{ 'V' };          // initialize from char
Stringy sy5{ 5 };            // Error! Attempt to narrow from int to char
```

Notice that the constructor (only) is defined with both `template` and `explicit`, meaning a new constructor is (attempted to be) generated when called with different types, and takes an r-value reference `T&&`. A function taking an r-value reference promises not to modify it; it can also be safely used with temporaries (such as `"Hello"s + " World"`) and is efficient as the temporary is not copied. (An optimization to use `std::move` when called with a `std::string` (only) r-value is a possiblilty here, however this would entail writing a second `explicit` constructor.)

## Standard exceptions, try, throw and catch

Exceptions are a means of altering program flow (at run-time) and *propagating* error conditions from a callee (sub-)function to its caller function (potentially as far back as `main()`, thus bypassing the usual function return mechanism). Program flow is interrupted at the point where an exception is *thrown*, and resumes at the point the exception is *caught*, which is always within the scope of a caller function (again, possibly `main()`, the beginning of the function call stack). Any code designed to handle an exception being thrown is contained within a *try-block*; this is a block of code enclosed in curly braces immediately after the `try` keyword. This try-block **is** allowed to make function/method calls, implicitly enclosing these within the try-block scope. (Any exceptions thrown from functions declared `noexcept`, or thrown from outside of a try-block's scope will terminate the program.)

An exception is thrown by using the `throw` keyword, followed by the object to be thrown. (If no object is specified then `std::terminate` is called, as for `noexcept` functions.) Usually, you will want to throw an instance of the `std::exception` hierarchy, although **any** user-defined or built-in type can be thrown.

An exception is caught by a catch-block immediately following the try-block and `catch` statement. There can be multiple consecutive catch-blocks and the order of these **is** significant; the first type-matching catch-block (in the case of a class hierarchy this is the base class) will be entered. The caught object should be named by reference (for example, `std::exception&`) and this becomes the *current exception*. The `throw` keyword by itself has a special meaning in the context of a catch-block, where it means to rethrow the current exception object further back down the function call stack.

The following program demonstrates use of the keywords `try`, `throw` and `catch`:

```cpp
// 10-throw1.cpp : simple exception demonstration, throw and catch

#include <iostream>
#include <exception>
using namespace std;

template <typename T>
void getInteger(T& value) {
    cout << "Please enter an integer (0 to throw): ";
    cin >> value;
    if (!value) {
        throw exception{};
    }
}

int main() {
    long long v{};
    try {
        getInteger(v);
    }
    catch (...) {
        cerr << "Caught exception!\n";
        return 1;
    }
    cout << "Got value: " << v << '\n';
}
```

Some new features of C++ introduced by this program:

* The `getInteger()` function prompts for an input `value`, and throws a `std::exception` if zero is entered.

* Due to the fact that it is a function template, the variable `value` is returned by a reference parameter, so that its type can be automatically deduced.

* Within `main()` the variable `v` must be defined outside the try-block as its value is needed after the end of the catch-block.

* The try-block has just one statement, the call to `getInteger()`. If an exception is thrown by this function it is caught by the catch-block which follows immediately.

* The catch-block begins with an ellipsis `(...)` meaning "catch any type". Without the `return` statement (which causes early exit from `main()`) control flow would fall through to the first line after the catch-block.

**Experiment:**

* Omit the line with the `return` statement in the catch-block. Does the program work as expected? Is the output a valid value?

* Now change the type of the function `getInteger()` to return `T` by **value**. What other change needs to be made?

* Try to catch the `std::exception` by **reference**, calling the variable `e`, **instead** of utilizing an ellipsis.

* Now experiment with by-value and by-pointer catching. Hint: the second of these will require `throw new ...`.

The Standard Library `std::exception` class is designed to be inherited from, and in fact the Standard Library includes an extensive class hierarchy with `std::exception` as the base class. Almost always, you will want any custom exception classes you derive to inherit from `std::exception`; this implies a constructor taking a `const char *` or `const std::string&` (**not** a `std::string_view`) which initializes a (`private:`) member which can be examined in the catch-block using the member function `what()`.

Catching exceptions by reference means that there is no possibility of *slicing*; this is where an object of derived class type is truncated to the size of its base class when passed/thrown by value. Catching by reference also means that there is no possiblity of a memory leak, as is the case with catching a pointer. There may be multiple catch-blocks following the try-block, each introducing its own scope, and the first (and only) one of these which matches the type thrown is entered. For this reason catch-blocks should be organized with the derived class(es) first; your compiler will probably warn you if a base class precedes a derived class in the catch-block order.

Exception support is useful even in small- to medium-sized projects, however two things need to be recognized: firstly, there is no way to return control flow back up the function stack to where the exception was originally thrown; and secondly, exception handling and use adds a significant performance overhead. In code required to be as fast as possible, exceptions should not be thrown and the functions should be declared with the `noexcept` keyword; this disables exception support, meaning that any use of `throw` simply calls `std::terminate`.

The following program defines a simple *event loop* which waits for user input and performs various actions:

```cpp
// 10-throw2.cpp : throw and catch exceptions from within and outside std::exception hierarchy

#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

int throwing() {
    cout << 1+R"(
Please choose:
1) throw std::runtime_error
2) throw std::exception
3) throw int
4) quit
Enter 1-4: )";
    int option;
    cin >> option;
    switch(option) {
    case 1:
        throw runtime_error{"std::runtime_error thrown"};
    case 2:
        throw exception{};
    case 3:
        throw 99;
    case 4:
        return 1;
    default:
        cout << "Error: unrecognized option\n";
    }
    return 0;
}

int main() {
    for (;;) {
        int action{};
        try {
            action = throwing();
        }
        catch (runtime_error& e) {
            cerr << "Caught std::runtime_error! (" << e.what() << ")\n";
        }
        catch (exception& e) {
            cerr << "Caught std::exception!\n";
        }
        catch (...) {
            cerr << "Caught something other than std::exception! Quitting.\n";
            return 1;
        }
        if (action) {
            break;
        }
    }
}
```

A few new things to note about this program:

* The function `throwing()` always returns control to `main()` from all paths whatever the user inputs.

* It works by throwing a `std::runtime_error` (which is derived from `std::exception`), throwing a plain `std::exception`, throwing an `int` or returning an `int`.

* There is no need for `break` statements within the `switch` as no `case:` conditions can fall through (except for `default:`, which never needs `break` as it should be the final clause).

* The order of the catch-blocks is significant, with ellipsis last and (derived class) `std::runtime_error` first.

**Experiment:**

* Modify `main()` so that it returns to the environment the value thrown as `int`.

* Create a class type derived from `std::runtime_error` called `FatalError`; it should have an `int` as a `public:` data member which is the value returned to the environment from `main()` when a `FatalError` is caught there. Write a suitable catch-block in the correct place, and modify the function `throwing()`.

* Now make the `int` a `private:` data member, and utilize a getter function called `getRC()`.

## Function objects

It is possible to overload the *function call operator* `operator()` for `struct`s and `class`es; this enables objects created from them to masquerade as functions. Sometimes these objects are called *functors*; essentially this means that they are *callable* in the same sense as free functions, member functions and *lambdas* (which are discussed later in this Chapter). The term functor can be used to describe both the `struct` or `class` definition and the instance objects it creates.

The following program demonstrates overloading `operator()` (it is also possible to overload on several different parameter types, if needed):

```cpp
// 10-functor1.cpp : simple function object demonstration

#include <iostream>
using namespace std;

struct Average {
    int operator()(int a, int b) {
        cout << "Calculating average...\n";
        return (a + b) / 2;
    }
};

int main() {
    Average a;
    cout << "Please enter two integers:\n";
    int x{}, y{};
    cin >> x >> y;
    auto avg = a(x, y);
    cout << "The average is: " << avg << '\n';
}
```

**Experiment:**

* Define another functor which calculates the average of two `double`s, giving it a different name.

* Move these functor definitions to within `main()`. Does the code still compile?

More usefully, functors can store state in data members, preserving it between (object-as-function) calls. The following program shows a function object definition which can calculate the (running) minimum, maximum and average of a `std::vector<int>`; in fact any container type for which `begin()` and `end()` are defined could be used:

```cpp
// 10-functor2.cpp : function object maintaining state

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct MinMaxAvg {
    void operator()(int i) {
        if (first) {
            min = max = avg = i;
            first = false;
            return;
        }
        if (i < min) {
            min = i;
        }
        if (i > max) {
            max = i;
        }
        avg = ((avg * num) + i) / (num + 1);
        ++num;
    }
    int min, max, num{ 1 };
    double avg;
    bool first{ true };
};

int main() {
    vector v{ 3, 5, 2, 6, 2, 4 };
    MinMaxAvg f = for_each(begin(v), end(v), MinMaxAvg{});
    cout << "Min: " << f.min << " Max: " << f.max
      << " Avg: " << f.avg << " Num: " << f.num << '\n';
}
```

A few points to note about this program:

* Only `num` and `first` are required to be set before the `std::for_each()` call; we have used universal initialization of the member variables, but this could also be achieved by using a (default-)constructor.

* The assignment of `f` (a `MinMaxAvg` function object) is the result of the call to `std::for_each()`, being the modified (default-constructed) third parameter.

* The function template `std::for_each()` call decomposes to the equivalent of: `auto f = MinMaxAvg{}; f(3); f(5); f(2); f(6); f(2); f(4);`. Of course, a range-for loop could be used to accomplish the same thing, but the *logic* within the functor's `operator()` would have to be written (or repeated) within the body of the loop.

**Experiment:**

* Replace `vector` with `auto`. Does the code still compile? What type is `v`?

* Replace `auto v` with `const int v[] =`. Does the code still compile now?

* Turn this functor into a template which can be instantiated with different types for `min`/`max` and `avg`.

## Lambdas

A *lambda* (or sometimes "lambda function"), is a callable entitiy which works much like a free function, whilst having some of the properties of a local variable. Unlike a `constexpr` function it can access global state, such as `cout`. Unlike free functions, they can access (or *capture*) variables from within the scope they are called from. Lambdas do have a lot in common with functors; in fact, compilers will implement lambdas by using a functor "behind the scenes". Interestingly, it has been said that if you fully understand C++ lambdas, you also understand much of C++, so knowledge of them is very useful.

Lambda expressions begin with an opening square bracket `[` (in a different context to array syntax), while the body of the lambda is enclosed within curly braces, as for a regular function. An **optional** parameter list enclosed in parentheses goes between the closing square bracket and the opening curly brace. The minimalist lamda is therefore simply `[]{}`. (The return type being `void` in this case is implicit.)

The following program demonstrates a very simple lambda:

```cpp
// 10-lambda1.cpp : simple lambda which produces output

#include <iostream>
using namespace std;

int main() {
    auto l = []{ cout << "Lambda says Hi!\n"; };
    
    l();
}
```

A few points to note:

* Lambdas can be assigned to variables, in this case the variable `l`. (Actually, other types of function can be assigned to variables too, using the `&` address-of operator.)

* The type of the lambda reflects its function signature (the combination of its parameter and return types). Rather than try to determine this manually, the use of `auto` here is almost universal.

* A semi-colon is necessary after both statement(s) in the body of the lambda **and** after the closing curly brace of the body (as with a `struct` or `class` definition).

* Lambdas can be easily identified where the sequence `= [` occurs, which is different (to both compilers and humans) from array subscript syntax.

* A lambda is *invoked* by stating its name with (possibly empty) parentheses and a semi-colon, with exactly the same semantics as a free function call.

**Experiment:**

* Add an empty parameter list between the closing square bracket and opening curly brace of the lambda definition. Does the program still compile?

* Omit the line `l();` and try to compile the program. What is its output now?

* Define and assign `l` on separate lines, omitting the use of `auto`. Hint: there are at least four ways of doing this, some more tricky than others; they involve using: `typedef`, `using`, `std::function` or `decltype`. You may need to do some research.

The following program calls its lambda with a parameter, altering its output:

```cpp
// 10-lambda2.cpp : another simple lambda which produces output

#include <iostream>
#include <string_view>
using namespace std;

int main() {
    auto l = [](string_view s){ cout << "Lambda says " << s << '\n'; };
    
    l("Hola");
}
```

A couple of things to note about this program:

* The parameter list is non-empty and takes the same format as that of a regular free or member function.

* Parameters can be accepted by value or reference.

* The match between argument `"Hola"` and parameter `string_view s` is performed at compile-time.

**Experiment:**

* Change the program to accept `s` by reference. What other (small) change needs to be made?

* Change the program so `l` is called with run-time user input.

* Try to implement this lambda as a functor.

* Change `string_view` to `auto`. Does the program still compile? What is the type of `s` now?

* Try to implement this new version of the lambda as a functor. (Hint: you will need to use template syntax to do this properly.) Experiment with both this functor and the lambda version using different literal types (not just string-like types).

Lambdas can return a value in the same way as for free and member functions; the type of this value is deduced from the `return` statement(s) in the body of the lambda. (Lambdas **can** have more than one flow and return path, but all `return` statements must have the same type.) When defining the lambda after an `auto` keyword, no change needs to be made in order to specify that the lambda returns a value.

The following program implements a lambda which returns the average of two numbers:

```cpp
// 10-lambda3.cpp : lambda function which calculates average of two values

#include <iostream>
using namespace std;

int main() {
    auto l = [](int a, int b) {
        cout << "Calculating average...\n";
        return (a + b) / 2;
    };

    cout << "Please enter two integers:\n";
    int x{}, y{};
    cin >> x >> y;
    auto avg = l(x, y);
    cout << "The average is: " << avg << '\n';
}
```

A few things to note about this program:

* This program is essentially an adaptation of `10-functor1.cpp`; it may be valuable to review these two programs side-by-side.

* The lambda `l` is defined over multiple lines; whitespace conventions for doing this vary, however the closing curly brace and semi-colon are often on a line by themselves

* The return type of `l(x, y);` is stored in the variable `avg` which is declared `auto`. It is important to recognize that this usage is different from that of `l`, also being declared `auto`.

**Experiment:**

* Change the lambda calculation to `/ 2.0`. Which variable has its type changed as a result?

* Instead, change the parameter list in the lambda to declare `a` and `b` as `auto`. Does this alter the behavior of the program when the average would be fractional?

* Now change the type definition of `x` and `y` to `double`. Experiment with integer and fractional numbers and results. Hint: you should also change the `cout` message. What does this tell you about *generic lambdas* such as this?

All of the lambdas introduced so far have been *stateless lambdas*. Whilst not necessarily pure functions (they can modify global state), they have only been able to operate on the parameters passed in. They have also only been able to return a single entity (although this could usefully be a `std::pair`, `std::tuple` or `struct`).

It is possible to enable lambdas to read from and write to variables in the (immediately) enclosing scope; this is the scope of the function in which the lambda is defined. Two things worthy of note stem from this: firstly, variables captured in this way are analogous to member variables of a functor, and secondly, the scope in which a lambda is defined is not necessarily the same as the one in which it is called. Care must be taken when capturing variables by reference not to cause dangling references; the captured variable must not have passed out of scope when the lambda is invoked.

The following program revisits the second functor example, calculating the minimum, maximum and mean average of the elements in a container:

```cpp
// 10-lambda4.cpp : lambda accessing scoped variables by value and reference

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector v{ 3, 5, 2, 6, 2, 4 };
    int min, max, num{ 1 };
    double avg;
    bool first{ true };
    
    auto l = [&](int i) {
        if (first) {
            min = max = avg = i;
            first = false;
            return;
        }
        if (i < min) {
            min = i;
        }
        if (i > max) {
            max = i;
        }
        avg = ((avg * num) + i) / (num + 1);
        ++num;
    };

    for_each(begin(v), end(v), l);
    cout << "Min: " << min << " Max: " << max
      << " Avg: " << avg << " Num: " << num << '\n';
}
```

A few important things to note about this program:

* This program is essentially an adaptation of `10-functor2.cpp`; it may be valuable to review these two programs side-by-side.

* The former member variables of the functor have been defined before the lambda in the same scope as the container.

* The ampersand inside the square brackets before the lambdas parameter list (`[&]`) indicates by-reference capture, which in this case means that all the variables in the scope of `main()` are accessible within the body of the lambda. (This includes `v` but since no copy is made this does not harm performance. It is possible to specify exactly which variables to capture, using a *capture list* `[&min,&max,&num,&avg,&first]` in order to avoid capturing `v`.)

* The body of the lambda and its parameter list are both the same as for the overloaded `operator()` of the functor.

* The lambda object `l` can be passed into `for_each()` by value (`std::ref` is not needed).

* The variables `min`, `max`, `avg` and `num` can be accessed directly after the lambda has modified them.

**Experiment:**

* Change the parameter list of the lambda to accept a variable declared `auto`. Does the program still compile and run?

* Change the types of `min` and `max` to double, along with the elements assigned to `v`.

* Change the capture to by-value (`[=]`). Does the program compile now?

* Change the capture to be empty. What error messages do you get?

* Define and assign to a second `std::vector` named `v2`. What other changes need to be made to the program in order to be able to call `std::for_each()` again for `v2`?

## Smart pointers

Smart pointers are entities which bind heap objects to scoped lifetimes. The advantage over using "plain" (or "naked") `new`/`delete` is that all return paths from a function or sub-scope are automatically covered, even if an exception is thrown. There are three C++ smart pointer classes, they are: `std::unique_ptr`, `std::shared_ptr` and `std::weak_ptr`.

The simplest smart pointer is `std::unique_ptr` which encapsulates the most common functionality associated with a raw pointer, that is *exclusive ownership*. The following program, which does not delete `p2` if called with arguments, demonstrates its use:

```cpp
// 10-smartptr1.cpp : use of unique_ptr

#include <iostream>
#include <string>
#include <string_view>
#include <memory>
using namespace std;

class Simple {
    string str;
public:
    Simple(string_view s) : str{s}
    { cout << "Simple(): " << str << '\n'; }
    ~Simple()
    { cout << "~Simple(): " << str << '\n'; }
};

int main(int argc, const char *argv[]) {
    unique_ptr<Simple> p1{ new Simple("p1") };
    Simple *p2 = new Simple("p2");
    {
        auto p3 = make_unique<Simple>("p3");
        if (argc > 1) {
            return 1;
        }
        delete p2;
        p2 = nullptr;
    }
}
```

A few things to note about this program:

* A `std::unique_ptr` is initialized with a pointer to a heap object. The pointer type needs to be provided in case it needs to be a (different) base class type, such as a `std::unique_ptr<Shape>` initialized with a `new Triangle()`.

* This initialization has a direct analogy with initialization of raw pointers.

* An alternative way to create a `std::unique_ptr` is by using the helper function `std::make_unique` as used to create `p3`. This is the preferred way in many cases due to its exception safety, so you will find this in code.

* A `std::unique_ptr` created within a sub-scope is destroyed at the end of the sub-scope. Otherwise, as with all stack objects, they are destroyed in the reverse order in which they were created.

**Experiment:**

* Modify the above program so that `p2` is always deleted, regardless of the value of `argc`. Hint: keep it as a raw pointer.

* Now modify the program so that a `std::exception` is thrown if `argc > 1`. Are the destructors called?

* Modify the program `09-shape.cpp` to use a `vector<unique_ptr<Shape>>`, making any other necessary changes.

It is possible to specify *custom deleters* for `std::unique_ptr`s; which can be any callable object which encapsulates the correct behavior to destroy the object. The following example demonstrates this for a `FILE*` (in case you didn't know, the C library functions `fopen()` and `fclose()` return and accept a `FILE*` pointer):

```cpp
// 10-smartptr2.cpp : encapsulate a FILE* in a unique_ptr

#include <iostream>
#include <cstdio>
#include <memory>
using namespace std;

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cerr << "Syntax: " << argv[0] << " <filename>\n";
        return 1;
    }

    unique_ptr<FILE,decltype(&fclose)> fp{ fopen(argv[1], "rb"), fclose };

    if (fp) {
        int c;
        while ((c = fgetc(fp.get())) != EOF) {
            putchar(c);
        }
    }
}
```

A couple of things to note about this program:

* Here `std::make_unique` cannot be used, nor can the type of the `std::unique_ptr` be deduced automatically. Also, we have to specify the type of the deleter explicitly: `decltype(&fclose)` provides us with a function pointer type.

* The member function `get()` is used to access the raw pointer needed for the call to the C Library function `fgetc()`.

The member function `reset()` changes the object owned by the `std::unique_ptr`; calling `reset(nullptr)` releases and destroys the object early. Also, `std::unique_ptr`s cannot be copied as this would make no semantic sense (a deep copy cannot be initiated by a pointer-to-object, and a shallow copy would mean either shared ownership or dangling pointers). They can however be moved, either explicitly using `std::move` or as a return value from a function (they are very useful as return types for factory functions).

The next smart pointer type is `std::shared_ptr`; this allows an object to become *reference counted* and only deletes it when the **last** pointer referring to it goes out of scope. The following program creates a `Simple` object in a sub-scope, yet destroys it in an outer scope:

```cpp
// 10-smartptr3.cpp : use of shared_ptr

#include <memory>
#include <iostream>
using namespace std;

class Simple {
    string str;
public:
    Simple(string_view s) : str{s}
    { cout << "Simple(): " << str << '\n'; }
    ~Simple()
    { cout << "~Simple(): " << str << '\n'; }
};

int main() {
    cout << "main(): 1\n";
    shared_ptr<Simple> p1{ new Simple("p1") };
    cout << "main(): 2\n";
    {
        cout << "main(): 3\n";
        auto p2 = make_shared<Simple>("p2");
        cout << "main(): 4\n";
        p1 = p2;
        cout << "main(): 5\n";
    }
    cout << "main(): 6\n";
}
```

A few things to note about this program:

* Every other statement in `main()` produces output, so the exact workings of `std::shared_ptr` are demonstrated.

* The use of `std::make_shared` is shown as an alternative to using a raw pointer to initialize a `std::shared_ptr`.

* Firstly, `p1` is created in the scope of `main()`.

* Secondly, `p2` is created in a sub-scope.

* Thirdly, `p2` is assigned to `p1`, thus object `"p1"` is deleted. Also, the scope of `p2` is **extended** from the sub-scope to that of `main()`.

* Then, the sub-scope exits, destroying `p2`, however the object it points to says alive becuase `p1` points to it.

* Finally, `main()` exits, destroying `p1` and `p2`. Thus `"p1"` and `"p2"` are destroyed in the **same** order in which they were initialized, unlike for `std::unique_ptr` where it would always be in reverse order.

Any `std::shared_ptr` object can be passed by **value** to a function, implying a copy of the `std::shared_ptr` and a sharing of ownership. Also a container of `std::shared_ptr`s can share ownership with named `std::shared_ptr`s, or even another container of `std::shared_ptr`s.

Some programming tasks involve use of pointers, often in containers, where the pointee needs to point back to the pointer. Use of `std::shared_ptr` may be unsuitable in this case becuase of the *dependency cycle* created. The key symptom of this is objects not being deleted within the lifetime of the program because the reference count cannot drop to zero for either the pointer or pointee. An example of subtly incorrect code is shown in the program fragment below:

```cpp
struct Pupil;    // forward declaration to allow shared_ptr<Pupil> in definition of Class

struct Class {
    int room;
    string subject, teacher_name;
    vector<shared_ptr<Pupil>> pupils;
};

struct Pupil {
    string name;
    vector<shared_ptr<Class>> subjects; // compiles but is incorrect!
};

vector<shared_ptr<Class>> AllClasses;
vector<shared_ptr<Pupil>> AllPupils;
```

This code will probably compile without a warning being issued, and `Class` and `Pupil` objects can be created and made to point to each other. However, when the containers `AllClasses` and `AllPupils` are destroyed or go out of scope, this does not cause the destructors of the `Class` and `Pupil` objects to be called correctly; this is caused by the semantics being wrong as a `Class` **cannot** "own" its `Pupil`s if the `Pupil`s **also** "own" the `Class`. Luckily there is a third smart pointer type `std::weak_ptr`, a non-owning smart pointer which can be initialized from a `std::shared_ptr`. A `std::weak_ptr` cannot be derefenced directly, but has a member function `lock()` which returns a suitable `std::shared_ptr` (within the scope of the call to `lock()`) which **can** be dereferenced. The change to the code is simple (assuming that `Class` is desired to own its `Pupil`s, rather than the other way about), and is shown below:

```cpp
struct Pupil {
    string name;
    vector<weak_ptr<Class>> subjects;
};
```

The corrected sample code is replicated in the complete program shown below; lambdas have been shown (instead of `friend` or `static` member functions) as ways to create and manipulate the `Class` and `Pupil` types, thus the program has only two global `struct` definitions and a fairly large `main()` function:

```cpp
// 10-pupils.cpp : use of shared_ptr and weak_ptr to avoid dependency cycle

#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string_view>
using namespace std;

struct Pupil;

struct Class {
    Class(int r, string_view s, string_view t)
        : room{ r }, subject{ s }, teacher_name{ t } {}
    int room;
    string subject, teacher_name;
    vector<shared_ptr<Pupil>> pupils;
};

struct Pupil {
    Pupil(string_view n) : name{ n } {}
    string name;
    vector<weak_ptr<Class>> classes;
};

int main() {
    vector<shared_ptr<Class>> AllClasses{
        make_shared<Class>(101, "English", "Mr White"),
        make_shared<Class>(150, "Math", "Miss Black")
    };
    vector<shared_ptr<Pupil>> AllPupils{
        make_shared<Pupil>("Paul"),
        make_shared<Pupil>("Percy"),
        make_shared<Pupil>("Perry"),
        make_shared<Pupil>("Phoebe"),
        make_shared<Pupil>("Penny"),
        make_shared<Pupil>("Patricia")
    };

    auto add_to_class = [&](string_view c, string_view p) {
        auto iter_c = find_if(cbegin(AllClasses), cend(AllClasses),
            [&](auto ec){ return c == ec->subject; });
        auto iter_p = find_if(cbegin(AllPupils), cend(AllPupils),
            [&](auto ep){ return p == ep->name; });
        if (iter_c != cend(AllClasses) && iter_p != cend(AllPupils)) {
            (*iter_c)->pupils.push_back(*iter_p);
            (*iter_p)->classes.push_back(*iter_c);
        }
        else {
            cerr << "Could not add " << p << " to " << c << '\n';
        }
    };

    add_to_class("English", "Paul");
    add_to_class("English", "Percy");
    add_to_class("English", "Phoebe");
    add_to_class("English", "Penny");
    add_to_class("Math", "Paul");
    add_to_class("Math", "Perry");
    add_to_class("Math", "Phoebe");
    add_to_class("Math", "Patricia");

    AllClasses.emplace_back(make_shared<Class>(260, "IT", "Mrs Brown"));
    add_to_class("IT", "Percy");
    add_to_class("IT", "Perry");

    for (const auto& c : AllClasses) {
        cout << "Room: " << c->room << "\nSubject: " << c->subject
            << "\nTeacher: " << c->teacher_name << "\nPupils: ";
        for (const auto& p : c->pupils) {
            cout << p->name << ' ';
        }
        cout << '\n';
    }
    
    for (;;) {
        cout << "Please enter a pupil name (blank line to quit): ";
        string s;
        getline(cin, s);
        if (s.empty()) {
            break;
        }
        auto iter_p = find_if(cbegin(AllPupils), cend(AllPupils),
            [&](auto ep){ return s == ep->name; });
        if (iter_p != cend(AllPupils)) {
            cout << "Classes: ";
            for (const auto& c : (*iter_p)->classes) {
                if (auto pc = c.lock(); pc) {
                    cout << pc->subject << ' ';
                }
            }
            cout << '\n';
        }
        else {
            cout << "Name not recognized!\n";
        }
    }
}
```

This is one of the larger programs we have seen, and covers much of the contents of this Chapter:

* Due to the fact that a `std::vector` of `std::shared_ptr` is used, a factory function needs to be used to generate the elements for `AllClasses` and `AllPupils`. The function template `std::make_shared` (introduced in `10-smartp3.cpp`) is used, which forwards its arguments to the constructor for the type specified within the angle brakets.

* The Standard Library `std::find` cannot easily be used to search for a matching `std::shared_ptr` element, so `std::find_if` is used (twice) instead in the lambda function `add_to_class()`. This lambda needs to capture `AllClasses` and `AllPupils` by reference, and iterates through these with a *predicate* lambda that returns a `bool`. It is worthwhile becoming familiar with this syntax, `std::find()` was used in Chapter 7.

* The variables `iter_c` and `iter_p` assume value `cend(AllClasses)` and `cend(AllPupils)` respectively if neither the predicates return `true`. Either of these causes the lambda `add_to_class()` to return early.

* The linking of the elements of `AllClasses` and `AllPupils` is done by dereferencing `iter_c` and `iter_p` to produce a `std::shared_ptr` in each case. These are then dereferenced to obtain the container data members `pupils` and `classes` respectively, which are invoked with `push_back()`.

* A range-for loop cycles through `AllClasses` printing out all of the `Class`es and their `Pupil`s.

* The last interactive part of the program accepts a `Pupil` name and cycles through the data member `classes` (a `std::vector` of `std::weak_ptr`s). A `std::shared_ptr` to each `Class` is obtained via the `lock()` member function of each `std::weak_ptr`. The syntax may be slightly tricky to follow, but does not contain anything not seen before.

**Experiment:**

* Add some more classes and pupils to the program, and check that they are associated correctly. Experiment with `AllPupils.push_back()` and `AllClasses.push_back()`, as well as removing (using `find()` and `erase()`) from these containers.

* Add a destructor to `Class` and `Pupil` which produces some output. Ensure that **all** objects in the program are correctly deleted.

* Change the lambda captures from `[&]` to specify exactly which variables to capture. Experiment with by-reference and by-value capture for each variable.

* Rewrite the program to use a member function `add_to_class()` instead of a lambda. This should be a member of `Pupil` and take a reference parameter of `std::shared_ptr<Class>`. You will also need to find a way for this function to access `AllClasses` and `AllPupils`, as well as a way of identifying an element of `AllPupils` by name within `main()`. (Hint: a `static` data member as a *class variable* may be useful here.)

* Make it impossible to add the same pupil to the same class twice.

* Change `Pupil` and `Class` to be `class`es instead of `struct`s, with `private:` data members. Hint: you will need to write some `public:` getters.

*All text and program code &copy;2019-2025 Richard Spencer, all rights reserved.*
