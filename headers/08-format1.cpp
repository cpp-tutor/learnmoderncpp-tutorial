// 08-format1.cpp : Basic usage of format string

#include <print>
#include <string>
using namespace std;

int main() {
    string s{ "Formatted" };
    auto d{ 10.0 / 3.0 };
    auto i{ 20000 };
    println("{0:20}:{2:8}, {1:12.11}", s, d, i);
}
