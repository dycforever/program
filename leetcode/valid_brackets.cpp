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
    bool _isValid(const string& s) {
        list<char> stack;
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (c == '(') {
                stack.push_back(c);
            } else if (c == ')') {
                if (stack.size() == 0) {
                    cout << "xxx:" << s << endl;
                    return false;
                } else {
                    stack.pop_back();
                }
            } else {
            }
        }
        if (stack.size() == 0) {
            return true;
        }
        return false;
    }

    bool isValid(string s) {
        int leftCnt = 0;
        int starCnt = 0;
        int rightCnt = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(')  {
                leftCnt++;
            } else if (s[i] == ')') {
                rightCnt++;
            } else {
                starCnt++;
            }
        }
        cout << leftCnt << ", " << rightCnt << ", " << starCnt << endl;
        if (leftCnt > rightCnt) {
            if (starCnt < (leftCnt - rightCnt)) {
                cout << "zzzz";
                return false;
            }
            int modifiedCnt = 0;
            for (int i = s.size() -1; i >= 0; i--) {
                if (s[i] == '*') {
                    s[i] = ')';
                    modifiedCnt++;
                }
                if (modifiedCnt == (leftCnt - rightCnt)) {
                    break;
                }
            }
        } else if (leftCnt < rightCnt) {
            if (starCnt < (leftCnt - rightCnt)) {
                cout << "yyy";
                return false;
            }           
            int modifiedCnt = 0;
            for (int i = 0; i < s.size(); i++) {
                if (s[i] == '*') {
                    s[i] = '(';
                    modifiedCnt++;
                }
                if (modifiedCnt == (rightCnt - leftCnt)) {
                    break;
                }
            }
        }
        // cout << "validing " << s << endl;
        return _isValid(s);
    }
};

int main() {
    Solution solution;
    vector<string> strVec = {
        // "(",
        // ")",
        // "())",
        // "(()",
        // "(*(*))((*"
        // "()",
        // "*)",
        // "(*",
        // "(*)",
        // "((*)",
        // "(*))",
        "((((()(()()()*()(((((*)()*(**(())))))(())()())(((())())())))))))(((((())*)))()))(()((*()*(*)))(*)()"
    };
    for (auto s : strVec)
        cout << solution.isValid(s) << endl;
    return 0;
}