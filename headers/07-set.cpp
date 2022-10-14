// 07-set.cpp : demonstrate automatic ordering of a set

#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

int main() {
    set<string> s{
        "Rossum, Guido van",
        "Yukihiro, Matsumoto",
        "Wall, Larry",
        "Eich, Brendan"
    };

    s.insert("Lerdorf, Rasmus");
    copy(begin(s), end(s), ostream_iterator<string>(cout, "\n"));
}
