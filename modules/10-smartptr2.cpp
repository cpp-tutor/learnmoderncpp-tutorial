// 10-smartptr2.cpp : encapsulate a FILE* in a unique_ptr

import std;
import std.compat;
using namespace std;

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cerr << "Syntax: " << argv[0] << " <filename>\n";
        return 1;
    }

    unique_ptr<FILE,decltype(&fclose)> fp{ fopen(argv[1], "rb"), fclose };

    if (fp) {
        int c;
        while ((c = fgetc(fp.get())) != ifstream::traits_type::eof()) {
            putchar(c);
        }
    }
}
