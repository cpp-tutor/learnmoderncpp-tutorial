// 10-lambda3.cpp : lambda function which calculates average of two values

#include <iostream>
using namespace std;

int main() {
    auto l = [](int a, int b) {
        cout << "Calculating average...\n";
        return (a + b) / 2;
    };

    cout << "Please enter two integers:\n";
    int x{}, y{};
    cin >> x >> y;
    auto avg = l(x, y);
    cout << "The average is: " << avg << '\n';
}
