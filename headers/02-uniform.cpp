// 02-uniform.cpp : avoid compiler error with uniform initialization and explicit narrowing cast

#include <iostream>
using namespace std;

int main() {
    // int c = { 2.5 };                 // Error: this does NOT compile
    int c = { static_cast<int>(2.5) };  // while this does
    double d = { 1 };                   // and so does this
    cout << "c = " << c << ", d = " << d << '\n';
}
