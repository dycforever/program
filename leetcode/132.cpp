#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isValid(const vector<int>& data,
                 int start, int end) {
        if (end - start <= 2) {
            return false;
        }
        vector<int> minVals(data.size());
        for (int i = 0; i < data.size(); i++) {
            if (i == 0) {
                minVals[i] = data[i];
            } else {
                minVals[i] = min(data[i], data[i-1]);
            }
        }

        for (int i = start+1; i < end-1; i++) {
            int mid = data[i];
            int minVal = minVals[i-1];
            for (int j = i+1; j < end; j++) {
                if (data[j] > minVal && data[j] < mid) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    vector<vector<int>> dataVec = {
        {1,3,2},
        {1,2,3,5},
        {3,1,4,2},
        {-2,1,2,-2,1,2}
    };

    Solution s;
    for (auto vec : dataVec) {
        cout << s.isValid(vec, 0, vec.size()) << endl;
    }
}


