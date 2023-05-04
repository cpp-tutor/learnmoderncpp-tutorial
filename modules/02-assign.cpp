// 02-assign.cpp : assign to local variables

import std;
using namespace std;

int main() {
    int i = 1, j = 2;
    unsigned k;
    cout << "(1) i = " << i << ", j = " << j << ", k = " << k << '\n';
    i = j;
    j = 3;
    k = -1;
    cout << "(2) i = " << i << ", j = " << j << ", k = " << k << '\n';
}
