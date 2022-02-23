// 10-lambda2.cpp : another simple lambda which produces output

#include <iostream>
#include <string_view>
using namespace std;

int main() {
	auto l = [](string_view s){ cout << "Lambda says " << s << '\n'; };
	
	l("Hola");
}
