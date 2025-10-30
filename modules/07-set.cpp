// 07-set.cpp : demonstrate automatic ordering of a set

import std;
using namespace std;

int main() {
    set<string> s{
        "Stroustrup, Bjarne",
        "Yukihiro, Matsumoto",
        "Wall, Larry",
        "Eich, Brendan"
    };

    s.insert("Lerdorf, Rasmus");
    copy(begin(s), end(s), ostream_iterator<string>(cout, "\n"));
}
