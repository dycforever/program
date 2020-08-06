#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isValid(vector<int> cnt, int threshold) {
        for (int i = 0; i < cnt.size(); i++) {
            if (cnt[i] > threshold) {
                return false;
            }
        }
        return true;
    }

    bool isEqual(vector<int> cnt, int threshold) {
        for (int i = 0; i < cnt.size(); i++) {
            if (cnt[i] != threshold) {
                return false;
            }
        }
        return true;
    }

    int min_replace(const vector<int>& data) {
        vector<int> cnt(4, 0);
        for (int d : data) {
            cnt[d]++;
        }

        if (isEqual(cnt, data.size()/ 4)) {
            return 0;
        }
        int minLen = data.size() + 1;
        for (int start = 0; start < data.size(); start++)  {

            vector<int> cntTmp = cnt;
            for (int end = start+1; end <= data.size(); end++)  {
                cntTmp[data[end-1]]--;
                // all <= threshold
                if (isValid(cntTmp, data.size()/4)) {
                    minLen = min(end - start, minLen);
                }
            }
        }
        return minLen;
    }
};


vector<vector<int>> to_int(const vector<string>& stringVec) {
    vector<vector<int>> dataVec(stringVec.size());
    int i = 0;
    for (const auto& s : stringVec) {
        dataVec[i] = vector<int>(4, 0);
        int j = 0;
        for (char c : s) {
            if (c=='Q') {
                dataVec[i][j] = 0;
            } else if (c=='W') {
                dataVec[i][j] = 1;
            } else if (c=='E') {
                dataVec[i][j] = 2;
            } else if (c=='R') {
                dataVec[i][j] = 3;
            }
            j++;
        }
        i++;
    }
    return dataVec;
}

int main() {
    vector<string> stringVec = {
        "QWER",
        "QQWE",
        "QQQW",
        "QQQQ"
    };

    vector<vector<int>> dataVec = to_int(stringVec);

    Solution s;
    for (auto vec : dataVec) {
        cout << s.min_replace(vec) << endl;
    }
}


