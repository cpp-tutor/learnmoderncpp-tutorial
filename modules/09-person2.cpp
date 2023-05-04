// 09-person2.cpp : model Person, Student and Employee as a class inheritance hierarchy

import std;
using namespace std;

class Person {
public:
    struct Date;
    Person(Date dob) : dob{ dob } {}
    Person(Date dob, string_view familyname, string_view firstname, bool familynamefirst = false)
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
    struct Date {
        unsigned short year{};
        unsigned char month{}, day{};
    };
protected:
    const Date dob;
private:
    string familyname, firstname;
    bool familynamefirst{};
};

class Student : public Person {
public:
    enum class Schooling;
    Student(const Person& person, const vector<string>& attended_classes = {}, Schooling school_type = Schooling::preschool)
        : Person{ person }, school_type{ school_type }, attended_classes{ attended_classes } {}
    const Date& getDOB() const { return dob; }
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
    bool isBirthday(Date today) const { return dob.month == today.month && dob.day == today.day; }
    void setSalary(int salary) { salary = salary; }
    auto getDetails() const { return pair{ employee_id, salary }; }
private:
    const int employee_id;
    int salary;
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
