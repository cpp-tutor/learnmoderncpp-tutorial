// 09-person3.cpp : define operator<=> for Person class

import std;
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
