// 02-scopes.cpp : define three variables with the same name in one program

import std.core;
using namespace std;

auto a{ 1.5f };

int main() {
    cout << "(1) " << a << '\n';
    auto a{ 2u };
    cout << "(2) " << a << '\n';
    {
        auto a{ 2.5 };
        cout << "(3) " << a << '\n';
    }
}
