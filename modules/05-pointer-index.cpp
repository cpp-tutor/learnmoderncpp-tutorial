// 05-pointer-index.cpp : demonstrate array indexing and pointer arithmetic

import std.core;
using namespace std;

void print_arr(const char s[], size_t n) {
    for (int i = 0; i != n; ++i) {
        cout << s[i];
    }
}

void print_ptr(const char *s, size_t n) {
    for (int i = 0; i != n; ++i) {
        cout << *(s + i);
    }
}

int main() {
    print_arr("Hello, ", 7);
    print_ptr("World!", 6);
    cout << '\n';
}
