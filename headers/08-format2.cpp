// 08-format2.cpp : Various format string-using functions

#include <print>
#include <format>
#include <string>
#include <iostream>
#include <iterator>
#include <array>
#include <cmath>
using namespace std;

int main() {
    string world{ "World" };
    print(cout, "Hello, {}!\n", world);
    println("{1} or {0}", false, true);
    
    constexpr const char *fmt = "Approximation of π = {:.12g}";
    string s = format(fmt, asin(1.0) * 2);
    cout << s << '\n';
    
    constexpr const wchar_t *wfmt = L"Approximation of pi = {:.12g}";
    wstring ws = format(wfmt, asin(1.0) * 2);
    wcout << ws << L'\n';
    
    format_to(ostream_iterator<char>(cout), "Hello, {}!\n", world);
    wstring ww{ L"World" };
    array<wchar_t,9> wa;
    auto iter = format_to_n(wa.begin(), 8, L"Hello, {}!\n", ww);
    *(iter.out) = L'\0';
    wcout << wa.data() << L'\n';
}
