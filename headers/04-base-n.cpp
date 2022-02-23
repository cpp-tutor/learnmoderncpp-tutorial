// 04-base-n.cpp : print out a number to given base

#include <iostream>
using namespace std;

void print_base_n(unsigned long long num, unsigned base = 10);

int main() {
    cout << "Please enter a number (in decimal): ";
    long long n{};
    cin >> n;
    cout << "Please enter the required base (2-16): ";
    int b{};
    cin >> b;
    if ((b >= 2) and (b <= 16)) {
        print_base_n(n, b);
        cout << '\n';
    }
    else {
        cerr << "Base not in range.\n";
    }
}

void print_base_n(unsigned long long num, unsigned base) {
    if (num >= base) {
        print_base_n(num / base, base);
    }
    cout << "0123456789abcdef"[num % base];
}
