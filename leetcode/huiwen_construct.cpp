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
    int char2int(char c) {
        if (c >= 'a' && c <= 'z') {
            return c-'a';
        }
        return c-'A' + 26;
    }

    bool solve(const string& s, const vector<int>& query,
               int prevStart, int prevEnd, 
               vector<bool>& bitmap) {
        // TODO: clear bit
        int start = query[0];
        int end = query[1];
        int repCnt = query[2];

        for (int i = start; i <= end; i++) {
            int idx = char2int(s[i]);
            bitmap[idx] = !bitmap[idx];
        }

        int lowCnt = 0;
        int upCnt = 0;
        for (int i = 0; i < 26; i++) {
            if (bitmap[i]) {
                lowCnt++;
            }
        }
        for (int i = 26; i < 52; i++) {
            if (bitmap[i]) {
                upCnt++;
            }
        }
        int diff = abs(upCnt - lowCnt);
        int minCnt = min(upCnt, lowCnt);
        if (diff <= 2*(repCnt - minCnt) + 1) {
            return true;
        }
        return false;
    }

    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        vector<bool> ret;
        ret.reserve(queries.size());
        vector<bool> bitmap(52, false);
        for (int i = 0; i < queries.size(); i++) {
            const auto& q = queries[i];
            if (i == 0) {
                ret.push_back(solve(s, q, -1, -1, bitmap));
            } else {
                ret.push_back(solve(s, q, queries[i-1][0],
                                    queries[i-1][1], bitmap));
            }
        }
        return ret;
    }
};


int main() {
    vector<vector<int>> queries = { {3,3,0}, {1,2,0}, {0,3,1}, {0,3,2}, {0,4,1} };
    Solution s;
    for (auto b : s.canMakePaliQueries("abcda", queries)) {
        cout << b << " ";
    }

}

