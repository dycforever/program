#include <iostream>
#include <vector>
#include <tuple>

using namespace std;


bool find_sub_str(const vector<int>& data, int target) {
    vector<tuple<int, int>> candidates;
    int start = 0;
    int end = 0;
    int sum = 0;
    while (1) {
        if (end == data.size() && sum < target) {
            break;
        }
        if (sum < target) {
            sum += data[end];
            end++;
        } else if (sum > target) {
            sum -= data[start];
            start++;
        } else {
            candidates.push_back(make_tuple(start, end-1));
            if (end != data.size()) {
                sum += data[end];
                end++;
            }
            sum -= data[start];
            start++;
        }
    }
    if (candidates.size() == 0) {
        return false;
    }
    for (auto c : candidates) {
        tie(start, end) = c;
        cout << start << ", " << end << endl;
    }
    vector<int> dp(data.size());
    int dpIdx = 0;
    int cdIdx = 0;
    tie(start, end) = candidates[cdIdx++];
    for (; dpIdx < data.size(); dpIdx++) {
        if (dpIdx == 0) {
            if (end == 0) {
                dp[dpIdx] = 1;
                if (cdIdx < candidates.size()) {
                    tie(start, end) = candidates[cdIdx++];
                }
            } else {
                dp[dpIdx] = 0;
            }
            continue;
        }
        if (end == dpIdx) {
            if (dp[dpIdx-1] != 0) {
                dp[dpIdx] = min(dp[dpIdx-1], end - start + 1); 
            } else {
                dp[dpIdx] = end - start + 1;
            }
            if (cdIdx < candidates.size()) {
                tie(start, end) = candidates[cdIdx++];
            }
        // } else if (end > dpIdx) {
        //     dp[dpIdx] = dp[dpIdx-1];
        } else {
            dp[dpIdx] = dp[dpIdx-1];
        }
    }
    for (auto d : dp) {
        cout << d << ",";
    }

    // for (start = 0; start < data.size(); start++) {
    //     int sum = data[start];
    //     for (end = start+1; end < data.size(); end++) {
    //         sum += data[end];
    //         if (sum == target) {
    //             return true;
    //         }
    //     }
    // }
    return false;
}

int main() {
    vector<int> data = {1,3,4,6,5,3};
    int target = 8;
    int start = 0;
    int end = 0;
    find_sub_str(data, target);
}
