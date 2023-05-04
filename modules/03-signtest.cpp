// 03-signtest.cpp : test an integer value for zero, positive or negative

import std;
using namespace std;

int main() {
    cout << "Please enter an integer value: ";
    int n{};
    cin >> n;
    cout << "The value entered was ";
    if (!n) {
        cout << "zero\n";
    }
    else if (n < 0) {
        cout << "negative\n";
    }
    else {
        cout << "positive\n";
    }
}
