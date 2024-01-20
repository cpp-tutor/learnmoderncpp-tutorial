# Enums and Structs

## Enumerations

Some variables belong to a small, defined set; that is they can have exactly one of a list of values. The `enum` type and its closely related `enum class` type each define a set of (integer) values which a variable is permitted to have.

Think of a complete pack of playing cards: each card has a suit and rank. Considering the rank first of all, this is how it can be represented and defined:

```cpp
enum Rank : unsigned short { ace = 1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, none = 99 };
```

The name of this type is `Rank`, by convention for a user-defined type this is in *SentenceCase*. Following the colon `:` is the *underlying type*; this **must** be a built-in integer type (`char` is also allowed) and defaults to `int` if not specified. Since we have specified `unsigned short` we can assign values from `0` to `65535` (most likely, however strictly speaking this is implementation dependent). Then, within curly braces are a list of comma-separated *enumerators*, each of which can optionally have values specified. We have set `ace = 1` instead of relying on the default value of zero for the first enumerator because it allows the internal value and representation to be the same. Subsequent enumerators take the next available value.

A variable of type `enum` (also known as *plain* enum), such as `Rank` above, can be initialized from any of the enumerators listed in its definition. However, care should be taken not to assign values not in its enumeration set; this includes default-initialization if zero is not one of the enumerators:

```cpp
Rank r1{ ace };     // ok, r1 is value of enumeration constant ace (1)
Rank r2{};          // possible problem, r2 has value zero which is not in enumeration set
Rank r3;            // worse, r3 has "random" (uninitialized) value
Rank r4{ 15 };      // possible problem, r4 has a value not within enumeration set
auto r5 = king;     // ok, r5 is of type Rank (not unsigned short)
int i = seven;      // ok, implicit conversion to integral type
```

It may be surprising to discover that in most ways `ace`, `two`, `three`, `four` and so on are just "normal" integer constant values. (Indeed in some historical versions of the C language, the only way to define constants was by using anonymous `enum`s; this curiosity was given the affectionate name of the "enum hack".) Thus variables of type `enum` can "borrow" enumerators from different types of `enum`s! Even worse, enumerators from different `enum` definitions in the same scope could **not** use the same name without causing a name collision.

To address these limitations the C++ `enum class` type was created; this type is also known as *scoped* or *strongly typed* enumeration. We can represent the suit of a card using this type:

```cpp
enum class Suit : char { spades = 'S', clubs = 'C', hearts = 'H', diamonds = 'D', none = '\?' };
```

The difference in syntax is small, we have `enum class Suit` compared to `enum Rank`, although this time the underlying type is `char` and character literals are used for the enumerators. However the `none` in `Suit` does not clash with `none` in `Rank`, and related to this feature the enumerators in an `enum class` have to be qualified with the type name, as follows:

```cpp
Suit s1 = Suit::hearts;     // good, types match
Suit s2{};                  // possible problem, s2 has value zero (NUL-byte)
Suit s3{ 'S' };             // ok, perhaps surprisingly
auto s4 = Suit::diamonds;   // s4 is of type Suit
char c = Suit::none;        // error: no implicit conversion to underlying type, static_cast needed
```

**Experiment:**

* Write a program to populate a 13-element array of `Rank` with element `[0]` taking `ace`. Cause it to print this array in reverse order.

* Write a function which outputs one of `Spades`, `Clubs`, `Hearts` or `Diamonds` based on its single parameter of type `Suit`.

## Member variables

Of course, in the context of a pack of playing cards it is not practical to think of "suit" and "rank" as separate entities: each playing card has both. The term *composite types* is used to describe objects composed from other types (either built-in or user-defined). The following `struct` definition is an example of a composite type, containing two fields (also called *member variables*) using the `enum` and `enum class` types already introduced:

```cpp
struct PlayingCard {
    Rank r;
    Suit s;
};
```

This `struct` type is named `PlayingCard`, again using sentence case. The fields of the `struct` are listed between braces like variable definitions, type-then-name, separated by semi-colons; there is also a **mandatory** semi-colon after the closing brace. The order of the fields is not usually significant; we have put `Rank` first as it is a 16-bit value compared to `Suit` being 8-bit, which makes the `struct`'s logical memory layout more sensible. (There is probably no gap between the fields in memory layout in this case, but `PlayingCard` is probably padded out to 32-bits at the end.) Also, this layout matches the usual order of the description of a card, such as "Three of Clubs".

Instances (variables) of type `PlayingCard` are examples of what are often called *objects* (as in *Object Oriented Progamming*, or *OOP*), and they can be defined and initialized in a similar way to containers using uniform initialization syntax. The code below demonstrates how to create the first card in the pack, and how to extract the object's fields back into separate variables:

```cpp
PlayingCard ace_of_spades{ ace, Suit::spades };

auto the_rank1 = ace_of_spades.r;               // the_rank1 = ace, and is of type Rank
auto the_suit1 = ace_of_spades.s;               // the_suit1 = Suit::spades, and is of type Suit

auto [ the_rank2, the_suit2 ] = ace_of_spades;  // the_rank2 = ace, the_suit2 = Suit::spades
```

The variables `the_rank1` and `the_suit1` are initialized from the individual fields of `ace_of_spades` separately using *dot-notation*, while `the_rank2` and `the_suit2` are initialized using *aggregate initialization* syntax.

**Experiment:**

* Put the definitions of `Rank`, `Suit` and `PlayingCard` into the same source file, together with a `main()` program which defines `ace_of_spades` as shown above. Does the order of the `enum` and `struct` definitions matter?

* What error message do you get if you swap `ace` and `Suit::spades` over in the definition of `ace_of_spades`. Would this error be easy to catch if plain `int` values were used instead of typed enumerators?

It may be desirable to create `struct`s with multiple fields of the same type. An example of this is a simple two-dimensional `Point` class with fields called `x` and `y`, both being signed integers:

```cpp
struct Point {
    int x{}, y{};
};

Point p1{ 2, 3 };
```

As the field variables are of the same type they can be defined together, separated by a comma. The empty braces `{}` mean the same thing as for `int` variable definitions, `x` and `y` will get the default value of the this type, being zero.

A question you may ask is: "Why not simply use a two-element array type?", such as:

```cpp
using PointA = int[2];

PointA p2{ 4, 5 };
```

It's a valid question, and at the machine level produces (most likely) similar code. In this case using a `struct` has the edge because it default-initializes, and having fields called `p1.x` and `p1.y` is more intuitive and less error-prone than having to use subscripting syntax `p2[0]` and `p2[1]`.

**Experiment:**

* Write a program to obtain the two fields of a previously defined `Point` object from `cin`. Don't use any temporary variables.

* Modify this program to manipulate these fields in some way (such as multiplying them by two) and output them.

* Write a function called `mirror_point()` which reflects its input (of type `Point`) in both the x- and y-axes. Experiment with passing by value and `const`-reference (and returning the modified `Point`), and by reference and by pointer (two different `void` functions). Hint: for the last variant pass an address of `Point` and access the fields with `p->x` and `p->y`, and see Chapter 4: [Parameters by value](https://learnmoderncpp.com/functions#topic-2) and [Parameters by reference](https://learnmoderncpp.com/functions#topic-3) for a refresher. Compare all four versions of this function for ease of comprehension and maintainability.

## Inheritance vs composition

We have talked about composite types being made up of other types, and in fact types can be *composed* (nested) indefinitely, although many programmers would struggle to comprehend more than a few levels. The other way to create new types with characteristics of previously defined types is through *inheritance*, which is a key concept of OOP.

The following program defines an `enum class` called `Color` (feel free to add more color enumerators) and uses the same `Point` class to create a new `Pixel` class, which has both a location and a color being composed of both `Point` and `Color` fields.

```cpp
// 06-pixel1.cpp : Color and position Pixel type through composition

#include <iostream>
#include <string_view>
using namespace std;

struct Point {
    int x{}, y{};
};

enum class Color { red, green, blue };

struct Pixel {
    Point pt;
    Color col{};
};

string_view get_color(Color c) {
    switch (c) {
        case Color::red:
            return "red";
        case Color::green:
            return "green";
        case Color::blue:
            return "blue";
        default:
            return "<no color>";
    }
}

int main() {
    Pixel p1;
    cout << "Pixel p1 has color " << get_color(p1.col);
    cout << " and co-ordinates " << p1.pt.x;
    cout << ',' << p1.pt.y << '\n';

    Pixel p2{ { -1, 2 }, Color::blue };
    cout << "Pixel p2 has color " << get_color(p2.col);
    cout << " and co-ordinates " << p2.pt.x;
    cout << ',' << p2.pt.y << '\n';
}
```

Most, if not all, of the syntax should be familiar, however a few things to note:

* `Point` and `Color` must be defined before `Pixel`, as the fields of `Pixel` are variables of these two types.

* Inside `Point`, `x` and `y` are default-initialized (to zero). This means that in `Pixel`, `pt` has aleady automatically default-initialized, while `col` has to be initialized explicitly.

* The function `get_color()` uses a `Color` as the `switch`-variable, this is permitted because `enum` and `enum class` always have an integer as the underlying type.

* This function returns a `std::string_view`, although `std::string` or `const char *` would work equally well. The data that the `std::string_view` refers to is guaranteed to outlive the scope of the function `get_color()` because they are read-only string literals; no copy is ever made. (The type `std::string_view` is covered in more detail in Chapter 7.)

* In `main()` the variable `p1` is default-initialized to `Color::red` and `0,0` becuase of the default-initialization syntax in the `struct` definitions. The member variable `p1.col` is `red` because that is the enumeration with value zero (from default initlalization with `{}`).

* The variable `p2` is set to `Color::blue` explicitly at initialization, with the co-ordinates `-1,2` using nested initializer syntax.

* The member variables `x` and `y` are members of `Point`, `pt` is a member of `Pixel`, so the full names of `p2`'s two co-ordinates are `p2.pt.x` and `p2.pt.y`. This ahows how the member operator `.` can be chained in this way (it works for member functions, too), and operations remain fully type-safe.

**Experiment:**

* Write a function `get_pixel()` which returns information about a `Pixel`, and remove the code duplication in calls to `cout` from `main()`. Hint: the return type should be `std::string` and it should call `get_color()`; the code in `main()` should read: `cout << get_pixel(p1) << '\n';`

* Can you call `get_pixel()` from `main()` with a third `Pixel`, without using a named variable? Hint: try to use initializer syntax in the function call.

* Change the default `Color` assigned to `p1` to be `<no color>`. Hint: this is a simple change.

The next program accomplishes exactly the same as the previous one, producing the same output, and most likely very similar code of comparable efficiency. However it use *inheritance* instead of composition, which is indicated by a slightly different definition of `Pixel`:

```cpp
// 06-pixel2.cpp : Color and position Pixel type through inheritance

#include <iostream>
#include <string_view>
using namespace std;

struct Point {
    int x{}, y{};
};

enum class Color { red, green, blue };

struct Pixel : Point {
    Color col{};
};

string_view get_color(Color c) {
    switch (c) {
        case Color::red:
            return "red";
        case Color::green:
            return "green";
        case Color::blue:
            return "blue";
        default:
            return "<no color>";
    }
}

int main() {
    Pixel p1;
    cout << "Pixel p1 has color " << get_color(p1.col);
    cout << " and co-ordinates " << p1.x;
    cout << ',' << p1.y << '\n';

    Pixel p2{ { -1, 2}, Color::blue};
    cout << "Pixel p2 has color " << get_color(p2.col);
    cout << " and co-ordinates " << p2.x;
    cout << ',' << p2.y << '\n';
}
```

A few things to note about this program:

* The definition syntax `struct Pixel : Point {...};` causes `Pixel` to be *derived* from `Point`, meaning `Pixel` inherits **all** of `Point`'s members. `Pixel` is therefore the *derived* class, while `Point` is the *base* class. Sometimes the terms *sub-class* and *super-class* are used to refer to derived and base respectively. (Due to the fact we are using inheritance, it might be considered natural to refer to the `struct` types defined here as "classes".)

* The `pt` member variable has been removed as it is no longer used

* The member variables `x` and `y` are now direct members of `p1` and `p2`, accessed using `p1.x` etc.

**Experiment:**

* What error message do you get it you change `p1.x` back to `p1.pt.x`. Would you understand what the compiler was saying?

* Modify `get_pixel()` (written previously) to work with this program. Hint: The necessary changes should be very small.

* Now try to inherit from both `Point` and `Color` (the syntax is: `struct Pixel : Point, Color {...};`). Does this work as expected? Why do you think this is?

The concepts of inheritance and composition introduced here pose the question: "Which is better?" The literature tells us that inheritance represents *is-a* modeling and composition represents *has-a*. So which is more accurate: `Pixel` is-a `Point` (with a color), or `Pixel` has-a `Point` (and a color)? Personally, I think the first one is a better description, and would suggest that *is-a* inheritance should be used wherever practical to do so. In Chapter 9 we will meet inheritance again when describing more complex classes.

## Member functions

We have seen that the `struct Point` fields defined as `int x{}, y{};` can be acessed as member variables of objects using dot-notation such as `p1.x` and `p1.y`. Changing the types of `x` and/or `y` (to `double` for example) does not cause any problems, but renaming the fields to something different causes a compilation error as we would be trying to reference former members of `Point` which no longer exist.

Our `struct Point` is said to have *zero encapsulation*; its internals are open to public view, inspection and modification. Sometimes this is acceptable, but more often we want to *separate implementation from interface*. Use of member functions can be a way to provide an interface between the *user* of a type (the programmer who uses objects of that user-defined type) and the *implementor* of that type (the programmer who created the user-defined type). This interface is a *contract* between the two, which should always be considered and designed carefully.

Let us consider what we need in order to rewrite `Point` with some degree of encapsulation. The following program is our, by now familiar, `Point` type with three member functions (sometimes called *methods* in other programming languages) defined in the body of the `struct` definition, that is, within the braces. These functions can read and write the values of the member variables `x` and `y`, and logically enough are known as *getters* and *setters*. They are said to be defined *inline* when written in full between the braces of the `struct` definition, and as such are often automatically inlined by the compiler. This means that there may well be no function call overhead, so performance considerations should not be a reason to disregard encapsulation. (Types with methods are ususally known as classes in other languages, from now on we will use this word to mean any C++ composite type declared with `struct` or `class`, except for `enum class`.)

```cpp
// 06-point1.cpp : a Point type with getter and setters

#include <iostream>
using namespace std;

struct Point {
    void setX(int nx) {
        x = nx;
    }
    void setY(int ny) {
        y = ny;
    }
    auto getXY() const {
        return pair{x, y};
    }
private:
    int x{}, y{};
};

int main() {
    Point p;
    int user_x{}, user_y{};
    cout << "Please enter x and y for Point:\n";
    cin >> user_x >> user_y;
    p.setX(user_x);
    p.setY(user_y);
    auto [ px, py ] = p.getXY();
    cout << "px = " << px << ", py = " << py << '\n';
}
```

A few things to note about this program:

* The member functions appear before the member variables in the definition of `Point`; this is just a convention since members can in most cases appear in any order. The member function names have been written in *camelCase* which is a common convention.

* The member variables `x` and `y` are in scope for all of the member functions, so there is no need to fully qualify them as `this->x` and `this->y`.

* The member function returns both `x` and `y` as a `std::pair`. The `auto` return type is used (it's actually `std::pair<int,int>`) and is declared `const` between the (empty) parameter list and the function body. The use of `const` in this context means the member function promises not to modify any member variables (its own state). If you remember one thing about member functions, it should be to declare them `const` whenever they do not modify the object.

* The *access specifier* `private:` is used before the member variables `x` and `y` which means that code outside the scope of `Point` (such as in `main()`) cannot use them; they must use the getter and setters.

* The variable `p` of type `Point` in `main()` is default-initialized, other variants such as `Point p{ 0, 1 };` are not possible (due to `x` and `y` being `private:`), this would need a class constructor to be written (see Chapter 9).

* The `int`s `user_x`, `user_y`, `px` and `py` are all defined local to `main()`. The member access operator `.` is used as in `p.setX(user_x);` to call the member functions; this is another use of dot-notation.

* The return type of member function `getXY()` is read into `px` and `py` using aggregate initialization, and these variables are outputted.

**Experiment:**

* Write a function `setXY()` which modifies both member variables of `Point`, and use this instead of `setX()` and `setY()` in `main()`.

* Write two functions `moveByX()` and `moveByY()` which add their parameter's value to the `x` and `y` members respectively

* Change `pair` to `tuple` in `getXY()`. Does the code still compile? What does this indicate about the generality of aggregate initialization from return types?

* Try to modify `x` within `getXY()`. What happens? Now try to return a modified `x` such as `x+1` instead. What happens now? Try both of these having removed the `const` qualifier.

* Change the name of `x` to `super_x` within `Point`, remebering to change all of the member functions which use `x` too. Does the code compile without any changes to `main()`? What does this tell you about another advantage of separating implementation from interface?

## Static members

In the context of a class definition, `static` member variables (sometimes called *class variables*) are similar to global variables, in that there is only one *instance*. They are said to be *per-class* as opposed to *per-object*; that is, regardless of how many objects of a `struct` (or `class`) there are. Also they are referred to outside of the `struct` definition with a double colon operator (`::`), not dot-notation.

The following program extends the `Point` class with two `static` member constants. The member functions `setX()` and `setY()` have been modified, try to guess what they now do from the code:

```cpp
// 06-point2.cpp : a Point type with getter and setters which check for values being within range

#include <iostream>
using namespace std;

struct Point {
    void setX(int nx)
    {
        if (nx < 0) {
            x = 0;
        }
        else if (nx > screenX) {
            x = screenX;
        }
        else {
            x = nx;
        }
    }
    void setY(int ny)
    {
        if (ny < 0) {
            y = 0;
        }
        else if (ny > screenY) {
            y = screenY;
        }
        else {
            y = ny;
        }
    }
    auto getXY() const {
        return pair{x, y};
    }
    static const int screenX{ 639 }, screenY{ 479 };
private:
    int x{}, y{};
};

int main() {
    cout << "Screen is " << Point::screenX + 1 << " by " << Point::screenY + 1 << '\n';
    Point p;
    int user_x{}, user_y{};
    cout << "Please enter x and y for Point:\n";
    cin >> user_x >> user_y;
    p.setX(user_x);
    p.setY(user_y);
    auto [ px, py ] = p.getXY();
    cout << "px = " << px << ", py = " << py << '\n';
}
```

A few things to note about this program:

* The static member variables `screenX` and `screenY` are declared both `static` and `const` and are assigned values within the definition of `Point`.

* These variables can be accessed directly from within `main()` as they are defined before the `private:` access specifier. As they are **read-only** it is acceptable for them to be accessed directly.

* The default values of `x` and `y` (zero) do not need to be changed as they fall within the permitted values.

* The class *invariants* `0 <= x <= screenX` and `0 <= y <= screenY` are not easily able to be broken when `Point` is written with setters which validate their input.

The goal of encapsulation is still achieved with `screenX` and `screenY` being directly accessible from within `main()` because they are constants.  If `screenX` and `screenY` could be modified directly, this would no longer be the case, and a setter/getter pair (or similar) should be created. (A similar rule is allowing global *constants*, as opposed to *variables*, without restriction as neither data-races nor accidental reassignment can occur with constants.)

**Experiment:**

* Refactor the code logic of `setX()` and `setY()` into a utility function `within()` which is called by both. Declare `within()` to be `static`. Can you call it from within `main()`? How would this be accomplished, and is it desirable?

* Can you find a utility function from the Standard Library which does the same task as `within()`?

* Remove the `const` qualifier from `screenX` and `screenY`'s definition. What other change is necessary?

* Move these two variables after the `private:` access specifier, and write a getter/setter pair called `getScreenXY()` and `setScreenXY()`. Modify `main()` to accommodate this change. Is it easily possible to maintain the invariants of this type for `Point`s already created, that is existing `Point`s that are now outside the screen area?

## Operator overloading

There are many operators in C++ and most of these can be adapted (or *overloaded*) to work with user-defined types. (Operators for built-in types are not able to be redefined.) Like many other features of the language their availability and flexibility should be approached with some degree of restraint.

Operator oveloading works in a similar way to function overloading, so some familiarity is assumed with this concept. C++ resolves operator calls to user-defined types, to function calls, so that `r = a X b` is resolved to `r = operator X (a, b)`. (This is a slight simplification; where `a` is a user-defined type, the member function `r = a.operator X (b)` is used in preference, if available.)

The following program demonstrates the `Point` type, simplified back to its original form, with global `operator+` defined for it:

```cpp
// 06-point3.cpp : Point type with global operator+ defined

#include <iostream>
using namespace std;

struct Point{
    int x{}, y{};
};

const Point operator+ (const Point& lhs, const Point& rhs) {
    Point result;
    result.x = lhs.x + rhs.x;
    result.y = lhs.y + rhs.y;
    return result;
}

int main() {
    Point p1{ 100, 200 }, p2{ 200, -50 }, p3;
    p3 = p1 + p2;           // use overloaded "operator+"
    cout << "p3 = (" << p3.x << ',' << p3.y << ")\n";
}
```

A few things to note about this program:

* The return type of the `operator+` we define is returned by value; it is a new variable. The return value is declared `const` in order to **prevent** accidental operations on a temporary, such as: `(p1 + p2).x = -99;`

* The parameters of this function are passed in by `const` reference. The names `lhs` and `rhs` are very common (for the left-hand-side and right-hand-side to the operator at the *call site* in `main()`).

* The function `operator+` needs to access the member variables of the parameters passed in.

* The new values `result.x` and `result.y` are computed independently, as might be expected.

* The statement `p3 = p1 + p2;` invokes a call to `operator+` automatically.

**Experiment:**

* Rewrite `operator+` to avoid the need for a named temporary variable `result`.

* Write an `operator-` and call it from `main()`.

It is usual to write `operator`s as global (or *free*, or *non-member*) functions when they do not need to access `private:` parts of the types which they operate on. This is not a problem for member function `operator`s as they implicitly have access to all parts of both themselves and the variable they operate on.

The simplified result of these conventions is demonstrated in the following program:

```cpp
// 06-point4.cpp : Point type with global operator+ and member operator+= defined

#include <iostream>
using namespace std;

struct Point{
    int x{}, y{};

    Point& operator+= (const Point& rhs) { // member operator +=
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
};

const Point operator+ (const Point& lhs, const Point& rhs) { // non-member operator+
    Point result{ lhs };
    result += rhs;
    return result;
}

int main() {
    Point p1{ 100, 200 }, p2{ 200, -50 }, p3;
    p3 = p1 + p2;
    cout << "p3 = (" << p3.x << ',' << p3.y << ")\n";
}
```

A few things to note about this program:

* The `main()` function and its output are the same as for the previous program.

* The member function `operator+=` takes **one** parameter named `rhs` and modifies its own member variables. It returns a **reference** to a `Point`, this being itself. One of the rare uses of the `this` pointer, dereferenced here with `*`, is shown here without further explanation.

* The global `operator+` makes a **copy** of `lhs` and then calls (member) `operator+=` on this with parameter `rhs`. (Both of the `rhs`'s are the same variable as they are passed by reference.)

* Global `operator+` does **not** directly access the member variables of either of its parameters.

* The variable `result` is then returned by `const` value, as before.

**Experiment:**

* Modify this program to implement and test `operator-=` and `operator-`.

* Now modify the program to use the encapsulated version of the `Point` from the program `06-point2.cpp`. What difficulty would you encounter if you tried using only global `operator+`?

* Add a `static` function to calculate the diagonal distance between two `Point`s and return it as a `double`. Consider how to implement `operator/` to calculate this value, and whether this would be a suitable use of OO.

*All text and program code &copy;2019-2024 Richard Spencer, all rights reserved.*
