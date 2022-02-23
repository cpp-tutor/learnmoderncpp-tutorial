// 04-absolute1.cpp : return the absolute value of a global variable

import std.core;
using namespace std;

int value;

int abs_value() {
    if (value < 0) {
        return -value;
    }
    return value;
}

int main() {
    cout << "Please enter a positive or negative integer: ";
    cin >> value;
    auto a = abs_value();
    cout << "The absolute value is: " << a << '\n';
}
