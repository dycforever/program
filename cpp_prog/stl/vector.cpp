
#include <iterator>
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <algorithm>

#include "common.h"

using namespace std;
using namespace dyc;

int main () {
    vector<int> coll;
    vector<int> coll2;
    cout << "size: " << coll.size() << " capacity: " << coll.capacity() << endl;
    // output:
    //      size: 0 capacity: 0

    for (int i=0; i<10; ++i) {
        coll.push_back(i);
    }
    Timer time;
    coll.push_back(10);
    long pass = time.ms_spend();
    cout << "size: " << coll.size() << " capacity: " << coll.capacity() << " pass time:" << pass << endl;
    // output:
    //      size: 11 capacity: 16 pass time:0

    coll.reserve(20);
    pass = time.ms_spend();
    cout << "size: " << coll.size() << " capacity: " << coll.capacity() << " pass time:" << pass << endl;
    // output:
    //      size: 11 capacity: 20 pass time:12

    coll.swap(coll2);
    cout << "size: " << coll.size() << " capacity: " << coll.capacity() << endl;
    // output:
    //      size: 0 capacity: 0
    
    // throw exception
    try {
        coll.at(2);
    } catch (exception ex) {
        cout << "catch ex: " << ex.what() << endl;
    }

    // segmentation fault
    //
    // int a = coll[2];
    // list<int> coll3;
    //


}
