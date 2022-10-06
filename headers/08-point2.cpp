// 08-point2.cpp : read Points from input stream

#include <iostream>
using namespace std;

struct Point {
    int x{}, y{};
};

istream& operator>> (istream& is, Point& p) {
    char a{}, b{}, c{};
    int px, py;
    is >> a >> px >> b >> py >> c;
    if (is.good()) {
        if (a == '(' && b == ',' && c == ')') {
            p.x = px;
            p.y = py;
        }
        else {
            is.setstate(ios_base::failbit);
        }
    }
    return is;
}

int main() {
    cout << "Please enter Points, in the form \'(2,-3)\'\n";
    Point p;
    while (!cin.eof()) {
        cin >> p;
        if (cin.good()) {
            cout << "Point read successfully!\n";
        }
        else {
            cout << "Error in input!\n";
            cin.clear();
        }
    }
}
