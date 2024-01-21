// 04-inline.cpp : use of an inline function

import std;
using namespace std;

inline void swap(int& x, int& y) {
    auto z = x;
    x = y;
    y = z;
}

int main() {
    int a = 1, b = 2;
    println("(1) a = {}, b = {}", a, b);
    swap(a, b);
    println("(2) a = {}, b = {}", a, b);
}
