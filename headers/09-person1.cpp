// 09-person1.cpp : model Person as a class with constructor

#include <iostream>
#include <string>
#include <string_view>
using namespace std;

struct Date {
    int year{}, month{}, day{};
};

class Person {
public:
    Person(const Date& dob, string_view familyname, string_view firstname)
        : dob{ dob }, familyname{ familyname }, firstname{ firstname }
        {}
    string getName() const { return firstname + ' ' + familyname; }
private:
    const Date dob;
    string familyname, firstname;
};


int main() {
    Person genius{ { 1879, 3, 14 }, "Einstein", "Albert" };
    cout << genius.getName() << '\n';
}
