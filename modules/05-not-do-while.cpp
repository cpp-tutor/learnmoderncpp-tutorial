// 05-not-do-while.cpp : alternative to post-condition loop

import std.core;
using namespace std;

int main() {
    int i{};
    cout << "Please enter a negative number: ";
    cin >> i;
    while (i >= 0) {
        cout << "Please enter a negative number: ";
        cin >> i;
    }
    cout << "You entered: " << i << '\n';
}
