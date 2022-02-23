// 05-while.cpp : print a user-entered string vertically

import std.core;
using namespace std;

int main() {
    char str[20];
    cout << "Please enter a string (up to "
         << size(str) - 1 << " characters):\n";
    cin.getline(str, size(str));
    const char *p = str;
    while (*p) {
        cout << "- " << *p << '\n';
        ++p;
    }
}
