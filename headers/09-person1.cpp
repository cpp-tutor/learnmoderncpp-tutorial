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
		: m_dob{ dob }, m_familyname{ familyname }, m_firstname{ firstname }
		{}
	string getName() const { return m_firstname + ' ' + m_familyname; }
private:
    const Date m_dob;
    string m_familyname, m_firstname;
};


int main() {
	Person genius{ { 1879, 3, 14 }, "Einstein", "Albert" };
	cout << genius.getName() << '\n';
}
