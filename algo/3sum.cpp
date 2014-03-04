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
    cout << endl;
}

class Solution {
    public:
        int binary_find(const vector<int> &num, int target) {
            int size = num.size();
            int left = 0;
            int right = size-1;
            int mid = 0;
            while (left <= right) {
                mid = (left + right) / 2;
                if (num[mid] == target) {
                    return mid;
                } else if (num[mid] < target) {
                    left = mid+1;
                } else {
                    right = mid-1;
                }
            }
            if (num[mid] < target) {
                return mid;
            }
            return mid-1;
        }

        int binary_find_lt(const vector<int> &num, int target) {
            int size = num.size();
            int left = 0;
            int right = size-1;
            int mid = 0;
            while (left <= right) {
                mid = (left + right) / 2;
                if (num[mid] <= target) {
                    left = mid+1;
                } else {
                    right = mid-1;
                }
            }
            if (num[mid] > target) {
                return mid;
            }
            return mid+1;
        }

        int find_target(const vector<int> &num, int left, int right, int target) {
            int mid = (left + right) / 2;
            while (left <= right) {
                mid = (left + right) / 2;
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

        // Note: The Solution object is instantiated only once and is reused by each test case.
        vector<vector<int> > threeSum(vector<int> &num) {
            vector<vector<int> > solution;
            int size = num.size();
            if (size < 3) {
                return solution;
            }
            sort(num.begin(), num.end());
//            PRINT_ELEMENTS(num);
            int zero_idx = binary_find(num, 0);
            if (zero_idx < 0 || zero_idx >= size) {
                return solution;
            }
            assert(num[zero_idx] <= 0);
            int left = 0;

            int right = size;
            for (left = 0; left <= zero_idx; ++left) {
                if (left > 0 && num[left] == num[left-1]) {
                    continue;
                }
                for (right = size-1;right >= zero_idx; --right) {
                    if (right < size-1 && num[right] == num[right+1]) {
                        continue;
                    }
                    int target = find_target(num, left+1, right-1, -(num[left] + num[right]));
                    if (target > 0) {
                        vector<int> tmp;
                        tmp.push_back(num[left]);
                        tmp.push_back(num[target]);
                        tmp.push_back(num[right]);
                        solution.push_back(tmp);
                    }
                }
            }
            return solution;
        }

};

int main () {
    Solution s;
//    int array[] = {-9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//    int array[] = {-1, 0, 1, 2, -1, -4};
//    int array[] = {1, 1, 1};
//    int array[] = {0,0,0,0,-1, -1, -1};
//    int array[] = {0,-5,3,-4,1,3,-4,-2,-2,-2,0,3,0,1,-4,-2,0};
    int array[] = {-1,4,0,0,-4,-5,-4,-5,0,2,-5,2,-2};
    vector<int> vec(array, array + sizeof(array)/sizeof(array[0]));

    vector<vector<int> > r = s.threeSum(vec);
    for (vector<vector<int> >::iterator it = r.begin(); it != r.end(); ++it) {
        PRINT_ELEMENTS(*it);
    }
}