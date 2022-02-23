// 08-string.cpp : read a string using the stream extraction operator

import std.core;
using namespace std;

int main() {
    cout << "Please enter your first name:\n";
    string name;
    cin >> name;
    cout << "Hi, \'" << name << "\', nice to meet you!\n";
}
