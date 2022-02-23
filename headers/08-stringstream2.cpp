// 08-stringstream2.cpp : validate input to calculator function

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
    string s;
    double a, b;
    char op;
    for (;;) {
        cout << "Please enter a calculation to perform (Number Operator Number):\n";
        getline(cin, s);
        if (s.empty()) {
            break;
        }
        istringstream iss{s};
        iss >> a >> op >> b;
        if (iss.fail() || !iss.eof()) {
            cout << "Bad input!\n";
        }
        else {
            cout << "Input read successfully.\n";
        }
    }
}
