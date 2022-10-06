// 09-person3.cpp : define operator== and operator<< for Person class

#include <iostream>
using namespace std;

struct Date {
    int year{}, month{}, day{};
};

bool operator== (const Date& lhs, const Date& rhs) {
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

class Person {
public:
    Person(const Date& dob, string_view familyname, string_view firstname)
        : dob{ dob }, familyname{ familyname }, firstname{ firstname }
        {}
    string getName() const { return firstname + ' ' + familyname; }
    friend bool operator== (const Person&, const Person&);
    friend ostream& operator<< (ostream&, const Person&);
private:
    const Date dob;
    string familyname, firstname;
};

bool operator== (const Person& lhs, const Person& rhs) {
    return lhs.familyname == rhs.familyname
        && lhs.firstname == rhs.firstname
        && lhs.dob == rhs.dob;
}

ostream& operator<< (ostream& os, const Person& p) {
    os << "Name: " << p.getName() << ", DOB: "
        << p.dob.year << '/' << p.dob.month << '/' << p.dob.day;
    return os;
}

int main() {
    Person person1{ { 2000, 1, 1 }, "John", "Doe" },
        person2{ { 1987, 11, 31 }, "John", "Doe" };
    cout << "person1: " << person1 << '\n';
    cout << "person2: " << person2 << '\n';
    if (person1 == person2) {
        cout << "Same person!\n";
    }
    else {
        cout << "Different person!\n";
    }
}
