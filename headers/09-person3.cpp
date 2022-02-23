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
		: m_dob{ dob }, m_familyname{ familyname }, m_firstname{ firstname }
		{}
	string getName() const { return m_firstname + ' ' + m_familyname; }
	friend bool operator== (const Person&, const Person&);
	friend ostream& operator<< (ostream&, const Person&);
private:
    const Date m_dob;
    string m_familyname, m_firstname;
};

bool operator== (const Person& lhs, const Person& rhs) {
	return lhs.m_familyname == rhs.m_familyname
		&& lhs.m_firstname == rhs.m_firstname
		&& lhs.m_dob == rhs.m_dob;
}

ostream& operator<< (ostream& os, const Person& p) {
	os << "Name: " << p.getName() << ", DOB: "
		<< p.m_dob.year << '/' << p.m_dob.month << '/' << p.m_dob.day;
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
