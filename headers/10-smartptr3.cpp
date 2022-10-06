// 10-smartptr3.cpp : use of shared_ptr

#include <memory>
#include <iostream>
using namespace std;

class Simple {
    string str;
public:
    Simple(string_view s) : str{s}
    { cout << "Simple(): " << str << '\n'; }
    ~Simple()
    { cout << "~Simple(): " << str << '\n'; }
};

int main() {
    cout << "main(): 1\n";
    shared_ptr<Simple> p1{ new Simple("p1") };
    cout << "main(): 2\n";
    {
        cout << "main(): 3\n";
        auto p2 = make_shared<Simple>("p2");
        cout << "main(): 4\n";
        p1 = p2;
        cout << "main(): 5\n";
    }
    cout << "main(): 6\n";
}
