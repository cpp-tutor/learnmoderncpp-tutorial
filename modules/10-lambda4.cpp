// 10-lambda4.cpp : lambda accessing scoped variables by value and reference

import std.core;
using namespace std;

int main() {
	vector v{ 3, 5, 2, 6, 2, 4 };
	int min, max, num{ 1 };
	double avg;
	bool first{ true };
	
	auto l = [&](int i) {
		if (first) {
			min = max = avg = i;
			first = false;
			return;
		}
		if (i < min) {
			min = i;
		}
		if (i > max) {
			max = i;
		}
		avg = ((avg * num) + i) / (num + 1);
		++num;
	};

	for_each(begin(v), end(v), l);
	cout << "Min: " << min << " Max: " << max
	  << " Avg: " << avg << " Num: " << num << '\n';
}
