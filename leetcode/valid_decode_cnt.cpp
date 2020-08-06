#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    int decodeCnt(const string& s, int start, int end) {
        if (end - start == 2) {
            if (s[start+1] == '0') {
               if (s[start] == '1' || s[start] == '2') {
                   return 1;
               } else {
                   return 0;
               }
            } else if (s[start] == '0') {
                return 0;
            } else {
                int n = atoi(s.substr(start, 2).c_str());
                if (n <= 26) {
                    return 2;
                }
                return 1;
            }
        }
        if (end - start == 1) {
            if (s[start] == '0') {
                return 0;
            }
            return 1;
        }
        if (s[start] == '0') return 0;
        int ret = decodeCnt(s, start+1, end);
        if (end >= start + 2) {
            int n = atoi(s.substr(start, 2).c_str());
            if (n <= 26) {
                ret += decodeCnt(s, start+2, end);
            }
        }
        return ret;
    }

    int decodeCntDP(const string& s) {
        if (s.size() == 0) {
            return 0;
        }
        if (s[0] == '0') {
            return 0;
        }
        if (s.size() == 1) {
            return 1;
        }
        vector<int> dp(s.size());
        int end = s.size();
        dp[0] = 1;
        if (s[1] == '0') {
            if (s[0] == '1' || s[0] == '2') {
                dp[1] = 1;
            } else {
                return 0;
            }
        } else {
            int n = atoi(s.substr(0, 2).c_str());
            if (n <= 26) {
                dp[1] = 2;
            } else {
                dp[1] = 1;
            }
        }

        for (int i = 2; i < end; i++) {
            if (s[i] == '0') {
                if (s[i-1] == '1' || s[i-1] == '2') {
                    dp[i] = dp[i-2];
                } else {
                    return 0;
                }
            } if (s[i-1] == '0') {
                dp[i] = dp[i-1];
            } else {
                int n = atoi(s.substr(i-1, 2).c_str());
                if (n <= 26) {
                    dp[i] = dp[i-2] + dp[i-1];
                } else {
                    dp[i] = dp[i-1];
                }
            }
        }
        return dp[s.size() - 1];
    }
};

int main() {
    Solution solution;
    vector<string> strVec = {
        //"0",
        //"10",
        //"12",
        //"226",
        "101",
        "1001"
    };
    for (auto s : strVec) {
        // cout << "xxx:" << s << endl;
        cout << solution.decodeCnt(s, 0, s.size()) << endl;
        // cout << solution.decodeCntDP(s) << endl;
    }
    return 0;
}
