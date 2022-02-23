// 08-stringstream1.cpp : write to string stream

#include <sstream>
#include <iomanip>
#include <cstdio>
using namespace std;

int main() {
    ostringstream oss{};
    oss.precision(3);
    oss << fixed << 1 << '+' << 3.2 << " = " << 1 + 3.2;
    puts(oss.str().c_str());
}
