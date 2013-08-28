#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>

using namespace std;

template <typename T>
void PRINT_ELEMENTS(T coll){
    copy(coll.begin(), coll.end(), ostream_iterator<typename T::value_type>(cout, " "));
}

int main()
{
    vector<int> a(10);

    for (unsigned i=0; i<a.size(); ++i) {
        a[i] = i+1;
    }
    PRINT_ELEMENTS(a);
    cout << endl;

    reverse(a.begin(),a.end());
    PRINT_ELEMENTS(a);
    cout << endl;

    transform(a.begin(),a.end(),    // source
            a.begin(),            // destination
            negate<int>());       // operation
    PRINT_ELEMENTS(a);
    cout << endl;

    int coll[] = { 5, 6, 2, 4, 1, 3 };

    // square all elements
    transform (coll, coll+6,        // first source
            coll,                // second source
            coll,                // destination
            multiplies<int>());  // operation

    // sort beginning with the second element
    sort (coll+1, coll+6);

    // print all elements
    copy (coll, coll+6,
            ostream_iterator<int>(cout," "));
    cout << endl;
}
