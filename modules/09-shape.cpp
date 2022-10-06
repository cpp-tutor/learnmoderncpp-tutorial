// 09-shape.cpp : Shape class hierarchy demonstrating polymorphism

import std.core;
using namespace std;

class Shape {
public:
    struct Point;
    Shape(int sides) : sides{ sides } {}
    Shape(int sides, Point center) : sides{ sides }, center{ center } {}
    virtual void draw(ostream& os) const = 0;
    virtual string getSides() const { return to_string(sides); }
    void moveBy(int dx, int dy) { center.x += dx; center.y += dy; }
    const Point& getCenter() const { return center; }
    virtual ~Shape() { cerr << "~Shape()\n"; }
    struct Point {
        int x{}, y{};
    };
private:
    int sides;
    Point center;
};

ostream& operator<< (ostream& os, const Shape::Point& pt) {
    return os << '(' << pt.x << ',' << pt.y << ')';
}

class Triangle final : public Shape {
public:
    Triangle(int side) : Shape{ 3 }, side{ side } {}
    Triangle(int x, int y, int side) : Shape{ 3, {x, y} }, side{ side } {}
    virtual void draw(ostream& os) const override {
        os << " /\\\n/__\\\nSide: " << side << "\nAt: " << getCenter() << '\n';
    }
private:
    int side;
};

class Circle : public Shape {
public:
    Circle(int radius) : Shape{ 0 }, radius{ radius } {}
    Circle(int x, int y, int radius) : Shape{ 0, {x, y} }, radius{ radius } {}
    virtual void draw(ostream& os) const override final {
        os << " _\n(_)\nRadius: " << radius << "\nAt: " << getCenter() << '\n';
    }
    virtual string getSides() const override final { return "infinite"; }
private:
    int radius;
};

class Rectangle : public Shape {
public:
    Rectangle(int side_x, int side_y) : Shape{ 4 }, side_x{ side_x }, side_y{ side_y } {}
    Rectangle(int x, int y, int side_x, int side_y)
        : Shape{ 4, {x ,y} }, side_x{ side_x }, side_y{ side_y } {}
    virtual void draw(ostream& os) const override {
        os << " ____\n|____|\nSize: " << side_x << 'x' << side_y << "\nAt: " << getCenter() << '\n';
    }
protected:
    int side_x, side_y;
};

class Square final : public Rectangle {
public:
    Square(int side) : Rectangle{ side, side } {}
    Square(int x, int y, int side) : Rectangle{ x, y, side, side } {}
    virtual void draw(ostream& os) const override final {
        os << " _\n|_|\nSide: " << side_x << "\nAt: " << getCenter() << '\n';
    }
};

int main() {
    vector<Shape*> shapes;
    shapes.push_back(new Circle{ 10 });
    shapes.push_back(new Triangle{ 10, 20, 15 });
    shapes.push_back(new Rectangle{ 10, 5 });
    shapes.push_back(new Square{ 25, 100, 50 });
    shapes[0]->moveBy(20, 50);

    for (auto& s : shapes) {
        s->draw(cout);
        cout << "Sides: " << s->getSides() << '\n';
        delete s;
        s = nullptr;
    }
}
