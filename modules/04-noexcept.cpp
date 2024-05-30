// 04-noexcept.cpp : a noexcept function throwing an exception

import std;
using namespace std;

void throw_if_zero(int i) noexcept {
    if (!i) {
        throw runtime_error("found a zero");
    }
    println("throw_if_zero(): {}", i);
}

int main() {
    println("Entering main()");
    try {
        throw_if_zero(1);
        throw_if_zero(0);
    }
    catch(exception& e) {
        println("Caught an exception: {}", e.what());
    }
    println("Leaving main()");
}
