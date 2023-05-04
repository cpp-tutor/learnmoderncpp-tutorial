// 07-vector.cpp : read integers from user, sort them and then output

import std;
using namespace std;

int main() {
    vector<int> v;
    for (;;) {
        cout << "Please enter a number (99 to quit): ";
        int i{};
        cin >> i;
        if (i == 99) {
            break;
        }
        v.push_back(i);
    }

    sort(begin(v), end(v));
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << '\n';
}
