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
    void buildRecords(const vector<int>& numbers,
            vector<pair<int, vector<int>>>& records) {
        for (int number : numbers) {
            for (auto& record : records) {
                if (record.first % number != 0) {
                    continue;
                }
                if (valid(record.first, number)) {
                    record.second.push_back(max(record.first, number));
                    record.first = min(record.first, number);
                }
            }
        }
    }

    bool valid(int m, int n) {
        if (m == n) {
            return true;
        }
        int minv = min(m, n);
        int maxv = max(m, n);
        int tmp = 0;
        int idx = 0;
        while (tmp < maxv) {
            tmp = minv * pow(2, idx);
            idx++;
        }
    }

    bool isValie(const vector<int>& numbers) {
        vector<pair<int, vector<int>>> records;
        buildRecords(numbers, records);
        for (auto& record : records) {
            sort(record.second.begin(), record.second.end());
            if (record.second.size() % 2 != 0) {
                return false;
            }
            for (int i = 1; i < record.second.size(); i = i+2) {
                int first = record.second[i-1];
                int second = record.second[i];
                if (first != 2 * second) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    vector<int> data = {};
    vector<pair<int, vector<int>>> records;
    s.buildRecords(data, records);
    return 0;
}