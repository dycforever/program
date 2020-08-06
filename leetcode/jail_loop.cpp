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

    char setBit(char c, int n) {
        return c | (1<<n);
    }

    char clearBit(char c, int n) {
        return c & (0<<n);
    }

    bool getBit(char c, int n) {
        return c & (1<<n);
    }

    char nextDay(char c) {
        char ret = 0;
        for (int i = 1; i < 7; i++) {
            if ((getBit(c, i-1) && getBit(c, i+1)) || 
                (!getBit(c, i-1) && !getBit(c, i+1))) {
                ret = setBit(ret, i);
            }
        }
        return ret;
    }

    char jail2char(const vector<int>& jail) {
        char c = 0;
        for (int i = 0; i < jail.size(); i++) {
            bool setbit = (jail[i] == 1);
            if (setbit) {
                c = setBit(c, 7-i);
            }
        }
        return c;
    }

    vector<int> char2jail(char c) {
        vector<int> ret(8);
        for (int i = 0; i < 8; i++) {
            if (getBit(c, 7-i)) {
                ret[i] = 1;
            } else {
                ret[i] = 0;
            }
        }
        return ret;
    }

    string printInBinary(char c) {
        bitset<8> x(c);
        stringstream ss;
        ss << x;
        return ss.str();
    }

    vector<int> solve(char j, int targetDay) {
        map<char, int> record;
        record[j] = 0;
        int dayFirst;
        int dayAgain;
        for (int day = 1; day <= targetDay; day++) {
            j = nextDay(j);
            if (day == targetDay) {
                return char2jail(j);
            }
            if (record.find(j) != record.end()) {
                dayFirst = record[j];
                dayAgain = day;
                break;
            }
            record[j] = day;
        }

        map<char, int> reversedRecord;
        for (auto iter : record) {
            reversedRecord[iter.second] = iter.first;
        }
        int loopLen = dayAgain - dayFirst;
        targetDay -= dayFirst;
        return char2jail(reversedRecord[dayFirst + targetDay%loopLen]);
    }

};


int main() {
    vector<vector<int>> jails = {
        {0,1,0,1,1,0,0,1},
        {1,0,0,1,0,0,1,0},
    };

    Solution s;
    for (const auto& jail : jails) {
        char j = s.jail2char(jail);
        // cout << (int)j << endl;
        // s.printInBinary(j);
        for (int i : s.solve(j, 1000000000)) {
            cout << i << ",";
        }
        cout << endl;
    }
}

