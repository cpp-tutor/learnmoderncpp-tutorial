// 04-absolute3.cpp : modify a parameter to become its absolute value

#include <iostream>
using namespace std;

void abs_value(int& v) {
    if (v < 0) {
        v = -v;
    }
}

int main() {
    int value{};
    cout << "Please enter a positive or negative integer: ";
    cin >> value;
    abs_value(value);
    cout << "The absolute value is: " << value << '\n';
}
