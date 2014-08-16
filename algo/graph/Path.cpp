#include "set"
#include "queue"

#include "common.h"
#include "graph.h"


namespace dyc{
using namespace std;

class Paths{
public:
    Paths(Graph<>& g, int s):m_graph(g), source(s){};
    int init(){
        edgeTo = NEW int[m_graph.getVertexNumber()];
        if(edgeTo == NULL){
            FATAL_LOG("new edgeTo failed");
            return -1;
        }
        reset();
        return 0;
    }


    void reset(){
        memset(edgeTo, 0xFF, sizeof(int)*m_graph.getVertexNumber());
    }

    // edgeTo数组记载的是从某个单源出发，各个结点第一次被访问时
    // 是来自哪个结点的
    bool hasPathTo(int v){
        reset();
        queue<int> q;
        cout << "travel " << source <<endl;
        edgeTo[source] = source;

        q.push(source);
        while(!q.empty()){
            int node = q.front();
            q.pop();

            set<int> neighbors = m_graph.getNeighbors(node);
            typename set<int>::iterator it = neighbors.begin();
            while(it != neighbors.end()){
                // 访问未遍历过的结点
                if(edgeTo[*it] == -1){
                    edgeTo[*it] = node;
                    // 已经找到了通往目的结点v的路径，所以可以break了
                    if(*it == v){
                        NOTICE_LOG("ok find");
                        return true;
                    }
                    NOTICE_LOG("push ing");
                    q.push(*it);
                }
                ++it;
            }
        }
        return false;
    }

    int pathTo(int v){
        int s = edgeTo[v];
        if(s!=source){
            pathTo(s);
        }
        cout << s << "-" << v << endl;

    }

private:
    Graph<>& m_graph;
    int* edgeTo;
    int source;

};

}

int main(){
    Graph<> g;
    FILE* fp = fopen("tinyG.txt","r");
    if(fp == NULL){
        FATAL_LOG("fp is null");
    }
//    parseMatrix(g,fp);
//    debug<int, int>(g);
    parseByLine(g,fp);
    g.show();

    Paths path(g, 0);
    cout << "0 has path to 4 ? : " << path.hasPathTo(4) << endl;
    NOTICE_LOG("show path:");
    path.pathTo(4);
}
