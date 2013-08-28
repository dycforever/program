#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

int main()
{
    list<int> coll;

    for (int i=1; i<=9; ++i) {
        coll.push_back(i);
    }

    // find position of element with value 5
    list<int>::iterator pos;
    pos = find (coll.begin(), coll.end(),
            5);

    // print value to which iterator pos refers
    cout << "pos:  " << *pos << endl;
    list<int>::reverse_iterator rpos(pos);
    cout << "rpos: " << *rpos << endl;
    list<int>::iterator rrpos = rpos.base();
    cout << "rrpos: " << *rrpos << endl;
    // output:
    //      pos:  5
    //      rpos: 4
    //      rrpos: 5
}
