// 03-age1.cpp : get and then display an integer

import std.core;
using namespace std;

int main() {
    int alice_age{};
    cout << "Please enter your guess for Alice\'s age: ";
    cin >> alice_age;
    cout << "You guessed " << alice_age << "!\n";
}
