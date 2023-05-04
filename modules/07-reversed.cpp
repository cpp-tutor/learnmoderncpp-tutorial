// 07-reversed.cpp : output different "string" types using a string_view

import std;
using namespace std;

void print_reversed(string_view sv) {
    for (auto iter = crbegin(sv); iter != crend(sv); ++iter) {
        cout << *iter;
    }
    cout << '\n';
}

int main() {
    const char *s1 = "Elf";
    char s2[] = "Dwarf";
    string s3 = "Hobbit"s;
    string_view s4 = "Orc"sv;

    print_reversed(s1);
    print_reversed(s2);
    print_reversed(s3);
    print_reversed(s4);
    print_reversed("Man");
}
