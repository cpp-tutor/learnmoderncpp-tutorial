// 02-constants.cpp : introducing the const keyword

import std;
using namespace std;

const double PI = 3.14159265358979;

int main() {
    auto const APPROX_E = 3;
    println("pi is almost exactly {}, while e is approximately {}",
        PI, APPROX_E);
}
