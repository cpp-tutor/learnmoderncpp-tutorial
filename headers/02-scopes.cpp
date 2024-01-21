// 02-scopes.cpp : define three variables with the same name in one program

#include <print>
using namespace std;

auto a{ 1.5f };

int main() {
    println("(1) {}", a);
    auto a{ 2u };
    println("(2) {}", a);
    {
        auto a{ 2.5 };
        println("(3) {}", a);
    }
}
