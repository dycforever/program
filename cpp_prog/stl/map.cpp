#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
    typedef map<string,float> StringFloatMap;
    StringFloatMap stocks;

    // insert some elements
    stocks["BASF"] = 369.50;
    stocks["VW"] = 413.50;
    stocks["Daimler"] = 819.00;
    stocks["BMW"] = 834.00;
    stocks["Siemens"] = 842.20;
    StringFloatMap::iterator pos;

    // boom (all prices doubled)
    for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
        pos->second *= 2;
    }

    // print all elements
    for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
        cout << "stock: " << pos->first << "\t"
            << "price: " << pos->second << endl;
    }
    cout << endl;
    // output:
    //      stock: BASF price: 739
    //      stock: BMW  price: 1668
    //      stock: Daimler  price: 1638
    //      stock: Siemens  price: 1684.4
    //      stock: VW   price: 827

    stocks["Volkswagen"] = stocks["VW"];
    for (pos = stocks.begin(); pos != stocks.end();) {
        if(pos->second == 827) {
            stocks.erase(pos++);
            // NOTICE: this is WRONG!!! erase may let the pos invalid
            // stocks.erase(pos);
            // ++pos;
        } else {
            ++pos;
        }
    }

    // print all elements
    for (pos = stocks.begin(); pos != stocks.end(); ++pos) {
        cout << "stock: " << pos->first << "\t"
            << "price: " << pos->second << endl;
    }
    // output:
    //      stock: BASF price: 739
    //      stock: BMW  price: 1668
    //      stock: Daimler  price: 1638
    //      stock: Siemens  price: 1684.4
}
