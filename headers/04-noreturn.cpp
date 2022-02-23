// 04-noreturn.cpp : program which does not return from main()

#include <iostream>
using namespace std;

[[noreturn]] void report_fatal_error(int e) {
    cerr << "Fatal error code: " << e << '\n';
    terminate();
}

int main() {
    cout << "Entering main()\n";
    cout << "Calling report_fatal_error()\n";
    report_fatal_error(-1);
    cout << "Leaving main()\n";
}
