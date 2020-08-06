#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int max_sum(const string& str) {
        int start = 0;
        int end = 0;
        map<char, int> charCnt;
        int maxLen = 0;

        while (start <= end && end < str.size()) {
            // 这里犯错过 !
            char c = str[end];
            charCnt[c]++;
            if (charCnt[c] == 1) {
                maxLen = max(maxLen, end - start + 1);
                // cout << start << "," << end << endl;
                end++;
                continue;
            }
            while(str[start] != c && start < end) {
                // 这里犯错过 !
                charCnt[str[start]]--;
                start++;
            }
            start++;
            charCnt[c]--;
            end++;
        }
        return maxLen;
    }
};


int main() {
    vector<string> strVec = {
        "abcabcbb",
        "b",
        "pwwkew"
    };

    Solution s;
    for (const auto& str : strVec) {
        // cout << s.max_sum(vec) << endl;
        cout << s.max_sum(str) << endl;
    }
}

