// 03-ifinitializer.cpp : use of variable initializer in if statement

import std.core;
using namespace std;

int main() {
    cout << "Please enter a positive number:\n";
    unsigned n{};
    cin >> n;
    cout << "The least significant digit was ";
    if (auto m = n % 10; m < 5) {
        cout << "less than five (" << m << ")\n";
    }
    else {
        cout << "five or more (" << m << ")\n";
    }
}
