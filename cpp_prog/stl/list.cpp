#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;

void printLists (const list<int>& l1, const list<int>& l2)
{
    cout << "list1: ";
    copy (l1.begin(), l1.end(), ostream_iterator<int>(cout," "));
    cout << endl << "list2: ";
    copy (l2.begin(), l2.end(), ostream_iterator<int>(cout," "));
    cout << endl << endl;
}

int main()
{
    vector<int> coll;
    list<int> list0;
    sort(coll.begin(), coll.end());
    // compile error: sort only for random access iterator
    //
    // sort(list0.begin(), list0.end());
    
    // NOTICE: list2 push front
    list<int> list1, list2;
    for (int i=0; i<6; ++i) {
        list1.push_back(i);
        list2.push_front(i);
    }

    // insert all elements of list1 before the first element with value 3 of list2
    // - find() returns an iterator to the first element with value 3
    list2.splice(find(list2.begin(),list2.end(),  // destination position
                3),
            list1);                          // source list
    printLists(list1, list2);
    // NOTICE source !!
    // output:
    //     list1: 
    //     list2: 5 4 0 1 2 3 4 5 3 2 1 0

    // move first element to the end
    list2.splice(list2.end(),        // destination position
            list2,              // source list
            list2.begin());     // source position
    printLists(list1, list2);
    // output:
    //      list1: 
    //      list2: 4 0 1 2 3 4 5 3 2 1 0 5

    // sort second list, assign to list1 and remove duplicates
    list2.sort();
    list1 = list2;
    list2.unique();
    printLists(list1, list2);
    // output:
    //      list1: 0 0 1 1 2 2 3 3 4 4 5 5 
    //      list2: 0 1 2 3 4 5

    // merge both sorted lists into the first list
    list1.merge(list2);
    printLists(list1, list2);
    // output:
    //      list1: 0 0 0 1 1 1 2 2 2 3 3 3 4 4 4 5 5 5 
    //      list2: 

}
