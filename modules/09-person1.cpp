// 09-person1.cpp : model Person as a class with constructor

import std;
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
