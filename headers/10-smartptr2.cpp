// 10-smartptr2.cpp : encapsulate a FILE* in a unique_ptr

#include <iostream>
#include <cstdio>
#include <memory>
using namespace std;

int main(int argc, const char *argv[]) {
	if (argc != 2) {
		cerr << "Syntax: " << argv[0] << " <filename>\n";
		return 1;
	}

	unique_ptr<FILE,decltype(&fclose)> fp{ fopen(argv[1], "rb"), fclose };

	if (fp) {
		int c;
		while ((c = fgetc(fp.get())) != EOF) {
			putchar(c);
		}
	}
}
