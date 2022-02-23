// 10-functor1.cpp : simple function object demonstration

import std.core;
using namespace std;

struct Average {
	int operator()(int a, int b) {
		cout << "Calculating average...\n";
		return (a + b) / 2;
	}
};

int main() {
	Average a;
	cout << "Please enter two integers:\n";
	int x{}, y{};
	cin >> x >> y;
	auto avg = a(x, y);
	cout << "The average is: " << avg << '\n';
}
