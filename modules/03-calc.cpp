// 03-calc.cpp : simple calculator with four functions

import std.core;
using namespace std;

int main() {
    int r{}, x{}, y{};
    char op{};
    cout << "Please enter a calulation (number op number, op is one of +-*/):\n";
    cin >> x >> op >> y;
    switch (op) {
    case '+':
        r = x + y;
        break;
    case '-':
        r = x - y;
        break;
    case '*':
        r = x * y;
        break;
    case '/':
        if (y) {
            r = x / y;
        }
        else {
            cerr << "Error: divide by zero.\n";
        }
        break;
    default:
        cerr << "Error: invalid op.\n";
        break;
    }
    cout << "Result: " << r << '\n';
}
