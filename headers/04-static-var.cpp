// 04-static-var.cpp : preserving function state in a static variable

#include <iostream>
using namespace std;

void f() {
    static int s{1};
    cout << s << '\n';
    ++s;
}

int main() {
    f();
    f();
    f();
}
