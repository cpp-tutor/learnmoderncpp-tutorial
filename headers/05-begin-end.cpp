// 05-begin-end.cpp : demostration of the use of begin() and end()

#include <iostream>
using namespace std;

int main() {
    int numbers[] = { 3, 4, 1, 5, 6, 2 };
    for (auto p = begin(numbers); p != end(numbers); ++p) {
        cout << "- " << *p << '\n';
    }
}
