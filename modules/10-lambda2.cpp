// 10-lambda2.cpp : another simple lambda which produces output

import std.core;
using namespace std;

int main() {
	auto l = [](string_view s){ cout << "Lambda says " << s << '\n'; };
	
	l("Hola");
}
