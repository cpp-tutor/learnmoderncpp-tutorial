// 04-noexcept.cpp : a noexcept function throwing an exception

import std;
using namespace std;

int throw_if_zero(int i) noexcept {
    if (!i) {
        throw runtime_error("found a zero");
    }
    println("throw_if_zero(): {}", i);
}

int main() {
    cout << "Entering main()\n";
    try {
        throw_if_zero(1);
        throw_if_zero(0);
    }
    catch(...) {
        println("Caught an exception!");
    }
    println("Leaving main()\n");
}
