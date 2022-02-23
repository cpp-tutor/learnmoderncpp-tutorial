// 05-do-while.cpp : use of post-condition loop to validate user input

#include <iostream>
using namespace std;

int main() {
    int i{};
    do {
        cout << "Please enter a negative number: ";
        cin >> i;
    } while (i >= 0);
    cout << "You entered: " << i << '\n';
}
