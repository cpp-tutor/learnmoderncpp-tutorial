// 02-constexpr.cpp : introducing the constexpr keyword

#include <iostream>
#include <cmath>
using namespace std;

const double PI1 = acos(-1.0);     // acos is not (yet) constexpr
constexpr double PI2 = 22.0 / 7.0;

// the following line does not compile and has been commented out
//static_assert(PI1 > 3.141 && PI1 < 3.143);
static_assert(PI2 > 3.141 && PI2 < 3.143);

int main() {
    cout << "PI1 = " << PI1 << '\n';
    cout << "PI2 = " << PI2 << '\n';
}
