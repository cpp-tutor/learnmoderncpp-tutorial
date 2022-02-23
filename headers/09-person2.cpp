// 09-person2.cpp : model Person, Student and Employee as a class inheritance hierarchy

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

class Person {
public:
	struct Date;
	Person(Date dob) : m_dob{ dob } {}
	Person(Date dob, string_view familyname, string_view firstname, bool familynamefirst = false)
		: m_dob{ dob }, m_familyname{ familyname }, m_firstname{ firstname },
		  m_familynamefirst{ familynamefirst } {}
	virtual ~Person() {}
	void setFamilyName(string_view familyname) { m_familyname = familyname; }
	void setFirstName(string_view firstname) { m_firstname = firstname; }
	void setFamilyNameFirst(bool familynamefirst) { m_familynamefirst = familynamefirst; }
	string getName() {
		if (m_familyname.empty() || m_firstname.empty()) {
			return m_familyname + m_firstname;
		}
		else if (m_familynamefirst) {
			return m_familyname + ' ' + m_firstname;
		}
		else {
			return m_firstname + ' ' + m_familyname;
		}
	}
	struct Date {
		unsigned short year{};
		unsigned char month{}, day{};
	};
protected:
	const Date m_dob;
private:
	string m_familyname, m_firstname;
	bool m_familynamefirst{};
};

class Student : public Person {
public:
	enum class Schooling;
	Student(const Person& person, vector<string> attended_classes = {}, Schooling school_type = Schooling::preschool)
		: Person{ person }, m_school_type{ school_type }, m_attended_classes{ move(attended_classes) } {}
	const Date& getDOB() const { return m_dob; }
	const vector<string>& getAttendedClasses() const { return m_attended_classes; }
	enum class Schooling { preschool, elementary, juniorhigh, highschool, college, homeschool, other };
private:
	Schooling m_school_type;
	vector<string> m_attended_classes;
};

class Employee : public Person {
public:
	Employee(const Person& person, int employee_id, int salary = 0)
		: Person{ person }, m_employee_id{ employee_id }, m_salary{ salary } {}
	bool isBirthday(Date today) const { return m_dob.month == today.month && m_dob.day == today.day; }
	void setSalary(int salary) { m_salary = salary; }
	auto getDetails() const { return pair{ m_employee_id, m_salary }; }
private:
	const int m_employee_id;
	int m_salary;
};

int main() {
	Person genius{ { 1879, 3, 14 }, "Einstein", "Albert" };
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
	Person::Date next_bday{ 2020, 3, 14 };
	if (genius_employee.isBirthday(next_bday)) {
		cout << "Happy Birthday!\n";
	} 
}
