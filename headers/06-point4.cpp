// 06-point4.cpp : Point type with global operator+ and member operator+= defined

#include <iostream>
using namespace std;

struct Point{
    int x{}, y{};

    Point& operator+= (const Point& rhs) { // member operator +=
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
};

Point operator+ (const Point& lhs, const Point& rhs) { // non-member operator+
    Point result{ lhs };
    result += rhs;
    return result;
}

int main() {
    Point p1{ 100, 200 }, p2{ 200, -50 }, p3;
    p3 = p1 + p2;
    cout << "p3 = (" << p3.x << ',' << p3.y << ")\n";
}
