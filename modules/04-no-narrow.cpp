// 04-no-narrow.cpp : calling a function with different types of arguments and parameters

import std.core;
using namespace std;

void f(int i) {
    cout << "f(): received int: " << i << '\n';
}

void g(double d) {
    cout << "g(): recieved double: " << d << '\n';
}

int main() {
    f(1);
    g(1);
    f(2.5);
    g(2.5);
}
