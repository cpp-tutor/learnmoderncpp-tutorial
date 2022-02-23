// 10-lambda1.cpp : simple lambda which produces output

#include <iostream>
using namespace std;

int main() {
	auto l = []{ cout << "Lambda says Hi!\n"; };
	
	l();
}
