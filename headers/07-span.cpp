// 07-span.cpp : convert different container types to span and print them out

#include <iostream>
#include <span>
#include <array>
#include <vector>
#include <string_view>
using namespace std;

void print_ints(span<int> s) {
    for (auto sep{ ""sv }; auto& e : s) {
        cout << sep << e;
        sep = ", "sv;
    }
    cout << '\n';
}

int main() {
    int c_array[] = { 1, 2, 3 };
    vector vec = { 2, 6, 4, 3 };
    array<int,4> std_array = { 3, 2, 1 };

    print_ints(c_array);
    print_ints(vec);
    print_ints(std_array);
    // print_ints({ 9, 8, 7, 6 }); // Error: does not compile
}
