// 04-overload.cpp : calling a function with different types of arguments and parameters

import std.core;
using namespace std;

void f(int i) {
    cout << "f(): int: " << i << '\n';
}

void f(double d) {
    cout << "f(): double: " << d << '\n';
}

int main() {
    f(1);
    f(2.5);
}
