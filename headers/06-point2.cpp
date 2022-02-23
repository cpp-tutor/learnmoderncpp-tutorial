// 06-point2.cpp : a Point type with getter and setters which check for values being within range

#include <iostream>
using namespace std;

struct Point {
	void setX(int nx)
	{
		if (nx < 0) {
			x = 0;
		}
		else if (nx > screenX) {
			x = screenX;
		}
		else {
			x = nx;
		}
	}
	void setY(int ny)
	{
		if (ny < 0) {
			y = 0;
		}
		else if (ny > screenY) {
			y = screenY;
		}
		else {
			y = ny;
		}
	}
	auto getXY() const {
	    return pair{x, y};
    }
	static const int screenX{ 639 }, screenY{ 479 };
private:
	int x{}, y{};
};

int main() {
	cout << "Screen is " << Point::screenX + 1 << " by " << Point::screenY + 1 << '\n';
	Point p;
	int user_x{}, user_y{};
	cout << "Please enter x and y for Point:\n";
	cin >> user_x >> user_y;
	p.setX(user_x);
	p.setY(user_y);
	auto [ px, py ] = p.getXY();
	cout << "px = " << px << ", py = " << py << '\n';
}
