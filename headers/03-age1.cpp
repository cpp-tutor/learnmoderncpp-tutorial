// 03-age1.cpp : get and then display an integer

#include <iostream>
using namespace std;

int main() {
    int alice_age{};
    cout << "Please enter your guess for Alice\'s age: ";
    cin >> alice_age;
    cout << "You guessed " << alice_age << "!\n";
}
