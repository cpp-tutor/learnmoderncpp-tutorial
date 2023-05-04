// 08-line1.cpp : obtain a line of input from the user and display it

import std;
using namespace std;

int main() {
    cout << "Please enter your full name:\n";
    char line[32];
    cin.getline(line, size(line));
    cout << "You entered: \'" << line << "\'\n";
}
