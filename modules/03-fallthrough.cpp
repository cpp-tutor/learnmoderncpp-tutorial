// 03-fallthrough.cpp : demonstrate case clauses without break

import std.core;
using namespace std;

int main() {
    cout << "Please enter an integer between zero and three:\n";
    int n{};
    cin >> n;
    switch (n) {
    case 0:
        cout << "Number is less than 1\n";
        [[fallthrough]];
    case 1:
        cout << "Number is less than 2\n";
        [[fallthrough]];
    case 2:
        cout << "Number is less than 3\n";
        break;
    case 3:
        cout << "Number is exactly 3\n";
        break;
    default:
        cout << "Number out of range!\n";
        break;
    }
}
