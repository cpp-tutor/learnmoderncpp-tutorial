// 03-zerotest1.cpp : test an integer value against zero

#include <iostream>
using namespace std;

int main() {
    cout << "Please enter an integer value: ";
    int n{};
    cin >> n;
    cout << "The value entered was ";
    if (n) {
        cout << "nonzero\n";
    }
    else {
        cout << "zero\n";
    }
}
