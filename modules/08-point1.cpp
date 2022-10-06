// 08-point1.cpp : a Point class with ostream formatter

import std.core;
using namespace std;

struct Point {
    int x{}, y{};
};

ostream& operator<< (ostream& os, const Point& p) {
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}

int main() {
    Point p{ 1, 2 };
    cout << p << '\n';
    cout << Point{ 3, 4 } << '\n';
}
