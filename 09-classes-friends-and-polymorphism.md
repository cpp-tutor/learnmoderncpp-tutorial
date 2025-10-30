# Classes, Friends and Polymorphism

## Private, protected and public

Classes are used to model abstract and concrete entities in ways that combine state with functionality. (The state is held in member variables and the functionality is provided by member functions.) The literature tells us that classes encapsulate both data and the methods (functions) that act upon that data. Objects are *instances* of a particular class in the same way that (normal) variables are instances of a (built-in) type.

Let us consider a minimalist `Person` class, which we will later extend to `Student` and `Employee` through inheritance. Our first attempt might look like this:

```cpp
struct Date {
    int year{}, month{}, day{};
};

class Person {
    Date dob;
    string familyname, firstname;
};

Person a_person{};

Person genius{ { 1879, 3, 14 }, "Einstein", "Albert" }; // Error: does not (yet) compile
```

This `Person` class (here defined with `class` as opposed to the `struct` keyword we met in Chapter 6) contains three members: `dob` (itself of a user-defined type called `Date`), `familyname` and `firstname` (both of which are `std::string`s). We can define a variable of type `Person` (here `a_person`) using default-initialization syntax (the braces shown here are in fact optional, while empty parentheses are **not** permitted) but we cannot do a lot else with this object. Its fields will be zero-initialized for `a_person.dob.year`, `a_person.dob.month`, and `a_person.dob.day`, while `a_person.familyname` and `a_person.firstname` are empty strings. This is becuase the access specifier `private:` (which we also met in Chapter 6) is always implied for `class`es. This means we cannot either access the fields (member variables) directly using dot-notation, or use uniform initialization syntax, as with `genius`.

**Experiment:**

* Change the above fragment to use `struct` instead of `class` in order to enable compilation, and also write an empty `main()` function. Does the program run? Is it therefore self-contained?

* Now try to create `genius` within `main()` using assignment to member variables and uniform initialization. What error messages do you get? Does changing the keyword `class` to `struct` fix this problem in both cases?

The key to solving the inability to create `Person`s using uniform initialization syntax is solved by writing a *constructor*. Access to member variables after the object has been created is achieved using *getters* and *setters*, which we met previously in Chapter 6. In order to be useful, a constructor must be declared after a `public:` access specifier. The following program demonstrates this, together with a `main()` program which produces output:

```cpp
// 09-person1.cpp : model Person as a class with constructor

#include <chrono>
#include <iostream>
#include <string>
#include <string_view>
using namespace std;
using namespace std::chrono;

class Person {
public:
    Person(const year_month_day& dob, string_view familyname, string_view firstname)
        : dob{ dob }, familyname{ familyname }, firstname{ firstname }
        {}
    string getName() const { return firstname + ' ' + familyname; }
    const year_month_day& getDob() const { return dob; }
private:
    const year_month_day dob;
    string familyname, firstname;
};


int main() {
    Person genius{ { 1879y, March, 14d }, "Einstein", "Albert" };
    cout << genius.getName() << " was born " << genius.getDob() << '\n';
}
```

Quite a few things to note about this program:

* A constructor has the format *ClassName* ( *parameter-list* ) : *member initializers* { *possibly empty function body* } and does **not** have a return type declared.

* The constructor's parameters have names `dob`, `familyname` and `firstname`, these being the same names as for the member variables (this is allowed in Modern C++). The conventions for naming (`private:`) class members vary, historically a trailing underscore is used, but this can become difficult to read.

* The member variables are initialized using uniform initialization syntax; this forbids narrowing conversions, and there shouldn't be any as the parameter types should have been carefully chosen. (Older code may use parentheses here instead of braces.) The order of construction is the same as the way the member fields are laid out (in this class they are all after the `private:` access specifier); the order in the comma-separated initializers is unimportant (although you should try to replicate the order of the member fields, and your compiler will warn if they differ). The constructor's body is empty here (although it must be present), and this is not unusual.

* The `std::chrono::year_month_day` parameter (itself initialized by uniform initialization) is passed as `const`-reference instead of by value, as it is probably too big to fit in a single register to pass by value. The names are passed by value as `std::string_view` although in older code `const std::string&` would be common.

* The member function `getName()` is declared `const` as it is guaranteed not to change any member variables. It returns a newly created `std::string` which must be returned by value.

* The member variable `dob` is declared `const` as it will never need to be changed; of course it needs to be initialized by the constructor, and this case is allowed. The member variables `familyname` and `firstname` need to be of type `std::string` (not `std::string_view` as for the constructor's parameters) for them to be guaranteed to exist for the lifetime of the class (consider factory functions which return a newly-constructed object, as we saw in Chapter 8).

* The member function `getDob()` is also declared `const` and returns a `const`-reference. It is possible to put this return value directly to a `std::ostream` as the Standard Library overloads `operator<<` for `std::chrono::year_month_day`.

**Experiment:**

* Add more `Person` objects to `main()`, and output their names.

* Rewrite the constructor to initialize the member variables in the body, instead of using the comma-separated list of member initializers.

* Modify this program to use `std::println()` instead of `cout`. Perform most of the formatting in a `const` member function `toString()`, which returns a `std::string`.

* Write getters (all declared `const`) called `getFamilyName()` and `getFirstName()` avoiding creation of unnecessary temporary variables. Modify `main()` to use these.

* Write setters called `setFamilyName()` and `setFirstName()`. Test these from `main()` again.

* Modify the original constructor to allow for `firstname` not being present. Hint: use a defaulted function parameter. What other function needs to be changed?

* Try to create a default-constructed `Person`. What do you find? Now try to create a `public:` default constructor (with an empty parameter list).

There is a third type of access specifier called `protected:`. Its meaning is the same as for `private:` except when inheritance is in use, when it means that (member functions defined within) derived classes have access to any members in the base class which were declared `protected:`. It's rare to find this in real code, although the next program we shall look at demonstrates its syntax and use.

Unlike with the `struct`s we met in Chapter 6, *private inheritance* is the default for `class`es. This means that any members which were public in the base class are not visible to users of the derived class. The literature tells us that (public) inheritance describes an *is-a* relationship, while the much rarer private inheritance describes an *is-implemented-by* relationship. Typically, this means that a **privately** derived class must provide (public) member functions which in turn call member functions of the base class. Interestingly, this doesn't necessarily mean that the size and binary layout of the privately derived class is different from that of the base class, unless it has additional member variables.

(*Protected inheritance*, as opposed to protected members, is even more unusual, and quite possibly has no useful purpose. It isn't discussed further here.)

The following program defines three `class`es, the second and third of which derive from the first. A collection of related classes that utilize inheritance is sometimes called an *inheritance hierarchy*. Quite a few changes have been made to `Person` so it is probably worth studying this first, before moving onto the new (derived) `Student` and `Employee` classes (quite a few member functions have been written on one line, to save space):

```cpp
// 09-person2.cpp : model Person, Student and Employee as a class inheritance hierarchy

#include <chrono>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;
using namespace std::chrono;

class Person {
public:
    Person(year_month_day dob) : dob{ dob } {}
    Person(year_month_day dob, string_view familyname, string_view firstname, bool familynamefirst = false)
        : dob{ dob }, familyname{ familyname }, firstname{ firstname },
          familynamefirst{ familynamefirst } {}
    virtual ~Person() {}
    void setFamilyName(string_view familyname) { familyname = familyname; }
    void setFirstName(string_view firstname) { firstname = firstname; }
    void setFamilyNameFirst(bool familynamefirst) { familynamefirst = familynamefirst; }
    string getName() {
        if (familyname.empty() || firstname.empty()) {
            return familyname + firstname;
        }
        else if (familynamefirst) {
            return familyname + ' ' + firstname;
        }
        else {
            return firstname + ' ' + familyname;
        }
    }
protected:
    const year_month_day dob;
private:
    string familyname, firstname;
    bool familynamefirst{};
};

class Student : public Person {
public:
    enum class Schooling;
    Student(const Person& person, const vector<string>& attended_classes = {}, Schooling school_type = Schooling::preschool)
        : Person{ person }, school_type{ school_type }, attended_classes{ attended_classes } {}
    const year_month_day& getDob() const { return dob; }
    const vector<string>& getAttendedClasses() const { return attended_classes; }
    enum class Schooling { preschool, elementary, juniorhigh, highschool, college, homeschool, other };
private:
    Schooling school_type;
    vector<string> attended_classes;
};

class Employee : public Person {
public:
    Employee(const Person& person, int employee_id, int salary = 0)
        : Person{ person }, employee_id{ employee_id }, salary{ salary } {}
    bool isBirthdayToday(year_month_day today) const { return dob.month() == today.month() && dob.day() == today.day(); }
    void setSalary(int salary) { salary = salary; }
    auto getDetails() const { return pair{ employee_id, salary }; }
private:
    const int employee_id;
    int salary;
};

int main() {
    Person genius{ { 1879y, March, 14d }, "Einstein", "Albert" };
    Student genius_student{ genius, { "math", "physics", "philosophy" }, Student::Schooling::other };
    Employee genius_employee{ genius, 1001, 15000 };

    cout << "Full name: " << genius_student.getName() << '\n';

    cout << "School classes: ";
    for (const auto& the_class : genius_student.getAttendedClasses()) {
        cout << the_class << ' ';
    }
    cout << '\n';

    auto [ id, salary ] = genius_employee.getDetails();
    cout << "ID: " << id << ", Salary: $" << salary << '\n';
    year_month_day next_bday{ 2024y, March, 14d };
    if (genius_employee.isBirthdayToday(next_bday)) {
        cout << "Happy Birthday!\n";
    }
}
```

Many things to note about this program:

* A second constructor for `Person` taking only a `std::chrono::year_month_day` has been added. Setters can be used later to initialize or modify the other three member variables, which are left defaulted by this constructor (empty for the two `std::string`s and `false` for the `bool`).

* A `virtual` destructor has been added to `Person`; a key C++ concept is that base classes often need a virtual destructor. This is so that any heap objects of type `Student` or `Employee` assigned to a pointer of type `Person*` (including use of smart pointers), the correct destructor of the **derived** class can be found and thus called, avoiding memory leaks.

* The `getName()` function returns the name(s) provided by either the constructor or the setter(s) as a single `std::string`, ordered according to the member variable `familynamefirst`. (Hopefully this attempt at cultural inclusion doesn't offend anyone!)

* The member variable `dob` is declared `protected:`, the other three are `private:`, as before.

* The `Student` type is derived from `Person` using the keyword `public`. If this keyword were omitted, none of `Person`'s `public:` members would be visible to users of `Student`, as `class`es default to private inheritance. The syntax is exactly as for `Pixel` inheriting from `Point` in Chapter 6.

* An `enum class` called `Schooling` is also forward-declared so that it is able to be used as a constructor parameter.

* The three `Student` constructor parameters are an existing `Person` object used to initialize the base class part, an optional `vector<string>` (needed to be passed by value in this case), and an optional value from the enumeration set `Schooling`.

* The base class portion of `Student` is initialized as `Person{ person }` where `person` is of type `const Person&`. Then the other two fields of `Student` are initialized. The constructor parameter variable `attended_classes` is passed as a `const vector<string>&` so that only one copy is made, which is when the member variable of the same name is initialized.

* A `public:` member function `getDob()` makes the `protected:` data member of the base class `dob` available to **users** of the derived class, in this case `Student`. It is declared `const` and returns a `const`-reference.

* The member function `getAttendedClasses()` returns a `const`-reference to `attended_classes`, therefore this `std::vector<string>` is made visible to the function which calls this member function, but is not modifiable.

* The `Employee` constructor takes three parameters, the third of which is optional. The base class portion is initialized in the same way as for `Student`.

* The member function `isBirthdayToday()` takes a `std::chrono::year_month_day` as a parameter and compares the return values of the `day()` and `month()` members with those of `dob`, returning `true` if they are the same, or `false` otherwise. (We're pretending "today" is March 14, 2024, so this function always returns `true`.)

* The member variable `employee_id` is not meant to be able to be changed, so is declared `const`. The setter `setSalary()` is defined so that `salary` can be updated, while the getter `getDetails()` returns an aggregate of both derived class member variables by value.

**Experiment:**

* Modify `main()` to remove the need for the variable `Person genius`. Hint: there will be some necessary code duplication.

* Add some other `Student`s and `Employee`s. Experiment with minimalist and partial initializations.

* Experiment with the member functions not previously called from `main()`.

* Write a getter/setter pair to retrieve/modify `school_type` for `Student`.

* Write a second constructor for `Student` which takes (in addition) the parameters needed to define a `Person`. Initialize the `Person` base class from these parameters. Should these parameters before or after the ones specific to `Student`? Can they be defaulted?

* Write a second constructor for `Employee` to accomplish the same thing.

* Add `getDob()` to `Employee`, as for `Student`. Now try to add it to `Person`, what do you find? Would a single `public:` getter in the base class be more useful than a `protected:` member variable?

* Add member functions `addAttendedClass()` and `removeAttendedClass()` to `Student`. Make them smart enough to handle duplicates/invalid parameters.

* Add the field `job_title` to `Employee` as well as support for this in the relevant getters/setters/constructors.

## Copying and comparisons

So far we have created stack objects and accessed their member functions. Often, you will want to make copies of these objects, whether its passing them to, or returning them from, functions, or storing them in a container. Sometimes they are passed by reference instead, and this is preferred for (larger) user-defined types, as passing by value has to cause a (potentially) expensive copy to be made. However the class designer needs to be aware of all of the copy and move operations that might be required of object instances, and must ensure they are implemented correctly.

There are **six** operations which are involved in this discussion: three constructors, two assignment operators and the destructor. All of these can be explicitly declared `= default` or `= delete`. (We have already discovered that defining a constructor which takes parameters causes the default constructor to no longer be generated.) The other two constructors and the two assignment operators each come in two forms: copy and move, as shown in the next code fragment, using `Person` as the name of the class, and a code example of when the operation would be called. (The *boilerplate* code shown here can be copied verbatim for other `class`es, simply changing every occurence `Person` to the name of the class. The actual variable parameter name, often being `rhs`, has been omitted; these are the minimalist forms of the member function declarations.)

```cpp
class Person {
// rest of class definition omitted
public:
    // "default constructor"
    Person() = delete;                           //  Person p1{}, p2(), p3;
    // "copy constructor"
    Person(const Person&) = delete;              //  Person p4{ p1 }, p5(p2);
    // "copy assignment operator"
    Person& operator= (const Person&) = delete;  //  Person p6; p6 = p1;
    // "move constructor"
    Person(Person&&) = delete;                   //  Person p7{ std::move(p2) };
    // "move assignment operator"
    Person& operator= (Person&&) = delete;       //  Person p8; p8 = std::move(p3);
    // "destructor"
    ~Person() = delete;                          //  Any Person object going out of scope
};
```

**Experiment:**

* Add the above code to the end of the definition of the `Person` class from `09-person1.cpp`. Why doesn't the code compile now? Hint: read the error message carefully. Fix this by `= default`ing just one of the operations.

* Try to create `p4` to `p8` as above, `= default`ing the operations as necessary. Are the (copied/assigned) objects in a valid state? Hint: try to use their member functions.

* Now use `auto` instead of `Person`, for example: `auto p1{};`. Does the code still compile? Are the objects valid?

As can be seen we are aided by the compiler in the provision of object duplication, as many (probably most) of the classes you will write have valid (`= default`) *special member functions* generated as they are needed. (The exact rules of when and which of them are generated automatically are slightly arcane; you may find references to the "rule of five" for Modern C++ online or in literature.) However, the exception proves the rule, and I would suggest declaring the first five of these `= delete` when writing a new class, enabling them one by one with `= default` as any compiler errors present themselves, ensuring that objects can be copied and moved correctly. Most member variable types are compatible with default copy/move semantics, the obvious one that isn't being raw pointers. Writing custom special member functions for derived classes is sometimes tricky, as it involves manually invoking the correct special member function on the base class. (Hopefully you won't have to do this very often, further explanation is beyond the scope of this Tutorial.) Be aware that if the member variables (of a base or derived class) themselves obey the usual rules of copying (such as `int`, `double`, `std::string`, `std::shared_ptr<T>`, but not `char *` for example) then the `=default` special member functions will always work correctly.

Often we will want to compare objects for equivalence. Some containers, such as `std::unordered_map`, mandate that `operator==` is defined, while others such as `std::map`, require `operator<`, so we can only store objects in associative containers if the required `operator`s have been defined. The following code defines a rudimentary member `operator==` for the `Person` class from `09-person1.cpp`, the syntax from Chapter 6 should be familiar:

```cpp
class Person {
// rest of class definition omitted
public:
    bool operator== (const Person& rhs) { return getName() == rhs.getName(); }
};
```

Alternatively, global `operator==` can be overloaded for `Person`, as demonstrated here:

```cpp
bool operator== (const Person& lhs, const Person& rhs) {
    return lhs.getName() == rhs.getName();
}
```

Defining either one of these variants of `operator==` is sufficient to make the following code compile:

```cpp
int main() {
    Person person1 { { 2000, 1, 1 }, "John", "Smith" };
    auto person2{ person1 };
    if (person1 == person2) {
        cout << "Same!\n";
    }
    else {
        cout << "Different!\n";
    }
}
```

A couple of things to note:

* The return type of both variants is `bool` (not `Person&`).

* The member function version has access to its own member variables and those of `rhs` (even though it doesn't access them directly), while the global (free) function version relies on public getters.

**Experiment:**

* Define `person2` with a different date of birth. How do they compare now?

* Can you fix this problem by modifying the member `operator==`?

* Do the same with global `operator==`?

* Write a member `operator==` for `Employee` from `09-person2.cpp`, that compares the `employee_id` member (only) for equality, and then test this operator.

## Friend functions and classes

Friends have access to all members of the `class` that declares them a `friend`, including those declared `private:` or `protected:`. Sometimes this is desirable, as shown in the following program:

```cpp
// 09-person3.cpp : define operator<=> for Person class

#include <iostream>
using namespace std;

struct Date {
    int year{}, month{}, day{};
    auto operator<=>(const Date&) const = default;
};

class Person {
public:
    Person(const Date& dob, string_view familyname, string_view firstname)
        : dob{ dob }, familyname{ familyname }, firstname{ firstname }
        {}
    string getName() const { return firstname + ' ' + familyname; }
    const auto& getDob() const { return dob; }
    auto operator<=>(const Person&) const = default;
    friend ostream& operator<< (ostream&, const Person&);
private:
    string familyname, firstname;
    const Date dob;
};

ostream& operator<< (ostream& os, const Person& p) {
    os << "Name: " << p.getName() << ", DOB: "
        << p.dob.year << '/' << p.dob.month << '/' << p.dob.day;
    return os;
}

int main() {
    Person person1{ { 2000, 1, 1 }, "Doe", "John" },
        person2{ { 1987, 11, 31 }, "Doe", "John" };
    cout << "person1: " << person1 << '\n';
    cout << "person2: " << person2 << '\n';
    if (person1 == person2) {
        cout << "Same person!\n";
    }
    else {
        cout << "Different person!\n";
    }

    cout << "person1 is ";
    if (person1.getDob() > person2.getDob()) {
        cout << "younger than ";
    }
    else if (person1.getDob() < person2.getDob()) {
        cout << "older than ";
    }
    else {
        cout << "the same age as ";
    }
    cout " person2\n";
}
```

Some things to note about this program:

* Member `operator<=>` (the "spaceship operator") is defaulted for this roll-your-own `Date`; this is all that is needed for the equality and ordering comparisons to be defined for this class, with ordering performed member-wise starting with the first data member.

* Within the definition of `Person`, global `operator<<` is declared as a `friend` function. This is more boilerplate that you can use in your own classes, changing parameter `const Person&` to the name of your class. (They are identical to normal function declarations, other than the use of the `friend` keyword.)

* Member `operator<=>` is defaulted for `Person`; with this code the `std:::string` members will be compared (`familyname` before `firstname`), before the `Date` members are compared.

* Global `operator<<` is also defined for `Person`, allowing objects to be put to `cout` (and any other `std::ostream`s) using `<<`. This needs to be a `friend` because it accesses `dob`.

**Experiment:**

* Give `person2` the same date of birth as `person1`. Does the program produce the expected output?

* Now give them different names. What output do you get?

* Define global `operator<<` for `Date`. Can you remove the need for `operator<<` for `Person` to itself be a `friend` of `class Person`?

* Compare a few `Person` instances with similar or same family names and first names, storing them in a `std::set<Person>`. Write code to output them telephone-book style. Are they ordered in the way you would expect?

Classes can be declared `friend`s as well as functions, although this use is probably less common. The following program defines two `class`es `A` and `B` which are mutual friends, thus allowing member functions of either to access each other's `private:` members.

```cpp
// 09-friends.cpp : two classes as friends of each other

#include <iostream>
using namespace std;

class B;

class A {
public:
    friend class B;
    void a(B& other);
private:
    int m_a{42};
};

class B {
public:
    friend class A;
    void b(A& other) { cout << "b():" << other.m_a << '\n'; }
private:
    double m_b{1.414};
};

void A::a(B& other)
{
    cout << "a():" << other.m_b << '\n';
}

int main() {
    A obj_a{};
    B obj_b{};

    obj_a.a(obj_b);
    obj_b.b(obj_a);
}
```

A few things to note about this program:

* In order for `friend class B` to be written within `class A`, the **delaration** `class B;` must appear beforehand. This forward declaration allows a reference (or pointer, including smart pointer) to `B` to be taken and used, but members cannot (yet) be accessed.

* The definition of `class A`'s member function `a()` must be written outside of the function body, **after** the definition of `class B`. It is important to appreciate that it is **still** a member function, not a global function, when written after the class definition *non-inline* (or *out-of-line*) in this way using the scope resolution operator (`::`).

* The definition of `class B` declares `friend class A` and its member function `b()` can access `other.m_a` for this reason.

* The member variables need a prefix (such as `m_`) because member functions called `a()` and `b()` are used, and the names would clash.

**Experiment:**

* Change the types of the member variables and their values. Does the program compile without further changes?

* Add a defaulted second parameter to `a()` and `b()` which is used to set the value of other class's member variable.

* Go back to `Person` from `09-person1.cpp` and define `getName()` outside the class body. Does it still need a declaration inside the class body? Can this definition now appear after `main()`? What do free functions and non-inline member functions have in common?

## Polymorphism

The literature tells us that polymorphism "is a concept in type theory wherein a name may denote instances of many different classes as long as they are related by some common superclass" (Booch, "Object-Oriented Analysis and Design with Applications"[^1]). What this means in practice is that derived class objects can be manipulated through a pointer or reference to a base class type, with member function selection being resolved **at run-time**. This probably doesn't sound too exciting, but is important in order for C++ to be classified as an object-**oriented** programming language, as opposed to merely object-**based**. Member functions whose selection is determined at run-time are called *virtual* functions, and are defined with the `virtual` keyword (which we have already met when discussing virtual destructors in base classes).

The following code defines (part of) an *abstract base class* called `Virtual`; it makes use of virtual functions in the following forms:

```cpp
class Virtual {
public:
    virtual void f();
    virtual void g() = 0;
    virtual void h() override;
    virtual void k() override final;
};
```

The meanings implied for these member functions in the context of the `virtual` keyword are as follows:

* `f()` is a function in a base class or derived class which can (optionally) be redefined (in the derived class).

* `g()` is a *pure-virtual* function of an abstract base class, which is not usually defined in this class and **must** be defined in a class that derives from it, in order for objects of the derived class to able to be created. Objects of an abstract class **cannot** be instantiated; attempting to do so would trigger a compile-time error.

* `h()` is a function in a derived class which redefines (overrides) a previous definition; the function signature must exactly match that in the base class (including `const` and `noexcept` qualifiers). This function **can** itself be redefined in any subsequently derived class.

* `k()` is the same as `h()` except this function **cannot** again be redefined in a subsequently derived class.

The following program demonstrates all of these uses in a more complex hierarchy deriving from an abstract `Shape` class:

```cpp
// 09-shape.cpp : Shape class hierarchy demonstrating polymorphism

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Shape {
public:
    struct Point;
    Shape(int sides) : sides{ sides } {}
    Shape(int sides, Point center) : sides{ sides }, center{ center } {}
    virtual void draw(ostream& os) const = 0;
    virtual string getSides() const { return to_string(sides); }
    void moveBy(int dx, int dy) { center.x += dx; center.y += dy; }
    const Point& getCenter() const { return center; }
    virtual ~Shape() { cerr << "~Shape()\n"; }
    struct Point {
        int x{}, y{};
    };
private:
    int sides;
    Point center;
};

ostream& operator<< (ostream& os, const Shape::Point& pt) {
    return os << '(' << pt.x << ',' << pt.y << ')';
}

class Triangle final : public Shape {
public:
    Triangle(int side) : Shape{ 3 }, side{ side } {}
    Triangle(int x, int y, int side) : Shape{ 3, {x, y} }, side{ side } {}
    virtual void draw(ostream& os) const override {
        os << " /\\\n/__\\\nSide: " << side << "\nAt: " << getCenter() << '\n';
    }
private:
    int side;
};

class Circle : public Shape {
public:
    Circle(int radius) : Shape{ 0 }, radius{ radius } {}
    Circle(int x, int y, int radius) : Shape{ 0, {x, y} }, radius{ radius } {}
    virtual void draw(ostream& os) const override final {
        os << " _\n(_)\nRadius: " << radius << "\nAt: " << getCenter() << '\n';
    }
    virtual string getSides() const override final { return "infinite"; }
private:
    int radius;
};

class Rectangle : public Shape {
public:
    Rectangle(int side_x, int side_y) : Shape{ 4 }, side_x{ side_x }, side_y{ side_y } {}
    Rectangle(int x, int y, int side_x, int side_y)
        : Shape{ 4, {x ,y} }, side_x{ side_x }, side_y{ side_y } {}
    virtual void draw(ostream& os) const override {
        os << " ____\n|____|\nSize: " << side_x << 'x' << side_y << "\nAt: " << getCenter() << '\n';
    }
protected:
    int side_x, side_y;
};

class Square final : public Rectangle {
public:
    Square(int side) : Rectangle{ side, side } {}
    Square(int x, int y, int side) : Rectangle{ x, y, side, side } {}
    virtual void draw(ostream& os) const override final {
        os << " _\n|_|\nSide: " << side_x << "\nAt: " << getCenter() << '\n';
    }
};

int main() {
    vector<Shape*> shapes;
    shapes.push_back(new Circle{ 10 });
    shapes.push_back(new Triangle{ 10, 20, 15 });
    shapes.push_back(new Rectangle{ 10, 5 });
    shapes.push_back(new Square{ 25, 100, 50 });
    shapes[0]->moveBy(20, 50);

    for (auto& s : shapes) {
        s->draw(cout);
        cout << "Sides: " << s->getSides() << '\n';
        delete s;
        s = nullptr;
    }
}
```

A lot of things to note about this program:

* The definition of `Shape` contains two constructors, one pure-virtual member function, one virtual function, two non-virtual functions and a virtual destructor. It also defines `Point` as a local `struct`. In addition, two `private:` member variables are defined.

* Both of the member variables are guaranteed to be initialized whenever a derived class calls either one of the `Shape` constructors.

* The two non-virtual member functions are not meant to be redefined in derived classes, and provide functionality for both the member variables that `Shape` defines (member functions of a base class **cannot** access member functions or variables of a derived class).

* To reduce code duplication, an overload of `operator<<` which handles `Shape::Point`s is provided (above the derived classes which use it).

* All of the derived classes provide an implementation of `draw()`. In addition, `Circle` provides its own implementation of `getSides()`.

* The definition of `Triangle` is the simplest of those which derive from `Shape` and represents an equilateral triangle; public inheritance needs to be specified as for all the other derived classes in this hierarchy. This class definition is qualified with the `final` keyword, which means that no class can derive from `Triangle` (it is therefore the "final" class of that inheritance "branch"). The constructors both call a `Shape` constructor. A single member variable `side` is defined which is used by the definition of `draw()`.

* The definition of `Circle` is very similar to that of `Triangle`; this is a common theme with class heirarchies. It redefines `getSides()` in addition to defining and using a member variable `radius`.

* The definition of `Rectangle` defines two `protected:` member variables which are initialized by both constructors and output by `draw()`.

* The definition of `Square` is, as for `Triangle`, qualified with `final`, and inherits from `Rectangle` (instead of directly from `Shape`). Since `Rectangle`'s constructor calls that for `Shape`, neither of `Square`'s constructors need to call it directly. It can access the `protected:` member variables of `Rectangle` within its definition of `draw()`.

* In `main()` a `std::vector<Shape*>` (vector of raw pointers to `Shape`) is created, and the populated with the return value from `new`; no intermediate pointer is used. (Since `Shape` is an abstract type it is not possible to create a `std::vector<Shape>`, as these would need to be able to be default-initialized in order for the container to be created.)

* The output from the range-for loop proves that polymorphism is being used, as the loop variable `s` is a (reference to a) pointer to the base class type of the hierarchy.

* The member functions `draw()` and `getSides()` can be called from `main()` becuase they were declared `public:` in **all** of the base and derived classes.

* The `Shape` objects are deleted as soon as they have been output; setting a pointer that is finished with to `nullptr` straightaway is good practice as it protects against the possibility of trying to access or delete a *dangling pointer*. Better practice still would be to use a `std::vector` of smart pointers.

**Experiment:**

* Try to create an object of type `Shape()` that would normally use the first constructor (which takes a single `int` parameter). What do you find?

* Move all the calls to `getCenter()` into `main()`.

* Write an overload of `operator<<` which handles `const Shape&`. Does this need to be a `friend` function? Decide whether you think this is neat, or just being too clever.

* Remove the `&` from the range-for loop in `main()`. What is the (single, invisible) difference about the program?

* Write a (`virtual`) destructor for all of the classes besides `Shape()`, observing how the output changes. What do you learn about order of destruction in a class hierarchy? What happens if you omit `Shape`s own destructor?

* Try to derive an empty class from `Square`. What compilation error do you get?

* Try removing the `const` qualifier from the overload of `getSides()` in `Circle`. Does the code still compile? What does this tell you about the effect of `const` on a member function's signature?

* Try to derive from `Circle`. What happens if you try to overload `draw()`?

* Consider the best way (least code duplication) to add a member function `getArea()` (which returns a `double`) to `Shape`, and implement this for all classes in the hierarchy.

[^1]: Grady Booch, Robert A. Maksimchuk, Michael W. Engle, Bobbi J. Young, Jim Conallen, Kelli A. Houston *Object-Oriented Analysis and Design with Applications* (3rd ed. Pearson, 2007, ISBN-13: 9780201895513)

*All text and program code &copy;2019-2025 Richard Spencer, all rights reserved.*
