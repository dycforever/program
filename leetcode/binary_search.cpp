#include <iostream>
#include <vector>
#include <tuple>

using namespace std;



int binarySearch(const vector<int>& data,
                 int target) {
    size_t start = 0;
    size_t end = data.size();

    while (start < end) {
        if (end - start == 1) {
            if (data[start] == target) {
                return start;
            } else {
                return -1;
            }
        }
        size_t mid = start + (end - start) / 2;
        if (data[mid] > target) {
            end = mid;
        } else if (data[mid] < target) {
            start = mid;
        } else {
            return mid;
        }
    }
}

int main() {
    vector<int> data = {0,1,2,3,4,5,6,7,8,9,10};
    for (auto target : data) {
        int ret = binarySearch(data, target);
        cout << ret << endl;
    }

    vector<int> data2 = {0,1};
    for (auto target : data2) {
        int ret = binarySearch(data, target);
        cout << ret << endl;
    }
}

