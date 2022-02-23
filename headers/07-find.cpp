// 07-find.cpp : find and erase a single element

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
using namespace std;

int main() {
    string a{ "hello" };
    vector v{ 1, 9, 7, 3 };
    set s{ 3, 8, 6, 4, 3 };
    
    cout << "Before:\nstring: " << a << "\nvector: ";
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));    
    cout << "\nset: ";
    copy(begin(s), end(s), ostream_iterator<int>(cout, " "));
    cout << '\n';

    auto f1 = a.find('l');
    if (f1 != string::npos) {
        cout << "Found in string at position: " << f1 << '\n';
        a.erase(f1, 1);
    }
    auto f2 = find(begin(v), end(v), 7);
    if (f2 != end(v)) {
        cout << "Found in vector: " << *f2 << '\n';
        v.erase(f2);
    }
    auto f3 = s.find(6);
    if (f3 != end(s)) {
        cout << "Found in set: " << *f3 << '\n';
        s.erase(f3);
    }

    cout << "After:\nstring: " << a << "\nvector: ";
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));    
    cout << "\nset: ";
    copy(begin(s), end(s), ostream_iterator<int>(cout, " "));
    cout << '\n';
}
