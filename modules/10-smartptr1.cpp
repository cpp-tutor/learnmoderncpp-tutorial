// 10-smartptr1.cpp : use of unique_ptr

import std;
using namespace std;

class Simple {
    string str;
public:
    Simple(string_view s) : str{s}
    { cout << "Simple(): " << str << '\n'; }
    ~Simple()
    { cout << "~Simple(): " << str << '\n'; }
};

int main(int argc, const char *argv[]) {
    unique_ptr<Simple> p1{ new Simple("p1") };
    Simple *p2 = new Simple("p2");
    {
        auto p3 = make_unique<Simple>("p3");
        if (argc > 1) {
            return 1;
        }
        delete p2;
        p2 = nullptr;
    }
}
