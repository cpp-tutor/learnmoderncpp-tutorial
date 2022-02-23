// 05-break-continue.cpp : use of control flow commands in loop

#include <iostream>
using namespace std;

int main() {
    for (;;) {
        int i{};
        cout << "Please enter a positive number (zero to quit): ";
        cin >> i;
        if (i == 0) {
            break;
        }
        if (i < 0) {
            continue;
        }
        cout << "You entered: " << i << '\n';
    }
    cout << "Program ended\n";
}
