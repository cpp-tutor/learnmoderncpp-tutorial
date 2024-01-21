// 02-height.cpp : define the same variable name in two different namespaces

import std;
using namespace std;

namespace Wonderland {
    auto alice_height_m{ 0.15 };
}

namespace VictorianEngland {
    auto alice_height_m{ 0.9 };
}

int main() {
    println("Alice\'s height varies between {}m and {}m",
        Wonderland::alice_height_m,
        VictorianEngland::alice_height_m);
}
