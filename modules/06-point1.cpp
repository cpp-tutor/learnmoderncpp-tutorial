// 06-point1.cpp : a Point type with getter and setters

import std.core;
using namespace std;

struct Point {
	void setX(int nx) {
	    x = nx;
	}
	void setY(int ny) {
	    y = ny;
	}
	auto getXY() const {
	    return pair{x, y};
	}
private:
	int x{}, y{};
};

int main() {
	Point p;
	int user_x{}, user_y{};
	cout << "Please enter x and y for Point:\n";
	cin >> user_x >> user_y;
	p.setX(user_x);
	p.setY(user_y);
	auto [ px, py ] = p.getXY();
	cout << "px = " << px << ", py = " << py << '\n';
}
