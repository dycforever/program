
#include "bitset"
#include "queue"

#include "common.h"
#include "graph.h"

namespace dyc{
using namespace std;

template<typename T>
class Search{
public:
    Search(Graph<T>& g):m_graph(g){
    }

//    int init(){
//        travelled = NEW bitset<m_graph.getVertexsNumber>;
//        if(travelled == NULL){
//            WARNING("init Search failed");
//            return -1;
//        }
//        return 0;
//    }

    int DFSsearch(const T& v){
        travelled.reset();
        cout << "travel " << v <<endl;
        travelled.set(v);

        set<T> neighbors = m_graph.getNeighbors(v);
        typename set<T>::iterator it = neighbors.begin();
        while(it != neighbors.end()){
            if( !travelled.test(*it) ){
                DFSsearch(*it);
            }
            ++it;
        }
    }

    // 这边的巧妙之处在于把元素入队的时候先访问一遍
    // 如果放在出队的时候访问，则有可能让同一个元素重复入队（他是队伍中两个元素的邻居）
    // 这样就要在选择入队元素的时候判断一遍，出队的时候再判断一遍
    // 不如下面这样的简洁
    int BFSsearch(const T& v){
        travelled.reset();
        typename set<T>::iterator it;
        queue<T> q;
        q.push(v);
        cout << "travel " << v <<endl;
        travelled.set(v);

        while(!q.empty()){
            T t = q.front();
            q.pop();

            set<T> neighbors = m_graph.getNeighbors(t);
            it = neighbors.begin();
            while(it != neighbors.end()){
                if(!travelled.test(*it)){
                    cout << "travel " << *it <<endl;
                    travelled.set(*it);
                    q.push(*it);
                }
                ++it;
            }
        }
    }

private:
    Graph<T>& m_graph;
    bitset<100> travelled;
};


}

int main(){
    Graph<int> g;
    FILE* fp = fopen("tinyG.txt","r");
    if(fp == NULL){
        FATAL_LOG("fp is null");
    }
//    parseMatrix(g,fp);
//    debug<int, int>(g);
    parseByLine(g,fp);
    g.show();
    Search<int> search(g);
    NOTICE_LOG("begin DFSsearch 0");
//    search.DFSsearch(0);
    NOTICE_LOG("begin DFSsearch 7");
//    search.DFSsearch(7);
    NOTICE_LOG("begin DFSsearch 9");
//    search.DFSsearch(9);

    NOTICE_LOG("begin BFSsearch 0");
    search.BFSsearch(0);
    NOTICE_LOG("begin BFSsearch 7");
    search.BFSsearch(7);
    NOTICE_LOG("begin BFSsearch 9");
    search.BFSsearch(9);
}


