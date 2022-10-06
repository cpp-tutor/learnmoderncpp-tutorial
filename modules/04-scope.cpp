// 04-scope.cpp : demonstrate function scope rules

import std.core;
using namespace std;

int alice_height_m;

void victorian_england() {
    size_t alice_height_m{ 1 };
    cout << "In \"victorian_england()\", alice_height_m is " << alice_height_m << ".\n";
}

void wonderland() {
    double alice_height_m{ 0.15 };
    cout << "In \"wonderland()\", alice_height_m is " << alice_height_m << ".\n";
}

int main() {
    cout << "In \"main()\", alice_height_m is " << alice_height_m << ".\n";
    victorian_england();
    wonderland();
    cout << "Back in \"main()\", alice_height_m is still " << alice_height_m << ".\n";
}
