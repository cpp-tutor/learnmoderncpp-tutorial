// 04-static-var.cpp : preserving function state in a static variable

#include <print>
using namespace std;

void f() {
    static int s{1};
    println("{}", s);
    ++s;
}

int main() {
    f();
    f();
    f();
}
