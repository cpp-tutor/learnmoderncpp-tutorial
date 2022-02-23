// 08-file2.cpp : echo disk file to console

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cerr << "Syntax: " << argv[0] << " <text file name>\n";
        return 1;
    }
    ifstream infile{ argv[1] };

    char c;
    while (!infile.eof()) {
        infile >> noskipws >> c;
        cout << c;
    }
}
