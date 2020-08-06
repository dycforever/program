#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    int atoi(const string& s, int start, int end) {
        int ret = 0;
        for (;start <= end; start++) {
            ret = ret*10 + s[start] - '0';
        }
        return ret;
    }

    int valid(const string& s, int start, int target) {
        int ret = 0;
        for (; start < s.size(); start++) {
            ret = ret * 10 + s[start] - '0';
            if (ret == target) {
                return start+1;
            }
        } 
        return -1;
    }

    bool isAggNumber(const string& s) { 
        // first three number
        int s1 = 0;
        int firstNum;
        int secondNum;
        int thirdNum;
        int nextPos;
        bool found = false;
        for (int e1 = 0; e1 < s.size(); e1++) {
            firstNum = atoi(s, s1, e1);
            int s2 = e1+1;
            for (int e2 = s2; e2 < s.size(); e2++) {
                secondNum = atoi(s, s2, e2);
                thirdNum = firstNum + secondNum;
                nextPos = valid(s, e2+1, thirdNum);
                if (nextPos != -1) {
                    found = true;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        while (nextPos < s.size()) {
            firstNum = secondNum;
            secondNum = thirdNum;
            thirdNum = firstNum + secondNum;
            nextPos = valid(s, nextPos, thirdNum);
            if (nextPos == -1) {
                return false;
            }
        }
        return true;
    }
};

char toChar(uint64_t n) {
    return n + '0';
}

string toStr(uint64_t number) {
    string ret = "";
    while (number != 0) {
        int a = number % 10;
        ret += toChar(a);
        number = number / 10;
    }
    int i = 0;
    int j = ret.size() - 1;
    while (j>i) {
        char tmp = ret[i];
        ret[i] = ret[j];
        ret[j] = tmp;
        j--;
        i++;
    }
    return ret;
}

int main() {
    vector<uint64_t> dataVec = {
        112358, 199100199, 190100190
//        112358        
    };

    Solution s;
    for (auto data : dataVec) {
        // cout << s.max_sum(vec) << endl;
        cout << s.isAggNumber(toStr(data)) << endl;
    }
}

