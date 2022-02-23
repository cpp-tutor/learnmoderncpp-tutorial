// 05-range-for.cpp : print a string literal vertically

import std.core;
using namespace std;

int main() {
    for (auto c : "Dinah") {
        cout << "- " << c << '\n';
    }
}
