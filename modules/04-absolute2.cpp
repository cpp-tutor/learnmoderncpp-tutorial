// 04-absolute2.cpp : return the absolute value of a local variable

import std;
using namespace std;

int abs_value(int v) {
    if (v < 0) {
        return -v;
    }
    else {
        return v;
    }
}

int main() {
    int value{};
    cout << "Please enter a positive or negative integer: ";
    cin >> value;
    auto a = abs_value(value);
    cout << "The absolute value is: " << a << '\n';
}
