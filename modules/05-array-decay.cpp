// 05-array-decay.cpp : demonstrate equivalence of pointer vs array parameters

import std.core;
using namespace std;

void print_arr(const char s[]) {
    while (*s) {
        cout << *s++;
    }
    cout << '\n';
}

void print_ptr(const char *s) {
    while (*s) {
        cout << *s++;
    }
    cout << '\n';
}

int main() {
    print_arr("Hello");
    print_ptr("World");
}
