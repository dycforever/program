#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>
using namespace std;

template <typename T>
void PRINT_ELEMENTS(T coll){
    copy(coll.begin(), coll.end(), ostream_iterator<typename T::value_type>(cout, " "));
    cout << endl; 
}

class Nth {    // function object that returns true for the nth call
    private:
        int nth;       // call for which to return true
        int count;     // call counter
    public:
        Nth (int n) : nth(n), count(0) {
        }
        bool operator() (int) {
            return ++count == nth;
        }
};

int main()
{
     list<int> coll;

     for (int i=1; i<=9; ++i) {
         coll.push_back(i);
     }

     // remove third element
     list<int>::iterator pos;
     pos = remove_if(coll.begin(),coll.end(),  // range
             Nth(3));                  // remove criterion
     coll.erase(pos,coll.end());

     PRINT_ELEMENTS(coll);
     // output:
     //     1 2 4 5 7 8 9
}
