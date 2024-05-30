// 02-constexpr.cpp : introducing the constexpr keyword

import std;
using namespace std;

// Note: currently, not all compilers mark `acos` as a
// constexpr function in cmath. The following line might
// not compile with `clang++` for example.
constexpr double PI1 = acos(-1.0);
constexpr double PI2 = 22.0 / 7.0;

static_assert(PI1 > 3.141 && PI1 < 3.143);
static_assert(PI2 > 3.141 && PI2 < 3.143);

int main() {
    println("PI1 = {}", PI1);
    println("PI2 = {}", PI2);
}
