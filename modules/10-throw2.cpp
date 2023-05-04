// 10-throw2.cpp : throw and catch exceptions from within and outside std::exception hierarchy

import std;
using namespace std;

int throwing() {
    cout << 1+R"(
Please choose:
1) throw std::runtime_error
2) throw std::exception
3) throw int
4) quit
Enter 1-4: )";
    int option;
    cin >> option;
    switch(option) {
    case 1:
        throw runtime_error{"std::runtime_error thrown"};
    case 2:
        throw exception{};
    case 3:
        throw 99;
    case 4:
        return 1;
    default:
        cout << "Error: unrecognized option\n";
    }
    return 0;
}

int main() {
    for (;;) {
        int action{};
        try {
            action = throwing();
        }
        catch (runtime_error& e) {
            cerr << "Caught std::runtime_error! (" << e.what() << ")\n";
        }
        catch (exception& e) {
            cerr << "Caught std::exception!\n";
        }
        catch (...) {
            cerr << "Caught something other than std::exception! Quitting.\n";
            return 1;
        }
        if (action) {
            break;
        }
    }
}
