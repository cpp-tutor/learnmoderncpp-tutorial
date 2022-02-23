// 08-calc.cpp : read from a file and perform calculations

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double calc(char op, double x, double y) {
    double r{};
    switch (op) {
    case '+':
        r = x + y;
        break;
    case '-':
        r = x - y;
        break;
    case '*':
        r = x * y;
        break;
    case '/':
        if (y) {
            r = x / y;
        }
        else {
            cerr << "Error: divide by zero.\n";
        }
        break;
    case '^':
        r = pow(x, y);
        break;
    default:
        cerr << "Error: invalid op.\n";
    }
    return r;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cerr << "Syntax: " << argv[0] << " <input file name>\n";
        return 1;
    }
    ifstream infile{argv[1]};

    while (!infile.eof()) {
        double x, y;
        char op;
        infile >> x >> op >> y;
        if (infile.fail() || infile.bad()) {
            cerr << "Error in input.\n";
            break;
        }
        auto r = calc(op, x, y);
        cout << x << ' ' << op << ' ' << y << " = " << r << '\n';
    }
}
