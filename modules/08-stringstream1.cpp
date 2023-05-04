// 08-stringstream1.cpp : write to string stream

import std;
using namespace std;

int main() {
    ostringstream oss{};
    oss.precision(3);
    oss << fixed << 1 << '+' << 3.2 << " = " << 1 + 3.2;
    puts(oss.str().c_str());
}
