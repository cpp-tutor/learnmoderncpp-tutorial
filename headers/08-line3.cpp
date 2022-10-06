// 08-line3.cpp : read a text file into a string variable and display it

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cerr << "Syntax: " << argv[0] << " <text file name>\n";
        return 1;
    }
    ifstream infile{argv[1]};

    string s;
    getline(infile, s, '\0');
    cout << s;
}
