// 03-ifconstexpr.cpp : demonstrate compile-time if

import std;
using namespace std;

int main() {
    constexpr auto int_size = sizeof(int);
    if constexpr (int_size == 4) {
        cout << "32 bit ints\n";
    }
    else if constexpr (int_size == 8) {
        cout << "64 bit ints\n";
    }
    else {
        cout << "Man, you have weird ints!\n";
    }
}
