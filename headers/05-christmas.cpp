// 05-christmas.cpp : calculate total number of gifts from the popular song

#include <iostream>
using namespace std;

int main() {
    int gifts{ 0 };
    for (int i{ 1 }, j{ 12 }; i <= 12; ++i, --j) {
        gifts += i * j;
    }
    cout << gifts << " gifts in total.\n";
}
