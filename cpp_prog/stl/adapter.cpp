#include <iterator>
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <algorithm>

using namespace std;

#define print_container(string, container) cout << string; \
    copy(container.begin(), container.end(), ostream_iterator<int>(cout, " "));\
    cout << endl;

//template<class T>
bool mod3 (int p) {
    return p%3==0;
}

int main()
{
    list<int> coll1;

    for (int i=1; i<=9; ++i) {
        coll1.push_back(i);
    }
    print_container("coll1: ", coll1);
    // output:
    //      coll1: 1 2 3 4 5 6 7 8 9
    
    // copy the elements of coll1 into coll2 by appending them
    vector<int> coll2;
    copy (coll1.begin(), coll1.end(),      // source
            back_inserter(coll2));           // destination
    print_container("coll2: ", coll2);
    // output:
    //      coll2: 1 2 3 4 5 6 7 8 9 

    deque<int> coll3;
    copy (coll1.begin(), coll1.end(),      // source
            front_inserter(coll3));          // destination
    print_container("coll3: ", coll3);
    // output:
    //      coll3: 9 8 7 6 5 4 3 2 1 

    set<int> coll4;
    copy (coll1.begin(), coll1.end(),      
            inserter(coll4,coll4.begin()));  
    print_container("coll4: ", coll4);
    // output:
    //      coll4: 1 2 3 4 5 6 7 8 9

    copy (coll1.rbegin(), coll1.rend(),      
            inserter(coll4,coll4.begin()));  
    print_container("coll4 with rbegin: ", coll4);
    // output:
    //      coll4 with rbegin: 1 2 3 4 5 6 7 8 9  (because coll4 is a set!!)

    remove_if(coll1.begin(), coll1.end(), mod3);
    print_container("coll1 after remove mod3: ", coll1);
    // output:
    //      coll1 after remove mod3: 1 2 4 5 7 8 7 8 9

    list<int> coll5;
    for (int i=1; i<=9; ++i) {
        coll5.push_back(i);
    }
    list<int>::iterator it = remove_if(coll5.begin(), coll5.end(), mod3);
    coll5.erase(it, coll5.end());
    print_container("coll5: ", coll5);
    // output:
    //      coll5: 1 2 4 5 7 8 

    list<int> coll6;
    // transform all elements into coll2 by multiplying 10
    transform (coll5.begin(),coll5.end(),        // source
            back_inserter(coll6),             // destination
            bind2nd(multiplies<int>(),10));   // operation
    print_container("coll6: ", coll6);
    // output:
    //      coll6: 10 20 40 50 70 80

}
