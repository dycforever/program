#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <set>
#include <list>
#include <algorithm>

using namespace std;

class Solution {
public:
    struct Edge {
        int src;
        vector<int> dsts;
        vector<bool> isRed;
    };

    vector<int> pathLength(int n,
            const vector<vector<int>>& blueEdges,
            const vector<vector<int>>& redEdges) {

        map<int, Edge> edges;
        for (const auto& edge : blueEdges) {
            edges[edge[0]].src = edge[0];
            edges[edge[0]].dsts.push_back(edge[1]);
            edges[edge[0]].isRed.push_back(false);
        }
        for (const auto& edge : redEdges) {
            edges[edge[0]].src = edge[0];
            edges[edge[0]].dsts.push_back(edge[1]);
            edges[edge[0]].isRed.push_back(true);
        }

        typedef pair<int, bool> VisitedNode;

        vector<int> ret(n);
        for (int i = 1; i < n; i++) {
            ret[i] = -1;
        }

        vector<list<VisitedNode>*> queues(2);
        queues[0] = new list<VisitedNode>;
        queues[1] = new list<VisitedNode>;
        int layerId = 0;
        list<VisitedNode>* queue = queues[layerId];
        queue->push_back({0, true});
        queue->push_back({0, false});

        set<VisitedNode> visited;

        while (queue->size() > 0) {
            layerId++;
            auto nextQueue = queues[layerId % 2];
            for (const VisitedNode& node : *queue) {
                auto& edge = edges[node.first];
                for (int neighborIdx = 0; neighborIdx < edge.dsts.size(); neighborIdx++) {
                    if (!(edge.isRed[neighborIdx] ^ node.second)) {
                        continue;
                    }
                    auto pairTmp = make_pair(edge.dsts[neighborIdx], edge.isRed[neighborIdx]);
                    if (visited.find(pairTmp) != visited.end()) {
                        continue;
                    }
                    nextQueue->push_back({edge.dsts[neighborIdx], edge.isRed[neighborIdx]});
                    visited.insert(pairTmp);
                    if (ret[pairTmp.first] == -1) {
                        ret[pairTmp.first] = layerId;
                    } else {
                        ret[pairTmp.first] = min(layerId, ret[pairTmp.first]);
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
    for (int i : s.pathLength(3, {{0,1}, {1,2}}, {})) {
        cout << i << ",";
    }
    cout << endl;

    for (int i : s.pathLength(3, {{1,0}}, {{2,1}})) {
        cout << i << ",";
    }
    cout << endl;

    for (int i : s.pathLength(3, {{0,1}}, {{1,2}})) {
        cout << i << ",";
    }
    cout << endl;

    for (int i : s.pathLength(3, {{0,1}, {0,2}}, {{1,0}})) {
        cout << i << ",";
    }
    cout << endl;
}

