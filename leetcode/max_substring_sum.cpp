#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    int max_sum(const vector<int>& data) {
        vector<int> dp(data.size(), 0);
        vector<pair<int, int>> range(data.size());
        for (int i = 0; i < data.size(); i++) {
            if (i == 0) {
                dp[i] = data[i];
                range[i] = make_pair(0, 0);
            } else {
                if (dp[i-1] + data[i] >= data[i]) {
                    dp[i] = dp[i-1] + data[i];
                    range[i] = make_pair(range[i-1].first, i);
                } else {
                    dp[i] = data[i];
                    range[i] = make_pair(i, i);
                }
            }
        }
        auto maxIter = max_element(dp.begin(), dp.end());
        auto maxIdx = maxIter - dp.begin();
        cout << "max " << *maxIter << " range: " << range[maxIdx].first << ", " << range[maxIdx].second << endl;
        return *maxIter;
    }
};


int main() {
    vector<vector<int>> dataVec = {
        {1,-2,1,1,-2,1}
    };

    Solution s;
    for (auto vec : dataVec) {
        // cout << s.max_sum(vec) << endl;
        s.max_sum(vec);
    }
}

