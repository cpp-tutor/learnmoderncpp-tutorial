// 06-point3.cpp : Point type with global operator+ defined

import std.core;
using namespace std;

struct Point{
	int x{}, y{};
};

Point operator+ (const Point& lhs, const Point& rhs) {
	Point result;
	result.x = lhs.x + rhs.x;
	result.y = lhs.y + rhs.y;
	return result;
}

int main() {
	Point p1{ 100, 200 }, p2{ 200, -50 }, p3;
	p3 = p1 + p2;
	cout << "p3 = (" << p3.x << ',' << p3.y << ")\n";
}
