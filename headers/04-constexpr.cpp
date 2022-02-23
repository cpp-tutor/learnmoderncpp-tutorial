// 04-constexpr.cpp : use of a constexpr function with static_assert

#include <iostream>
using namespace std;

constexpr int factorial(int n) {
    if (n < 2) {
        return 1;
    }
    else {
        return n * factorial(n - 1);
    }
}

static_assert(factorial(0) == 1);
static_assert(factorial(5) == 120);

int main() {
    cout << "Please enter a number: ";
    int n{};
    cin >> n;
    cout << n << "! = " << factorial(n) << '\n';
}
