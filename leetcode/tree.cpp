#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

struct Node {
    Node* left;
    Node* right;
    int val;
};

void split(const string& s, vector<string>& results, const string& delimitor) {
    size_t start = 0;
    size_t end = 0;
    while (end < s.size()) {
        end = s.find(delimitor, start);
        if (end == string::npos) {
            results.push_back(s.substr(start, s.size() - start));
            break;
        }
        results.push_back(s.substr(start, end - start));
        start = end + delimitor.size();
        end = start;
    }
}

Node* parse(const vector<int>& seq,
            size_t start, size_t end) {
    if (start >= end) {
        return NULL;
    }
    int v = seq[start];
    size_t pos = start + 1;
    while (seq[pos] < v) {
        pos++;
    }
    Node* left = parse(seq, start+1, pos);
    Node* right = parse(seq, pos, end);
    Node* node = new Node();
    node->val = v;
    node->left = left;
    node->right = right;
    return node;
}

void bfs(Node* node) {
    vector<vector<Node*>> queues(2);
    size_t queueId = 0;
    vector<Node*>* queue = &queues[0];
    queue->push_back(node);
    while (queue->size() > 0) {
        queueId = (queueId+1) % 2;
        vector<Node*>* next_queue = &queues[queueId];
        for (auto n : *queue) {
            if (n == NULL) {
                cout << "NULL" << endl;
                continue;
            }

            cout << n->val << endl;
            if (n->left == NULL && n->right == NULL) {
                continue;
            }
            next_queue->push_back(n->left);
            next_queue->push_back(n->right);
        }
        queue->clear();
        queue = next_queue;
    }
}

void dfs(Node* node) {
    if (node == NULL) {
        return;
    }
    dfs(node->left);
    cout << node->val << endl;
    dfs(node->right);
}

int main() {
    string s = "4,2,1,7,6,8";
    vector<string> results;
    split(s, results, ",");

    vector<int> seq;
    for (auto s : results) {
        seq.push_back(atoi(s.c_str()));
    }
    Node* root = parse(seq, 0, results.size());
    cout << "==========\n";
    bfs(root);
    cout << "==========\n";
    dfs(root);
}
