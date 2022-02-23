// 06-pixel1.cpp : Color and position Pixel type through composition

#include <iostream>
#include <string_view>
using namespace std;

struct Point {
    int x{}, y{};
};

enum class Color { red, green, blue };

struct Pixel {
    Point pt;
    Color col{};
};

string_view get_color(Color c) {
    switch (c) {
        case Color::red:
            return "red";
            break;
        case Color::green:
            return "green";
            break;
        case Color::blue:
            return "blue";
            break;
    }
    return "<no color>";
}

int main() {
    Pixel p1;
    cout << "Pixel p1 has color " << get_color(p1.col);
    cout << " and co-ordinates " << p1.pt.x;
    cout << ',' << p1.pt.y << '\n';

    Pixel p2{ { -1, 2 }, Color::blue };
    cout << "Pixel p2 has color " << get_color(p2.col);
    cout << " and co-ordinates " << p2.pt.x;
    cout << ',' << p2.pt.y << '\n';
}
