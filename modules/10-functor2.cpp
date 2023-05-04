// 10-functor2.cpp : function object maintaining state

import std;
using namespace std;

struct MinMaxAvg {
    void operator()(int i) {
        if (first) {
            min = max = avg = i;
            first = false;
            return;
        }
        if (i < min) {
            min = i;
        }
        if (i > max) {
            max = i;
        }
        avg = ((avg * num) + i) / (num + 1);
        ++num;
    }
    int min, max, num{ 1 };
    double avg;
    bool first{ true };
};

int main() {
    vector v{ 3, 5, 2, 6, 2, 4 };
    MinMaxAvg f;
    for_each(begin(v), end(v), ref(f));
    cout << "Min: " << f.min << " Max: " << f.max
      << " Avg: " << f.avg << " Num: " << f.num << '\n';
}
