// 08-line1.cpp : obtain a line of input from the user and display it

#include <iostream>
using namespace std;

int main() {
    cout << "Please enter your full name:\n";
    char line[32];
    cin.getline(line, size(line));
    cout << "You entered: \'" << line << "\'\n";
}
