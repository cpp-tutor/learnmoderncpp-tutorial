// 08-line2.cpp : obtain a line of input from the user, store it in a string variable and display it

import std;
using namespace std;

int main() {
    cout << "Please enter your full name:\n";
    string s;
    getline(cin, s);
    cout << "You entered: \'" << s << "\'\n";
}
