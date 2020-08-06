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
    struct Node {
        Node* left;
        Node* right;
        char val;
    };

    set<int> deleteColumn(const vector<string>& strVec, 
                          size_t lineStart, size_t lineEnd, 
                          size_t colStart) {
        set<int> tobeDelete;
        size_t strLen = strVec[0].size();
        if (colStart == strLen) {
            return tobeDelete;
        }

        for (int cid = colStart; cid < strLen; cid++) {
            bool isAscending = true;
            bool hasEqual = false;
            for (int i = lineStart + 1; i < lineEnd; i++) {
                if (strVec[i][cid] > strVec[i-1][cid]) {
                    isAscending = false;
                    break;
                }
                if (strVec[i][cid] == strVec[i-1][cid]) {
                    hasEqual = true;
                }
            }
            if (!isAscending) {
                tobeDelete.insert(cid);
            }
            if (!hasEqual) {
                continue;
            }
            int i = lineStart + 1;
            while (i < lineEnd) {
                while (strVec[i-1][cid] != strVec[i][cid] && i < lineEnd) {
                    i++;
                }
                int nextStart = i-1;
                while (strVec[i-1][cid] == strVec[i][cid] && i < lineEnd) {
                    i++;
                }
                int nextEnd = i;
                const auto& ret = deleteColumn(strVec, nextStart, nextEnd, cid);
                tobeDelete.insert(ret.begin(), ret.end());
            }
            break;
        }
        return tobeDelete;
    }

    size_t isValid(const vector<string>& strVec) {
        if (strVec.size() == 0) {
            return 0;
        }
        size_t strLen = strVec[0].size();
        for (int i = 1; i < strVec.size(); i++) {
            if (strLen != strVec[i].size()) {
                return -1;
            }
        }
        return deleteColumn(strVec, 0, strVec.size(), 0).size();
    }
};

int main() {
    vector<string> strVec = {
        "ca",
        "bb",
        "ac"
    };
    return 0;
}