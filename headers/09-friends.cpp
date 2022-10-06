// 09-friends.cpp : two classes as friends of each other

#include <iostream>
using namespace std;

class B;

class A {
public:
    friend class B;
    void a(B& other);
private:
    int m_a{42};
};

class B {
public:
    friend class A;
    void b(A& other) { cout << "b():" << other.m_a << '\n'; }
private:
    double m_b{1.414};
};

void A::a(B& other)
{
    cout << "a():" << other.m_b << '\n';
}

int main() {
    A obj_a{};
    B obj_b{};

    obj_a.a(obj_b);
    obj_b.b(obj_a);
}
