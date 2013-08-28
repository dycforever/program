#include <iterator>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

template <typename T>
void PRINT_ELEMENTS(T coll){
    copy(coll.begin(), coll.end(), ostream_iterator<typename T::value_type>(cout, " "));
    cout << endl; 
}

int main()
{
    list<int> coll;
 
    front_insert_iterator<list<int> > iter(coll);

    *iter = 1;
    iter++;
    *iter = 2;
    iter++;
    *iter = 3;
    // list: 3 2 1

    // create back inserter and insert elements
    // - convenient way
    back_inserter(coll) = 44;
    front_inserter(coll) = 55;
    PRINT_ELEMENTS(coll);
    // output: //      55 3 2 1 44 

    cout << "\n\ninserter: " << endl;
    vector<int> vec;
    insert_iterator<vector<int> > insert_it(vec,vec.begin());

    // insert elements with the usual insert_itator interface
    *insert_it = 1;
    insert_it++;
    *insert_it = 2;
    insert_it++;
    *insert_it = 3;
    // vector: 1 2 3

    inserter(vec,vec.end()) = 44;
    // vec: 1 2 3 44

    // use inserter to insert all elements into a list
    vector<int> vec2;
    vec2.insert(vec2.begin(), 1);
    vec2.insert(vec2.begin(), 2);
    // vec2: 2 1

    //  if no reserve, the copy below may core!
    //
    //    vec.reserve(2*vec.size());
    //    copy (vec2.begin(), vec2.end(),    // source
    //            back_inserter(vec2));        // destination
    //

    copy (vec.begin(), vec.end(),           // source
            inserter(vec2,++vec2.begin()));   // destination

    PRINT_ELEMENTS(vec2);
    // output:
    //      2 1 2 3 44 1
}
