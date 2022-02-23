// 05-not-do-while.cpp : alternative to post-condition loop

#include <iostream>
using namespace std;

int main() {
    int i{};
    cout << "Please enter a negative number: ";
    cin >> i;
    while (i >= 0) {
        cout << "Please enter a negative number: ";
        cin >> i;
    }
    cout << "You entered: " << i << '\n';
}
