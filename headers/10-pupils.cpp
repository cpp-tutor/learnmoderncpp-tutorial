// 10-pupils.cpp : use of shared_ptr and weak_ptr to avoid dependency cycle

#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <string_view>
using namespace std;

struct Pupil;

struct Class {
    Class(int r, string_view s, string_view t)
        : room{ r }, subject{ s }, teacher_name{ t } {}
    int room;
    string subject, teacher_name;
    vector<shared_ptr<Pupil>> pupils;
};

struct Pupil {
    Pupil(string_view n) : name{ n } {}
    string name;
    vector<weak_ptr<Class>> classes;
};

int main() {
    vector<shared_ptr<Class>> AllClasses{
        make_shared<Class>(101, "English", "Mr White"),
        make_shared<Class>(150, "Math", "Miss Black")
    };
    vector<shared_ptr<Pupil>> AllPupils{
        make_shared<Pupil>("Paul"),
        make_shared<Pupil>("Percy"),
        make_shared<Pupil>("Perry"),
        make_shared<Pupil>("Phoebe"),
        make_shared<Pupil>("Penny"),
        make_shared<Pupil>("Patricia")
    };

    auto add_to_class = [&](string_view c, string_view p) {
        auto iter_c = find_if(cbegin(AllClasses), cend(AllClasses),
            [&](auto ec){ return c == ec->subject; });
        auto iter_p = find_if(cbegin(AllPupils), cend(AllPupils),
            [&](auto ep){ return p == ep->name; });
        if (iter_c != cend(AllClasses) && iter_p != cend(AllPupils)) {
            (*iter_c)->pupils.push_back(*iter_p);
            (*iter_p)->classes.push_back(*iter_c);
        }
        else {
            cerr << "Could not add " << p << " to " << c << '\n';
        }
    };

    add_to_class("English", "Paul");
    add_to_class("English", "Percy");
    add_to_class("English", "Phoebe");
    add_to_class("English", "Penny");
    add_to_class("Math", "Paul");
    add_to_class("Math", "Perry");
    add_to_class("Math", "Phoebe");
    add_to_class("Math", "Patricia");

    AllClasses.emplace_back(make_shared<Class>(260, "IT", "Mrs Brown"));
    add_to_class("IT", "Percy");
    add_to_class("IT", "Perry");

    for (const auto& c : AllClasses) {
        cout << "Room: " << c->room << "\nSubject: " << c->subject
            << "\nTeacher: " << c->teacher_name << "\nPupils: ";
        for (const auto& p : c->pupils) {
            cout << p->name << ' ';
        }
        cout << '\n';
    }
    
    for (;;) {
        cout << "Please enter a pupil name (blank line to quit): ";
        string s;
        getline(cin, s);
        if (s.empty()) {
            break;
        }
        auto iter_p = find_if(cbegin(AllPupils), cend(AllPupils),
            [&](auto ep){ return s == ep->name; });
        if (iter_p != cend(AllPupils)) {
            cout << "Classes: ";
            for (const auto& c : (*iter_p)->classes) {
                if (auto pc = c.lock(); pc) {
                    cout << pc->subject << ' ';
                }
            }
            cout << '\n';
        }
        else {
            cout << "Name not recognized!\n";
        }
    }
}    
