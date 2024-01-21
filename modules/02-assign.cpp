// 02-assign.cpp : assign to local variables

import std;
using namespace std;

int main() {
    int i = 1, j = 2;
    unsigned k;
    println("(1) i = {}, j = {}, k = {}", i, j, k);
    i = j;
    j = 3;
    k = -1;
    println("(2) i = {}, j = {}, k = {}", i, j, k);
}
