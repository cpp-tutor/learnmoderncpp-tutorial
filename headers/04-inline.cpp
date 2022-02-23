// 04-inline.cpp : use of an inline function

#include <iostream>
using namespace std;

inline void swap(int& x, int& y) {
    auto z = x;
    x = y;
    y = z;
}

int main() {
    int a = 1, b = 2;
    cout << "(1) a = " << a << ", b = " << b << '\n';
    swap(a, b);
    cout << "(2) a = " << a << ", b = " << b << '\n';
}
