
#include <assert.h>
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
        int binary_find(const vector<int> &num, int target) {
            int size = num.size();
            int left = 0;
            int right = size-1;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (num[mid] == target) {
                    return mid;
                } else if (num[mid] < target) {
                    left = mid+1;
                } else {
                    right = mid-1;
                }
            }
            return -1;
        }

        int find_target(const vector<int> &num, int oleft, int oright) {
            int left = oleft;
            int right = oright;
            cout << "left: " << left << " right: " << right << endl;
            int target = -(num[left] + num[right]);
            while (left < right) {
                int mid = (left + right) / 2;
//                cout << "mid: " << mid << endl;
//                cout << "left: " << left << " right: " << right << endl;
                if (num[mid] == target && mid != oleft && mid != oright) {
                    return mid;
                } else if (num[mid] < target) {
                    left = mid+1;
                } else {
                    right = mid-1;
                }
            }
            return -1;
        }
        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<vector<int> > threeSum(vector<int> &num) {
            sort(num.begin(), num.end());
            vector<vector<int> > solution;
            int zero_idx = 9;
            assert(num[zero_idx] == 0);
            int left = 0;
            int right = num.size() - 1;
            while (true) {
                int target = find_target(num, left, right);
                if (target > 0) {
                    vector<int> tmp;
                    tmp.push_back(num[left]);
                    tmp.push_back(num[target]);
                    tmp.push_back(num[right]);
                    solution.push_back(tmp);
                }
                if(left < zero_idx) {
                    ++left;
                }

                target = find_target(num, left, right);
                if (target > 0) {
                    vector<int> tmp;
                    tmp.push_back(num[left]);
                    tmp.push_back(num[target]);
                    tmp.push_back(num[right]);
                    solution.push_back(tmp);
                }
                if (right > zero_idx) {
                    --right;
                }
                if (left == zero_idx && right == zero_idx) {
                    break;
                }
            }
            return solution;
        }

};

int main () {
    Solution s;
    int array0[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> vec0(array0, array0 + sizeof(array0)/sizeof(array0[0]));
    for (uint32_t i=0; i<10; ++i) {
        cout << s.binary_find(vec0, i) << endl;
    }
    return 0;

    int array[] = {-9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> vec(array, array + sizeof(array)/sizeof(array[0]));
    PRINT_ELEMENTS(vec);
    cout << endl;

    vector<vector<int> > r = s.threeSum(vec);
    for (vector<vector<int> >::iterator it = r.begin(); it != r.end(); ++it) {
        PRINT_ELEMENTS(*it);
        cout << endl;
    }
}