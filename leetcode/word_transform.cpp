#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:

    bool diffOf1(const string& s1, const string& s2) {
        if (s1.size() != s2.size()) {
            return false;
        }
        int diffCnt = 0;
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] != s2[i]) {
                diffCnt++;
            }
        }
        return diffCnt == 1;
    }

    list<int> travel(map<int, vector<int>>& edges, int startId, int endId) {
        map<int, int> trace;
        vector<list<int>*> queues(2);
        queues[0] = new list<int>();
        queues[1] = new list<int>();

        list<int>* queue = queues[0];
        queue->push_back(startId);
        set<int> visited;
        int qId = 0;

        bool found = false;
        while(queue->size() > 0) {
            if (found) {
                break;
            }
            qId++;
            list<int>* nextQueue = queues[qId % 2];
            for (int curId : *queue) {
                for (int neighborId : edges[curId]) {
                    if (visited.find(neighborId) != visited.end()) {
                        continue;
                    }
                    visited.insert(neighborId);
                    trace[neighborId] = curId;
                    nextQueue->push_back(neighborId);
                    if (neighborId == endId) {
                        found = true;
                    }
                }
            }
            queue->clear();
            queue = nextQueue;
        }
        list<int> ret;
        if (!found) {
            return ret;
        }
        int nextId = endId;
        while(nextId != startId) {
            ret.push_front(nextId);
            nextId = trace[nextId];
        }
        ret.push_front(nextId);
        return ret;
    }

    vector<string> transform(vector<string> wordList, string start, string end) {
        map<int, vector<int>> edges;
        for (int i = 0; i < wordList.size(); i++) {
            const string& word = wordList[i];
            for (int j = 0; j < i; j++) {
                if (diffOf1(wordList[i], wordList[j])) {
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }
            }
        }
        int startId = -1;
        int endId = -1;
        for (int i = 0; i < wordList.size(); i++) {
            const string& word = wordList[i];
            if (word == start) {
                startId = i;
            }
            if (word == end) {
                endId = i;
            }
        }

        vector<string> ret;
        if (startId == -1 || endId == -1) {
            return ret;
        }
        list<int> path = travel(edges, startId, endId);
        ret.reserve(path.size());

        for (int i : path) {
            ret.push_back(wordList[i]);
        }
        return ret; 
    }
};


int main() {
//    vector<string> wordList = {
//        "hit", "hot", "dot", "lot", "log", "cog"
//    };
//    string start = "hit";
//    string end = "cog";


    vector<string> wordList = {
        "hot", "dot", "lot", "log", "cog"
    };
    string start = "hit";
    string end = "cog";


    Solution s;
    for (auto& p : s.transform(wordList, start, end)) {
        cout << p << endl;
    }
}

