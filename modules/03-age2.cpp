// 03-age2.cpp : get and then test an integer is within range

import std.core;
using namespace std;

int main() {
    int alice_age{};
    cout << "Please enter your guess for Alice\'s age: ";
    cin >> alice_age;
    if (6 <= alice_age and alice_age <= 11) {
        cout << "A good guess!\n";
    }
    else {
        cout << "Not a good guess.\n";
    }
}
