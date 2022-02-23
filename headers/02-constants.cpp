// 02-constants.cpp : introducing the const keyword

#include <iostream>
using namespace std;

const double PI = 3.14159265358979;

int main() {
    auto const APPROX_E = 3;
    cout << "pi is almost exactly " << PI
    << "e is approximately " << APPROX_E
    << '\n';
}
