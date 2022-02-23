// 08-receipt.cpp : output a till-receipt from user input

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Entry {
	string product;
	size_t quantity;
	double unit_price;
	inline static double total{};
};

Entry add_entry(const string& input) {
	Entry e;
	istringstream iss{ input };
	iss >> e.product >> e.quantity >> e.unit_price;
	if (iss.fail()) {
		cerr << "Bad entry.\n";
		e.quantity = 0;
	}
	else {
		Entry::total += e.quantity * e.unit_price;
	}
	return e;
}

int main() {
	vector<Entry> sales;
	cout << "Please enter: PRODUCT QTY PRICE (eg. \'Apple 6 0.50\')\n";
	string s;
	getline(cin, s);
	while(!s.empty()) {
		sales.emplace_back(add_entry(s));
		cout << "Please enter: PRODUCT QTY PRICE (blank line to finish)\n";
		getline(cin, s);
	}

	cout << "====================\n";
    auto f = cout.flags();
	auto p = cout.precision(2);
	cout.setf(ios_base::fixed, ios_base::floatfield);
	for (const auto& line : sales) {
		if (line.quantity) {
			cout.setf(ios_base::left, ios_base::adjustfield);
			cout.width(11);
			cout << line.product;
			cout.unsetf(ios_base::adjustfield);
			cout.width(3);
			cout << line.quantity;
			cout.width(6);
			cout << line.unit_price << '\n';
		}
	}
	cout << "====================\n";
	cout << "Total:";
	cout.width(14);
	cout << Entry::total << '\n';
	cout.flags(f);
	cout.precision(p);
}
