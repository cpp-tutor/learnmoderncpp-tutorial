// 07-lists.cpp : forward and bi-directional lists

import std.core;
using namespace std;

int main() {
    forward_list<string> fwd;
    auto iter = fwd.before_begin();  // note: member function
    cout << "Please enter some words (blank line to end):\n";
    for (;;) {
        string s;
        getline(cin, s);
        if (s.empty()) {
            break;
        }
        fwd.insert_after(iter, s);  // note: member function
        ++iter;                     // note: must "keep up"
    }

    list<string> lst(begin(fwd), end(fwd));
    lst.sort();
    for (const auto& e : lst) {
        cout << "- " << e << '\n';
    }
}
