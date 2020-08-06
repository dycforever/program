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
    map<int, int> travel(int n, 
                const vector<pair<int, int>>& edges,
                const string& labels,
                int startNodeId) {
        vector<list<int>*> queues(2);
        queues[0] = new list<int>;
        queues[1] = new list<int>;

        map<int, list<int>> neighbors;
        for (const auto& pair : edges) {
            neighbors[pair.first].push_back(pair.second);
            neighbors[pair.second].push_back(pair.first);
        }

        set<int> visited;
        int layerId = 0;
        list<int>* queue = queues[layerId];
        queue->push_back(0);
        visited.insert(0);

        bool breakAll = false;
        while (queue->size() > 0) {
            layerId++;
            auto nextQueue = queues[layerId % 2];
            for (auto nid : *queue) {
                for (auto neighbor : neighbors[nid]) {
                    if (visited.find(neighbor) == visited.end()) {
                        nextQueue->push_back(neighbor);
                        visited.insert(neighbor);
                    }
                    if (neighbor == startNodeId) {
                        breakAll = true;
                        break;
                    }
                }
                if (breakAll) {
                    break;
                }
            }
            if (breakAll) {
                break;
            }
            queue->clear();
            queue = nextQueue;
        }

        map<int, int> ret;
        queues[0]->clear();
        queues[1]->clear();
        queue = queues[layerId % 2];
        while (queue->size() > 0) {
            layerId++;
            auto nextQueue = queues[layerId % 2];
            for (auto nid : *queue) {
                for (auto neighbor : neighbors[nid]) {
                    if (visited.find(nid) == visited.end()) {
                        ret[labels[nid]]++;
                        nextQueue->push_back(nid);
                    }
                }
            }
            queue->clear();
            queue = nextQueue;
        }
        return ret;
    }
};

int main() {
    Solution s;
    int n = 7;
    vector<pair<int, int>> edges = {
        {0, 1},
        {0, 2},
        {1, 4},
        {1, 5},
        {2, 3},
        {2, 6}
    };
    string labels = "abaedcd";
    s.travel(n, edges, labels, 1);

    return 0;
}