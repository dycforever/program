#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

class Solution {
    void deleteComments(const vector<string>& lines);
};

void Solution::processLine(const string& line) {
    if (stat == 1) {
        return processLine(line);
    }
}

void Solution::deleteComments() {
    vector<string> result;
    for (auto line : lines) {
        result.push_back(processLine(line));
    }
}

int main() {
    vector<string> lines;

}
