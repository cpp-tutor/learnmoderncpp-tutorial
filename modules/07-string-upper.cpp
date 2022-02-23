// 07-string-upper.cpp : function to make a std::string uppercase in-place

import std.core;
using namespace std;

void string_to_uppercase(string &s) {
	for (auto& c : s) {
		c = toupper(c);
	}
}

int main() {
	cout << "Please enter some text in lower-, mixed- or upper-case:\n";
	string input;
	getline(cin, input);
	string_to_uppercase(input);
	cout << "The same text in uppercase is:\n" << input << '\n';
}
