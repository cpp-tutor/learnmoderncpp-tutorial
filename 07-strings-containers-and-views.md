# Strings, Containers and Views

## String initialization, concatenation and comparison

Whilst support for read-only string literals is built into C++, we must make use of the Standard Library when we want a string-type which is be able to be manipulated and compared, using operators such as `+` (concatenation) and `==` (equality comparison). The `std::string` type supports all of the operations you would expect to be present, such as concatenation, indexing, sub-string extraction, comparisons and reporting the length. All of the memory management operations necessary are taken care of automatically at run-time; string objects are allowed to use heap memory and interestingly do not use any "special" features of the language not available to the application programmer.

An empty string object can be created using `string` as the type specifier, either using uniform initialization syntax, or `auto`, or omitting the braces altogether where the type specifier is first:

```cpp
string s1;
string s2{};
auto s3 = string{}; // s1, s2, s3 are empty (mutable) strings
```

Other variants exist as well, but these shown are the most modern. When an empty `std::string` is compared against an empty string literal `""` using `==` the result is `true`.

A `std::string` can be initialized or re-assigned from a string literal:

```cpp
string name1;
name1 = "Bilbo";             // (re-)assignment after definition

string name2{ "Frodo" };     // assignment combined with definition
```

Both `name1` and `name2` are able to be modified, for example by concatenation using `+`:

```cpp
name1 = name1 + " Baggins";  // name1 has value "Bilbo Baggins"
name2 += " Baggins";         // name2 has value "Frodo Baggins"
```

Single `char` literals can be appended too, although a `std::string` **cannot** be created from a single `char`:

```cpp
string s1 = 'A';             // Error! Does not compile
auto s2 = string{} + 'A';    // This version is fine, but maybe non-obvious
```

Strings can be reset to empty using a member function, or by assigning to an empty string literal:

```cpp
s1 = "";                     // Both of these accomplish the same thing
s2.clear();                  // (Using clear() is the preferred method)
```

Confusingly, there are two different member functions which return a `std::string`'s length (excluding the `\0` terminator if it was constructed from a string literal), and a third which returns a `bool` (value `true` indicates length is zero):

```cpp
if (name1.length() == name2.size()) { // historically std::string did not have size()
    cout << "Equal length\n";
}

if (s2.empty()) { // use in preference to "s2.size() == 0"
    cout << "Empty string\n";
}
```

The member functions `size()` and `empty()` are present in other containers as well, so it's a good idea to get to know them.

## Subscripting and string methods

It is possible to iterate over a `std::string` using a range-for loop; the following program demonstrates this:

```cpp
// 07-string-upper.cpp : function to make a std::string uppercase in-place

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

void string_to_uppercase(string &s) {
    for (auto& c : s) {
        c = toupper(c);
    }
}

int main() {
    cout << "Please enter some text in lower-, mixed- or upper-case:\n";
    string input;
    getline(cin, input);
    string_to_uppercase(input);
    cout << "The same text in uppercase is:\n" << input << '\n';
}
```

Things to note about this program:

* Both variables `s` and `c` are declared as references, thus modifiying them changes the variable they refer to, not a copy.

* The type of `c` is, perhaps unsurprisingly, `char&`.

* The `getline()` function (explained further in Chapter 8) is used to get an arbitrarily long line of input from `cin` and store it in `input`. (Note: don't confuse this with `cin.getline()` which we met in Chapter 5.)

**Experiment:**

* Remove one of the `&`s in the function `string_to_uppercase()`. Does the program still compile? Does it produce the expected output when run? Now remove the other `&` instead and try the same thing. What does this tell you about the importance of reading code which uses reference semantics very carefully?

* Modify `string_to_uppercase()` so that the uppercase string is *appended* to the input. Hint: this is a simple change that just requires some thought.

* Modify `string_to_uppercase()` so that a new uppercase string is returned as a `std::string`. Is the construct `input = string_to_uppercase(input);` within `main()` now legal? Does it work as expected? Do you still need to use reference semantics?

Individual characters of a `std::string` can be selected for read- or write-access using the subscript operator `[]`, which works in the same way as on built-in arrays. The index value is **not** checked for being within valid range (which is between `0` and `length() - 1` inclusive); if this check is required the member function `at()` should be used:

```cpp
string book = "a hobbit";
    
book[0] = 'A';           // book is now "A hobbit"

auto c1 = book[99];      // undefined behavior, probably garbage assigned to c1
auto c2 = book.at(99);   // throws an exception, possibly terminating the program (no value is assigned to c2)
```

**Experiment:**

* Modify `string_to_uppercase()` to use a regular for-loop and an index variable, together with unchecked array access syntax.

* Now modify this program to use **checked** array access. What happens if you make a (deliberate) bounds-checking error?

The member functions `front()` and `back()` return (modifiable) references to the first and last characters of a string; they can be used instead of `s[0]` and `s[s.length() - 1]`. Interestingly, **reading** `s[s.length()]` is not undefined behavior, but instead returns a value which is the default value of the underlying character type (`'\0'` for `char`).

To add or remove individual characters or substrings, the `insert()` and `erase()` member functions can be used (don't try to write to `s[s.length()]`):

```cpp
string book = "a hobbit";

book = "In " + book;
    // book is now "In a hobbit"
book.insert(5, "hole in the ground, there lived a ");
    // book is now "In a hole in the ground, there lived a hobbit"
book.erase(10, 21);
    // book is now "In a hole lived a hobbit"
```

There is also `replace()`, which is a combination of both of `erase()` and `insert()`.

Substrings can be extracted from a `std::string` using the `substr()` member function:

```cpp
string wizard = "Gandalf the Gray";

auto s1 = wizard.substr(0, 7);    // s1 is "Gandalf"
auto s2 = wizard.substr(8, 3);    // s2 is "the"
auto s3 = wizard.substr(12);      // s3 is "Gray"
```

The return type of `substr()` is `std::string`, which is a **new** variable containing a **copy** of (part of) the contents of the original `std::string`.

Finally there is `append()` which is considered better style than using the `+=` operator as it is potentially more efficient:

```cpp
auto wizard2 = "Saruman"s;    // note: suffix produces a string
wizard2.append(" the White"); // wizard2 becomes "Saruman the White"
```

## Conversions and literals

Sometimes it is necessary to convert between a `std::string` and other (often built-in) types, such as converting to and from an integer or floating-point number. The Standard Library function template `to_string` is overloaded to cope with different (built-in) types:

```cpp
auto n1 = 1.23;
auto n2 = 45;

auto s1 = to_string(n1);  // s1 is "1.230000"
auto s2 = to_string(n2);  // s2 is "45"
```

Converting the other way, the group of functions `sto`*x*`()` allow the (exact) output integer or floating-point type from an input `std::string` (often usefully a sub-string). The full list is: `stoi()`, `stol()`, `stoul()`, `stoll()`, `stoull()`, `stof()`, `stod()` and `stold()`.

```cpp
auto n3 = stoi(s2);   // n3 is of type int
auto n4 = stold(s1);  // n4 is of type long double
```

For the conversion functions which return an integer type, the optional third parameter is the numerical base to be applied (this defaults to 10), while for all of these functions the optional second parameter is a pointer to `std::size_t` variable used to indicate the index into the `std::string` of the first unused character (this defaults to `nullptr`, that is no index is returned).

It is possible to declare `std::string` variables using syntax which is very similar to that for string literals, which uses the *literal suffix* `s`:

```cpp
auto h1{ "Merry"s };               // h1 is mutable
const auto h2{ "Pippin"s };        // h2 cannot be altered
constexpr auto h3{ "Samwise"s };   // h3 can be used in constexpr contexts
```

In addition, a single (possibly empty) `std::string` literal can be safely concatenated with any number of string and character literals:

```cpp
auto alphabet = ""s + "ABCDEF" + ' ' + "abcde" + 'f';
             // alphabet contains "ABCDEF abcdef" and is of type std::string
```

Here `alphabet` has type `std::string`, and the concatenation is performed at run-time (use `constexpr` to make it happen at compile-time).

Access to the underlying `char` representation of a `std::string` is provided by the member functions `c_str()` (an abbreviation of "C-String") and `data()`. The difference between the two is that `c_str()` **guarantees** to include a terminating zero-byte and is **not** writable, whereas `data()` **is** writable but with the caveat that there may be not be any terminating zero-byte (it depends on both the `std::string`'s contents and the library implementation). Thus `c_str()` returns a `const char *` that can be safely used as a parameter to C functions such as `puts()`, or with C++ stream output, whereas `data()` returns a `char *` which is not always safe to be used with any function which expects a zero-byte terminator. (As an example, use of `data()` combined with `size()` to create a `std::string_view` is always safe.)

**Experiment:**

* Modify `string_to_uppercase()` to use `data()` inside a regular for-loop to do its work. Hint: Continue to use a loop index, the syntax may surprise you.

* Now modify this program to use pointer arithmetic instead of a loop index.

* Modify this program again to use `begin()` and `end()`.

## String views

There is a fourth string-like type (besides literal string, built-in array of `char` and `std::string`) called `std::string_view`, which provides a "half-way house" between a fully-fledged string type and raw array access. Typically it is implemented with only two fields (pointer and length); its main advantage over `std::string` is that it can be constructed and passed around more cheaply in many cases.

The `std::string_view` type only provides a subset of the features provided by `std::string`, in particular it does **not** support either in-place modification or concatenation. It also does **not** "own" the resource it refers to, therefore care must be taken to ensure that a `std::string_view` object does not outlive the entity from which it was constructed (usually a `std::string` or `const char *`, construction from a string literal is always safe.). It is safe when used as a function parameter (where otherwise a `const std::string&` or `const char *` would be used), and sometimes safe as a return type (instead of `const char *`).

```cpp
string_view v1{ "Elrond" }; // string_view constructed from const char *
string_view v2{ "Arwen"s }; // Error! attempt to construct string_view from temporary std::string
auto v3{ "Galadriel"sv };   // std::string_view literal

cout << v1 << '\n';         // outputs "Elrond"
cout << v2[0];              // outputs "A"
cout << v3.data() << '\n';  // Possibly unsafe, no guarantee of terminating '\0'
v3[0] = 'C';                // Error! no write access
v3.data()[0] = 'C';         // Error! no write access
auto elves = v1 + v3;       // Error! operator+ (concatenation) not supported
```

The following program demonstrates a function called `print_reversed()` with a `std::string_view` as a function parameter, called with each of: a pointer, a string literal, a `char`-array, a `std::string` and a `std::string_view`.

```cpp
// 07-reversed.cpp : output different "string" types using a string_view

#include <iostream>
#include <string>
#include <string_view>
using namespace std;

void print_reversed(string_view sv) {
    for (auto iter = crbegin(sv); iter != crend(sv); ++iter) {
        cout << *iter;
    }
    cout << '\n';
}

int main() {
    const char *s1 = "Elf";
    char s2[] = "Dwarf";
    string s3 = "Hobbit"s;
    string_view s4 = "Orc"sv;

    print_reversed(s1);
    print_reversed(s2);
    print_reversed(s3);
    print_reversed(s4);
    print_reversed("Man");
}
```

A few things to note about this program:

* The function `print_reversed()` uses a constant reverse iterator to loop over its input. If you're not familiar with this idiom, you may wish to review program `05-begin-end.cpp` and the table below it from Chapter 5.

* The iterator variable `iter` is dereferenced as `*iter` to obtain a single character for printing.

* The function `print_reversed()` is called from `main()` repeatedly but with different typed arguments, all of which are resolved at compile-time and are *implicitly convertible* to `std::string_view`.

**Experiment**

* Change the type of `print_reversed()`'s parameter to `const string&`. Does the program compile?

* What about if you use a `const char[]`? Hint: remember array decay.

* Now modify this function so that it **returns** its input reversed. What parameter type and return type would you choose?

## Vectors and iterators

If you remember one thing about C++ container types, of which `std::vector` is one, it should be that elements are meant to be manipulated using *iterators*. (We have seen the `std::string` member functions `insert()` and `erase()` being used with indices, however even these can use iterators instead.) An iterator is a pointer-like object that when dereferenced, yields exactly one object from within a container; the `begin()` and `end()` family of functions should each be thought of as returning an iterator, rather than a pointer.

The following program populates a `std::vector` of integers from user input, and then outputs it in numerically sorted order.

```cpp
// 07-vector.cpp : read integers from user, sort them and then output

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int main() {
    vector<int> v;
    for (;;) {
        cout << "Please enter a number (99 to quit): ";
        int i{};
        cin >> i;
        if (i == 99) {
            break;
        }
        v.push_back(i);
    }

    sort(begin(v), end(v));
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << '\n';
}
```

A few things to note about this program:

* We start with an empty `std::vector`, this means that the `int` element type **must** be specified (within angle brackets) as it cannot be otherwise deduced. This type is fixed at compile-time.

* A "forever" loop with local variable `i` is used to avoid the need for either multiple `cout` statements (which would be code duplication) or a do-while loop (which would most likely cause `99` to be appended to the `vector`, which we don't want).

* The `push_back()` member function of `vector` is used to make `i` the new last element, this "grows" the container automatically as needed.

* The *Standard Libary algorithm* `std::sort()` gets all of the information about the `vector` that it needs in order to operate from the two iterators provided as parameters. (It can be relied upon to be an efficient algorithm, probably performing better than any hand-written code.)

* Instead of a traditional or range-for loop, a second algorithm `std::copy()` is used. As might be guessed this copies everything from the first iterator up to, but not including, the second iterator to its third parameter, which is actually an *output iterator*. There is no "magic" involved, all you need to understand is that a `std::output_iterator` *object* takes a single type of its output between triangular brackets (here it is `int`) and the output stream and optional delimiter are specified as parameters. (This is boilerplate code that can be reused in your own programs, possibly with different types and delimiters.)

**Experiment:**

* Type `99` as the first input value. Does the program crash? Does this surprise you? Check that `v` is `empty()`.

* Modify the program to print out the highest numbers first. Hint: use `crbegin()` and `crend()`.

* Change to using a range-for loop instead of `std::copy()` to output the `vector`. Hint: use `const auto&`.

* Use member functions `begin()` and `end()` in the call to `std::sort()`. Does the compile to the same thing? Which style do you prefer?

* Rewrite the second `for`-loop using an index variable and subscript access. Do you still prefer this form?

There are many member functions belonging to `std::vector` and the other standard containers, and even experienced C++ programmers don't remember them all. There are even more (over 100) function templates (algorithms) which operate with the standard containers through iterators; where there is a choice between both the member function should be used as this will be specialized for the container type. There is almost never a need to write a mini-algorithm which operates within a loop over the elements of a container, as would be needed in C or with built-in arrays; they have been implemented in the Standard Library ready for you to use.

When you reach for a container, `std::vector` is often the best fit, and should be your natural first choice. Should you decide that one of the other container types is needed, this would usually be a design decision made early in the development of your program. There is uniformity in the naming of the member functions, so all containers support `clear()`, for example. However as soon as you delve into the implementation details, such similarity appears superficial. It is important to have a basic understanding of the implementation of each container so that their individual advantages and limitations are understood, in order for the correct one to be chosen and used effectively.

As an example, consider the use of `std::find()` versus member function `find()` when using `std::string`, `std::vector` and `std::set`; this function finds the first occurence of its parameter in the specified container. The `std::set` container is similar to `std::vector` except that it maintains its elements in sorted order. The differences are:

* For `std::string`, member function `find()` returns an **index** having performed a *linear search* (checking each character element in turn).

* For `std::vector`, algorithm `std::find()` returns an **iterator**, again performing a linear search.

* For `std::set`, member function `find()` returns an **iterator** having performed a *binary search* (repeatedly dividing the range of values in half). This is quicker than using `std::find()`.

For `std::string`s if the search criterion is not found, special value `std::string::npos` is returned ("no position"), whilst the iterator which indicates not found is `end()` (**not** `nullptr` or zero). The following program demonstrates this:

```cpp
// 07-find.cpp : find and erase a single element

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <iterator>
using namespace std;

int main() {
    string a{ "hello" };
    vector v{ 1, 9, 7, 3 };
    set s{ 3, 8, 6, 4, 3 };
    
    cout << "Before:\nstring: " << a << "\nvector: ";
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));    
    cout << "\nset: ";
    copy(begin(s), end(s), ostream_iterator<int>(cout, " "));
    cout << '\n';

    auto f1 = a.find('l');
    if (f1 != string::npos) {
        cout << "Found in string at position: " << f1 << '\n';
        a.erase(f1, 1);
    }
    auto f2 = find(begin(v), end(v), 7);
    if (f2 != end(v)) {
        cout << "Found in vector: " << *f2 << '\n';
        v.erase(f2);
    }
    auto f3 = s.find(6);
    if (f3 != end(s)) {
        cout << "Found in set: " << *f3 << '\n';
        s.erase(f3);
    }

    cout << "After:\nstring: " << a << "\nvector: ";
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));    
    cout << "\nset: ";
    copy(begin(s), end(s), ostream_iterator<int>(cout, " "));
    cout << '\n';
}
```

The output from running this program is:

```
Before:
string: hello
vector: 1 9 7 3
set: 3 4 6 8
Found in string at position: 2
Found in vector: 7
Found in set: 6
After:
string: helo
vector: 1 9 3
set: 3 4 8
```

Take time to study this program as it contains some important concepts:

* The `main()` program consists of four parts, the second and fourth of which are near-identical and simply print out all the containers before and after modification.

* The first part assigns a `std::string` from a string literal, and a `std::vector` and `std::set` from two different initializer lists. Note that `std::set` can only hold unique values, so the container begins with a size of four, not five as for the initializer list (because of the duplicated value `3`).

* The interesting part of the program is the third part, itself split into three. The logic is the same, search for an element value with the correct form of `find()`, compare it against "not found", and if found then erase it. The form of `erase()` used for `std::string` needs a length for the second parameter, while for `std::vector` and `std::set` it takes an iterator as the single element to erase.

**Experiment**

* Sort the `std::vector` and use a binary search instead of a linear one. Hint: use `std::lower_bound()` not `std::binary_search()`.

* Experiment with adding values to the containers, at the beginning, in the middle and at the end. Use a mixture of member function `push_back()` (where possible) and member function `insert()` or `std::insert()` where applicable.

## Spans and arrays

It can be very inefficient to copy `std::vector`s by value, as copies of both the `vector` object, and also the array it manages, need to be made. The preferred way to pass a `vector` to a function is to use a reference, or a `const` reference in cases where the original `vector` should not be modified.

**Experiment**

* Write a function called `populate_int()` which takes a `vector<int>` as its parameter and implements the logic of the `for`-loop in `07-vector.cpp`. Call this function from `main()` instead of using a `for`-loop .

* Now use `double` instead of `int` in the program. How many code changes are needed?

In the style of `std::string_view` being implicitly constructible from charater sequences, there exists the type `std::span` which provides a similar function for array-style containers (those which hold their elements contiguously in memory). The following program contains a function `print_ints()` whose parameter is of type `std::span<int>` and which iterates over this sequence:

```cpp
// 07-span.cpp : convert different container types to span and print them out

#include <iostream>
#include <span>
#include <array>
#include <vector>
#include <string_view>
using namespace std;

void print_ints(span<int> s) {
    for (auto sep{ ""sv }; auto& e : s) {
        cout << sep << e;
        sep = ", "sv;
    }
    cout << '\n';
}

int main() {
    int c_array[] = { 1, 2, 3 };
    vector vec = { 2, 6, 4, 3 };
    array<int,4> std_array = { 7, 6, 5 };

    print_ints(c_array);
    print_ints(vec);
    print_ints(std_array);
    // print_ints({ 9, 8, 7, 6 }); // Error: does not compile
}
```

A few things to note about this program:

* A range-for loop with an initializer field prints out the values of the `std::span` parameter, outputting a separator in-between, but not after, the elements. The trick of reassigning the variable `sep` gets around the limitation of using `std::copy()`.

* The three array-like types are initialized in `main()`. The size of type `std::array` is fixed at compile-time (from its optional second template parameter) and allows it to be allocated on the stack, not using any heap memory. (Due to the fact that `begin()` and `end()` can be used with built-in arrays there are not many cases where `std::array` is useful.)

* The commented-out call to `print_ints()` doesn't compile as there is no valid conversion from `std::initializer_list<int>` to `std::span<int>`. This is a possible use case for a temporary `std::array`, as in: `print_ints(array{ 9, 8, 7 ,6 });`

Unlike `std::string_view`, `std::span` can modify its elements, although it does not "own" them. Also, a second type of `std::span` takes its size parameter after the type, which is also fixed at compile-time.

**Experiment**

* Remove the size field (`4`) from the definition of `std_array`. What is the inferred size of this `std::array` now?

* Perform a sort within `print_ints()` before outputting.

* Now output the containers in `main()` after calling `print_ints()`. Have the orders of these changed?

## Ordered and unordered sets

A `std::set` holds its contents in sorted order at all times, thus it is called an *ordered container*. Occasionally this is desirable, however there are space and time costs to this convenience so before using this container type you should consider whether a `std::vector` which can be (manually) sorted when required is a better solution. Array access (using `[]`) is not supported for `std::set`; this may be a deciding factor as to its suitability. Ordered containers require that `operator<` (less-than) is defined when using them to hold user-defined types (other ordering criteria can be specified, if needed).

A feature of `std::set` is that it cannot hold duplicate values; subsequently inserting a previously held value does not alter the container, while an initializer list containing duplicates is shortened (and sorted) immediately. (The type `std::multiset` does allow duplicate values.)

The following program defines a `std::set` with value type `std::string`:

```cpp
// 07-set.cpp : demonstrate automatic ordering of a set

#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

int main() {
    set<string> s{
        "Rossum, Guido van",
        "Yukihiro, Matsumoto",
        "Wall, Larry",
        "Eich, Brendan"
    };

    s.insert("Lerdorf, Rasmus");
    copy(begin(s), end(s), ostream_iterator<string>(cout, "\n"));
}
```

**Experiment**

* Modify this program so that further names can be added with user input. Is the sorted order preserved?

* Change the container type to `std::multiset`. Does the program compile and run? What happens if you (deliberately) enter a duplicate name?

* The correct ordering depends on the rule of surname first with capitalized first letter. Remove this second restriction by storing all names in lower-case, capitalizing the first letter for output.

Lookup for `std::set` is faster than linear searching due to the fact that its elements are always sorted. There is also the container type `std::unordered_set` which can claim to have constant-time lookup in the best case due to utilization of a *hash function*. (To complete the quartet, there exists `std::unordered_multiset`.)

**Experiment**

* Modify the original `07-set.cpp` to use `std::unordered_set` as the only change.

* Now add the ability to add subsequent entries from user input, and print out the whole collection on each change. Does anything surprise you?

In fact, due to the way that the *unordered containers* are implemented, removal or addition of even a single element can change the whole apparent "order" of the elements. Note that a hash function needs to be provided for user-defined types stored in an unordered container (this is achieved by providing a *specialization* of `std::hash`).

## Lists and forward-lists

Some operations can be inefficient with `std::vector` because of the way it is implemented by the library; operations such as `insert()` and `erase()` can involve the movement much of the data stored in memory. (In fact this is unavoidable, the Standard dictates that the elements of a `std::vector` are stored contiguously in memory.) Other operations such as `push_front()` are not implemented at all, for the same reason. (Using a `std::deque` instead would resolve this particular limitation.)

The implementation of `std::list` is fairly straightforward; each element is stored in its own block of assigned memory, together with two pointers; one pointer to the previous element and one pointer to the next element. This does mean that element insertion and deletion can be much quicker than for `std::vector`, however more memory is used by this container in total (the size of two pointers times number of elements, approximately). Lists of "large" objects become more efficient than lists of "small" ones, and as for `std::vector` all elements must be of the same type and size. It follows that the implementation of `std::forward_list` is similar but with only one pointer in each block, pointing to the next element.

Some operations that `std::vector` supports, such as indexing using subscript syntax (`[]`) and `std::sort()`, are not supported at all, either because performance would be unacceptably poor or because the algorithm requres a *random-access iterator*. In fact, `std::list` implements its own member function `sort()` which performs a *stable sort* in-place. The iterator type which works with `std::list` is called a *bi-directional iterator*, meaning that pointer arithmetic-style operations on iterators cannot work. The iterator type for `std::forward_list` is called a *forward iterator*.

The following program demonstrates both `std::forward_list` and `std::list` being used, although it is not intended to be an example of best practice:

```cpp
// 07-lists.cpp : forward and bi-directional lists

#include <iostream>
#include <string>
#include <forward_list>
#include <list>
using namespace std;

int main() {
    forward_list<string> fwd;
    auto iter = fwd.before_begin();  // note: member function
    cout << "Please enter some words (blank line to end):\n";
    for (;;) {
        string s;
        getline(cin, s);
        if (s.empty()) {
            break;
        }
        fwd.insert_after(iter, s);  // note: member function
        ++iter;                     // note: must "keep up"
    }

    list<string> lst(begin(fwd), end(fwd)); // copy fwd into lst
    lst.sort();
    for (const auto& e : lst) {
        cout << "- " << e << '\n';
    }
}
```

A few new things about this program:

* There are two lists, a `std::forward_list` called `fwd` and a `std::list` called `lst`.

* The variable `iter` is initialized by member function `before_begin()`, this is unique to `std::forward_list`.

* In the first loop the `std::string` in variable `s` is inserted after `iter`'s position using member function `insert_after()`.

* The variable `iter` is then incremented, still in the first loop.

* The empty `std::list` is initialized from the `begin()` and `end()` of `fwd`. This is the standard way of making a copy of a container.

* Member function `sort()` is called on `lst`, which is then printed out.

**Experiment**

* Consider how to memberwise compare `fwd` and `lst`.

* Since the input is to be sorted eventually, experiment with other ways of populating `fwd`. Hint: consider `push_front()`.

## Ordered and unordered maps

All of the containers seen so far have stored a number of elements of a single type. There has been no other information stored with the element, except possibly for `std::vector` where the first element has index `0`, the second has index `1` and so on. This index can be thought of as the *key* as it allows direct access to a single *value*.

This can be generalized so that the key can be of any type, not just a sequence of advancing integers. In C++ all maps operate with a type called `std::pair` which as might be guessed has two fields; these are called `first` and `second`. We could define `std::pair` as follows:

```cpp
template <typename Key, typename Value>
struct pair {
    Key first;
    Value second;
};
```

However we don't need to do this as the Standard Library provides this definition (or one very similar, the exact implementation details are not important). Maps operate on collections of *key/value pairs* which are provided by this type.

The first *associative container* we will look at is `std::map`. The following program uses a `std::map` to hold the per-weight prices of a list of fruits, which can be added to during a run of the program:

```cpp
// 07-map.cpp : calculate prices from associative array of products and per-weight cost

#include <iostream>
#include <string>
#include <cctype>
#include <map>
using namespace std;

int main() {
    map<string,double> products{
        { "Apples", 0.65 },
        { "Oranges", 0.85 },
        { "Bananas", 0.45 },
        { "Pears", 0.50 }
    };
    cout.precision(2);
    cout << fixed;
    for (;;) {
        cout << "Please choose: Add product, Calculate price, Quit\nEnter one of A, C, Q: ";
        char opt;
        cin >> opt;
        opt = toupper(opt);
        if (opt == 'Q') {
            break;
        }
        else if (opt == 'A') {
            cout << "Enter product and price-per-kilo: ";
            string product;
            double price;
            cin >> product >> price;
            product.front() = toupper(product.front());
            products.insert(pair{ product, price });
        }
        else if (opt == 'C') {
            for (const auto& p : products) {
                cout << p.first << '\t' << p.second << "/kg\n";
            } 
            cout << "Enter product and quantity: ";
            string product;
            double quantity;
            cin >> product >> quantity;
            product.front() = toupper(product.front());
            auto iter = products.find(product);
            if (iter != end(products)) {
                cout << "Price: " << iter->second * quantity << '\n';
            }
            else {
                cout << "Could not find \"" << product << "\"\n";
            }
        }
        else {
            cout << "Option not recognized.\n";
        }
    }
}
```

This is a longer program but does not contain much that is new. A few points to note:

* The `std::map` called `products` is initialized from a nested initializer list, and the key/value types are specified within the angle brackets. The output of floating point numbers is fixed to two decimal places.

* With user option `A`, member function `insert()` is called with a (temporary) `std::pair`. This is usually preferred over using array syntax, while `products[product] = price` would work in most cases it is not the most efficient.

* With user option `C`, all of the products are printed out by a range-for loop which iterates over `products` and outputs the `first` and `second` fields of each element. Then member function `find()` is called to obtain an iterator. This is compared against `end(products)` (which if equal would indicate "not found"), a valid value allows the value as `iter->second` to be retrieved.

As explained above, use of array syntax is not used by this program when adding an entry, nor is it advisable in most cases for element lookup:

```cpp
auto price_per_product1 = products["Apples"];      // would work, but find() is better
auto price_per_product2 = products["Missing1"];    // Warning: creates entry with key "Missing1" and value 0.0
auto price_per_product3 = products.at("Missing2"); // Warning: might throw an exception, which would need to be caught
```

**Experiment**

* What happens if you try to change an existing entry with a different price-per-kilo? Can you discover a way to warn the user?

* Use `std::unordered_map` instead of `std::map`. Does the program still compile and run? What is the effect of adding one or more products to the order in which they are output?

To complete the list of associative containers, `std::multimap` and `std::unordered_multimap` allow duplicate occurences of keys with the same or different values, thus `insert()` always succeeds.

## Other containers and adaptors

There are some other containers and *container adaptors* implemented in the Standard Library:

* `std::vector<bool>` is a specialization of `std::vector` that stores binary bits as packed data

* `std::bitset` also stores binary bits, but has its size fixed at compile-time

* `std::deque` (pronounced "deck") implements a double-ended container similar to `std::vector`, but with additional operations such as `push_front()`

* `std::stack` implements a LIFO (Last In First Out)

* `std::queue` implements a FIFO (First In First Out)

* `std::priority_queue` implements a FIFO that sorts by age and priority

* `std::flat_set` implements a sorted container of unique values, typically implemented as a vector

* `std::flat_map` implements a sorted associative container, typically implemented as two vectors (one for keys and one for values)

A brief Tutorial such as this is not the place to delve into these, and indeed the other containers covered in this Chapter have much more detail to discover. As a go-to for both tutorial and reference I can highly recommend [CppReference.com](https://en.cppreference.com)[^1] and [Josuttis, "The C++ Standard Library"](http://cppstdlib.com)[^2].

[^1]: https://en.cppreference.com
[^2]: http://cppstdlib.com

*All text and program code &copy;2019-2024 Richard Spencer, all rights reserved.*
