// 02-references.cpp : introducing l-value references

import std;
using namespace std;

int alice_age{ 9 };

int main() {
    println("Alice\'s age is {}", alice_age);
    int& alice_age_ref = alice_age;
    alice_age_ref = 10;
    println("Alice\'s age is now {}", alice_age);
}
