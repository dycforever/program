#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

vector<pair<int, char>> transform(const string& s) {
    size_t start = 0;
    vector<pair<int, char>> results;
    while(start < s.size()) {
        size_t pos = s.find_first_not_of("X", start);
        if (pos == string::npos) {
            break;
        }
        int xCnt = pos - start;
        results.push_back(make_pair(xCnt, s[pos]));
        start = pos + 1;
    }
    return results;
}

bool isValid(vector<pair<int, char>>& start, 
             vector<pair<int, char>>& end) {
    if (start.size() != end.size()) {
        return false;
    }
    for (size_t i = 0; i < start.size(); i++) {
        if (start[i].second != end[i].second) {
            return false;
        }
        if (start[i].second == 'R') {
            if (end[i].first < start[i].first) {
                return false;
            } else if (end[i].first > start[i].first) {
                int diff = end[i].first - start[i].first;
            }
        }
    }
}

int main() {
    string start = "RXXLRXRXL";
    string end =   "XRLXXRRLX";
    
    auto transformedStart = transform(start);
    for (auto t : transformedStart) {
        cout << t.first << ", " << t.second << endl;
    }

    cout << "=========\n";

    auto transformedEnd = transform(end);
    for (auto t : transformedEnd) {
        cout << t.first << ", " << t.second << endl;
    }

    cout << isValid(vector<pair<int, char>> transformedStart, vector<pair<int, char>> transformedEnd) << endl;
}

