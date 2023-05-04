// 04-aggregate.cpp : calling a function with different types of arguments and parameters

import std;
using namespace std;

auto get_numbers() {
    cout << "Please enter a float and an integer: ";
    double d{};
    int i{};
    cin >> d >> i;
    return pair{ d, i };
}

int main() {
    auto [ a, b ] = get_numbers();
    cout << "You entered " << a << " and " << b << '\n';
}
