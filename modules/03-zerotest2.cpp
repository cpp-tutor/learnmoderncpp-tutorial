// 03-zerotest2.cpp : test an integer value against zero and use conditional expression

import std.core;
using namespace std;

int main() {
    cout << "Please enter an integer value: ";
    int n{};
    cin >> n;
    cout << "The value entered was " << ( (n) ? "nonzero\n" : "zero\n" );
}
