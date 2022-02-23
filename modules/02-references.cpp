// 02-references.cpp : introducing l-value references

import std.core;
using namespace std;

int alice_age{ 9 };

int main() {
    cout << "Alice\'s age is " << alice_age << '\n';
    int& alice_age_ref = alice_age;
    alice_age_ref = 10;
    cout << "Alice\'s age is now " << alice_age << '\n';
}
