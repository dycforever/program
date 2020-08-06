#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    int sum(const vector<int>& data) {
        if (data.size() == 0) {
            return 0;
        }
        if (data.size() == 1) {
            return data[0];
        }

        vector<int> dp(data.size(), 0);
        dp[0] = data[0];

        for (int i = 1; i < data.size(); i++) {
            dp[i] = 0;
            int minTmp = data[i];
            for (int j = i; j >= 0; j--) {
                minTmp = min(minTmp, data[j]);
                dp[i] += minTmp;
            }
        }
        int ret = 0;
        for (int i = 0; i < data.size(); i++) {
            ret += dp[i];
            ret = ret % ((size_t)(1e9+7));
        }
        return ret;
    }
};


int main() {
    vector<vector<int>> dataVec = {
        {3},
        {3,1},
        {3,1,2},
        {3,1,2,4}
    };

    Solution s;
    for (auto vec : dataVec) {
        // cout << s.max_sum(vec) << endl;
        // cout << s.sum(vec) << endl;
    }
}

