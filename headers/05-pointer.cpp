// 05-pointer.cpp : write a variables value through a pointer

#include <iostream>
using namespace std;

int main() {
    int i{ -1 }, j{};
    int *p;          // define p as an int*
    p = &i;          // set p to address of i
    cout << "(1) p = " << p << ", *p = " << *p << ", i = " << i << '\n';
    cout << "Please enter an integer: ";
    cin >> j;
    *p = j;          // assign the value of j to the variable p points to
    cout << "(2) p = " << p << ", *p = " << *p << ", i = " << i << '\n';
}
