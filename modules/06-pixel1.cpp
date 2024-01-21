// 06-pixel1.cpp : Color and position Pixel type through composition

import std;
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
        case Color::green:
            return "green";
        case Color::blue:
            return "blue";
        default:
            return "<no color>";
    }
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
