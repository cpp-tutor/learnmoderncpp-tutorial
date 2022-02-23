// 07-map.cpp : calculate prices from associative array of products and per-weight cost

#include <iostream>
#include <string>
#include <cctype>
#include <map>
using namespace std;

int main() {
    map<string,double> products{
        { "Apples", 0.65 },
        { "Oranges", 0.85 },
        { "Bananas", 0.45 },
        { "Pears", 0.50 }
    };
    cout.precision(2);
    cout << fixed;
    for (;;) {
        cout << "Please choose: Add product, Calculate price, Quit\nEnter one of A, C, Q: ";
        char opt;
        cin >> opt;
        opt = toupper(opt);
        if (opt == 'Q') {
            break;
        }
        else if (opt == 'A') {
            cout << "Enter product and price-per-kilo: ";
            string product;
            double price;
            cin >> product >> price;
            product.front() = toupper(product.front());
            products.insert(pair{ product, price });
        }
        else if (opt == 'C') {
            for (const auto& p : products) {
                cout << p.first << '\t' << p.second << "/kg\n";
            } 
            cout << "Enter product and quantity: ";
            string product;
            double quantity;
            cin >> product >> quantity;
            product.front() = toupper(product.front());
            auto iter = products.find(product);
            if (iter != end(products)) {
                cout << "Price: " << iter->second * quantity << '\n';
            }
            else {
                cout << "Could not find \"" << product << "\"\n";
            }
        }
        else {
            cout << "Option not recognized.\n";
        }
    }
}
