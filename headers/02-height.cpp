// 02-height.cpp : define the same variable name in two different namespaces

#include <iostream>
using namespace std;

namespace Wonderland {
    auto alice_height_m{ 0.15 };
}

namespace VictorianEngland {
    auto alice_height_m{ 0.9 };
}

int main() {
    cout << "Alice\'s height varies between "
    << Wonderland::alice_height_m
    << "m and "
    << VictorianEngland::alice_height_m
    << "m.\n";
}
