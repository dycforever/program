
#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>


using namespace std;

template <typename T>
void PRINT_ELEMENTS(T coll){
    copy(coll.begin(), coll.end(), ostream_iterator<typename T::value_type>(cout, " "));
}

class Solution {
    public:
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<vector<int> > threeSum(vector<int> &num) {
        }

};

int main () {
    int array[] = {-9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> vec(array, array + sizeof(array)/sizeof(array[0]));
    PRINT_ELEMENTS(vec);
    cout << endl;

}