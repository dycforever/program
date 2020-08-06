#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> solve(const vector<int>& rain) {
        vector<int> ret(rain.size());
        map<int, int> rainingDays;
        vector<int> sunDays;
        sunDays.reserve(rain.size());

        for (size_t i = 0; i < rain.size(); i++) {
            if (rain[i] == 0) {
                sunDays.push_back(i);
                continue;
            }
            // 下雨了
            ret[i] = -1;
            int poolId = rain[i];
            if (rainingDays.find(poolId) == rainingDays.end()) {
                rainingDays[poolId] = i;
                continue;
            }
            for (size_t sunDayIdx = 0; sunDayIdx < sunDays.size(); sunDayIdx++) {
                int sunDay = sunDays[sunDayIdx];
                if (sunDay > rainingDays[poolId]) {
                    sunDays[sunDayIdx] = -1;
                    rainingDays.erase(poolId);
                    if (sunDay >= ret.size()) {
                        cout << "xxxxxxxxxxx "<< sunDay  << " : " <<  ret.size() << endl;
                        exit(0);
                    }
                    ret[sunDay] = poolId;
                    break;
                }
            }
        }
        return ret;
    }
};


int main() {
    vector<vector<int>> rains = {
        {1,2,3,4},
        {1,2,0,0,2,1},
        {1,2,0,1,2},
        {69,0,0,0,69},
        {10,20,20},
    };

    Solution s;
    for (const auto& rain : rains) {
        for (int i : s.solve(rain)) {
            cout << i << ",";
        }
        cout << endl;
    }
}

