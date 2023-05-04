// 05-for.cpp : output an array using for

import std;
using namespace std;

int main() {
    int a[]{ 9, 8, 7, 6, 5, 4 };
    for (int i{ 0 }; i != 6; ++i) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}
