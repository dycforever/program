/*
 * graph.h
 *
 *  Created on: Sep 6, 2011
 *      Author: dyc
 */
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <utility>

#include <iostream>
#include <stdio.h>

#include "common.h"
using namespace std;
using namespace dyc;

// 其实就是一般意义上的edge
// 只是类中用邻接list来实现，
// edge就变成了vertex数组中的邻居
template<typename W=int>
class Neighbor{
public:
    // 对应结点在vinfo数组中的下标
	int dest; 
	W weight;
    Neighbor(int d,W w):dest(d),weight(w){};

    bool operator<(const Neighbor& n2)const{
        return (this->dest) < n2.dest;
    }
    bool operator==(const Neighbor& n2)const{
        return this->dest == n2.dest;
    }
};

// 泛型后的结点，Ｔ是结点数据类型，Ｗ是边的权重类型
template<typename T, typename W=int>
class VertexInfo{
public:
    // 从vertex的值到其index的映射
    // 所以所有vertex的值其实是放在map中的
	typename map<T ,int>::iterator vtxMapLoc;

    // 与本结点有边的其他结点
	set<Neighbor<W> > edges;  

    // 结点的入度
	int inDegree;

    // 是否已经被使用
	bool occupied;  

	VertexInfo(typename map<T,int>::iterator v ):vtxMapLoc(v){};
//	VertexInfo(){};
};

template <typename T=int, typename W=int>
class Graph{
public:
    Graph(){
        numVertexs = 0;
        numEdges = 0;
    }

    // 获得数据ｖ所代表的结点的下标,取得对应的Info结构
    // 然后遍历它的edges集合
    set<T> getNeighbors(const T& v){
    	int index = vtxMap[v];
    	const VertexInfo<T, W>& vertex = vinfo[index];
    	set<T> tmp;
    	typename set<Neighbor<W> >::iterator it;
    	int nodeid;
    	for(it = vertex.edges.begin();it!=vertex.edges.end();it++){
    		nodeid = (*it).dest;
    		tmp.insert((*vinfo[nodeid].vtxMapLoc).first);
    	}
    	return tmp;
    }
    
    // 把info数组中所有的occupy熟悉置为false
    // 然后把 vertex value->index的map清空
    void clear(){
    	for(int i=0;i<vinfo.size();i++){
    		if(vinfo[i].occupied==true){
    			vinfo[i].occupied=false;
    			availStack.push(i);
    		}
    	}
    	for(typename VertexMap::iterator it = vtxMap.begin();it!=vtxMap.end();it++){
    		vtxMap.erase(it->first);
    	}
    	numVertexs = 0;
    	numEdges = 0;
    }
    
    // 如果边和结点数都为０，则图为空
    bool empty(){
    	if(numVertexs == 0 && numEdges == 0)
    		return 1;
    	return 0;
    }
    
    // 消除v1和v2指定的边
    void eraseEdge(T v1,T v2){
    	int index = vtxMap[v1];
    	set<Neighbor<W> >& edgeSet1 = vinfo[index].edges;
    	typename set<Neighbor<W> >::iterator it = edgeSet1.begin();
    	while(it != edgeSet1.end()){
    		if(it->dest == v2){
    			edgeSet1.erase(it);
    			break;
    		}
    		it++;
    	}
        --numEdges;

    	index = vtxMap[v2];
    	set<Neighbor<W> >& edgeSet2 = vinfo[index].edges;
    	it = edgeSet2.begin();
    	while(it != edgeSet2.end()){
    		if(it->dest == v1){
    			edgeSet2.erase(it);
    			break;
    		}
    		it++;
    	}
        --numEdges;
    }
    
    void eraseVertex(T v){
        NOTICE("begin erase");
    	const int index = vtxMap[v];
    	//remove edge to v
        set<T>* edges = getNeighbors(v);
        typename set<T>::iterator it = edges->begin();
    	while(it != edges->end()){
            eraseEdge(v, *it);
            ++it;
//            eraseEdge(*it, v);
    	}
    	vtxMap.erase(v);
    	//把废弃的info结点放到stack cache
    	vinfo[index].occupied = false;
    	availStack.push(index);
        --numVertexs;
    }
    
    // 获得指定边的权重
    W getWeight(T v1,T v2){
    	int index = vtxMap[v1];
    	set<Neighbor<W> > edgeSet = vinfo[index].edges;
    	typename set<Neighbor<W> >::iterator it = edgeSet.begin();
    	for(;it!=edgeSet.end();it++){
    		if(*it==v2)
    			return (*it).weight;
    	}
    }
    
    // 获得指定结点的入度
    int inDegree(T v){
    	int count = 0;
    	for(int i=0;i<vinfo.size();i++){
    	    const set<Neighbor<W> >& edgeSet = vinfo[i].edges;
    		typename set<Neighbor<W> >::iterator it = edgeSet.begin();
    		for(;it!=edgeSet.end(); ++it){
    			if(*it == v){
    				++count;
    				break;
    			}
    		}
    	}
        return count; 
    }
    
    void insertEdge(T v1,T v2, W w=1){
    	int index1 = vtxMap[v1];
    	int index2 = vtxMap[v2];
        Neighbor<W> nb(index2, w);
    	typename set<Neighbor<W> >::iterator it = vinfo[index1].edges.find(nb);
        if(it != vinfo[index1].edges.end())
            return;
    	Neighbor<W> edge1(index2,w);
    	Neighbor<W> edge2(index1,w);
    	vinfo[index1].edges.insert(edge1);
        ++numEdges;
    	vinfo[index2].edges.insert(edge2);
        ++numEdges;
    }
    
    // 插入一个结点
    // 先看是否有空闲的info结构，如果有就利用，避免重新分配，并获得index
    // 然后构造一个<v, index>的pair，插入到map中
    // 最后要给刚才的info结构中的vtxMapLoc字段赋值
    int insertVertex(T v){
    	int index = -1;
    	if(!availStack.empty()){
    		index = availStack.top();
    		availStack.pop();
        }else{
            VertexInfo<T, W> tmp(vtxMap.end());
    		vinfo.push_back(tmp);
            index = vinfo.size()-1;
        }

        pair<T,int> p(v,index);
        vtxMap.insert(p);

        // 空的info结构中的vtxMapLoc与occupied字段需要赋值
        typename map<T,int>::iterator it = vtxMap.begin();
        for(;it!=vtxMap.end();it++){
            int s = it->second;
            if(s == index){
                vinfo[index].vtxMapLoc = it;
                break;
            }
        }

    	vinfo[index].occupied = true;
        ++numVertexs;
    }
    
    int outDegree(T v){
    	int index = vtxMap[v];
    	return vinfo[index].edges.size();
    }
    
    void setWeight(T v1,T v2,int weight){
    	int index = vtxMap[v1];
    	set<Neighbor<W> > edgeSet = vinfo[index].edges;
    	typename set<Neighbor<W> >::iterator it = edgeSet.begin();
    	for(;it!=edgeSet.end();it++){
            if(*it==v2)
                (*it).weight = weight;
        }
    }


    void show(){
        printf("----------------show graph----------------\n");
        printf("vertexs: %d \t edges: %d \n", numVertexs, numEdges);
        for(unsigned int i=0;i<vinfo.size();i++){
            if(vinfo[i].occupied == false)
                continue;
 //           printf("vertex[%d]has %d neighbors:\n", i, vinfo[i].edges.size());
            map<int,int> neighbor;
            typename set<Neighbor<W> >::iterator it = vinfo[i].edges.begin();
            for(;it!=vinfo[i].edges.end();++it){
//                printf("in for i=%d weight=%d\n", i, (*it).weight);
                if((*it).weight > 0){
                    pair<int,int> p(it->dest, (*it).weight);
                    neighbor.insert(p);
                }
            }
            for(int j=0;j<vinfo.size();j++){
                if(vinfo[j].occupied == false)
                    continue;
                if(neighbor.find(j)==neighbor.end())
                    printf("0 ");
                else
                    printf("%d ",neighbor[j]);
            }
            printf("\n");
        }
    }

   VertexInfo<T, W>* getvInfo(int index){
       if(index >= numVertexs){
           WARNING("index[%d] out of range[%d]", index, numVertexs);
           return NULL;
       }
       return vinfo + index;
   }

   int getVertexNumber(){
       return numVertexs;
   }

   int getEdgeNumber(){
       return numEdges;
   }

private:
   typedef map<T,int> VertexMap;
   VertexMap vtxMap;
   vector<VertexInfo<T, W> > vinfo;
   int numVertexs;
   int numEdges;

   // 空闲info结构在数组中的下标
   stack<int> availStack;
};


template<typename T, typename W>
void debug(Graph<T,W>& g){
    for(int i=0;i<3;i++)
    	g.insertVertex(i);
    g.insertEdge(0,1);
    g.insertEdge(2,1);
    g.insertEdge(0,2);
    g.insertEdge(0,1);
    g.show();
    g.eraseEdge(2,1);
    g.show();

    g.eraseVertex(1);
    g.show();

    g.clear();
    cout <<"empty:" << g.empty() << endl;
    g.show();
}

template<typename T, typename W>
void parseMatrix(Graph<T, W>& g,FILE* f){
	int num;
	fscanf(f, "%d", &num);
    NOTICE("%d vertex", num);
	for(int i=0;i<num;i++)
		g.insertVertex(i);

    int weight;
	for(int line=0;line<num;line++){
		NOTICE("in for line");
	    for(int vi=0; vi<num; vi++){
	        fscanf(f, "%d", &weight);
            g.insertEdge(line, vi, weight);
        }
	}
}

template<typename T, typename W>
void parseByLine(Graph<T, W>& g,FILE* f){
	int edgeNum, vertexNum;
	fscanf(f, "%d %d", &vertexNum, &edgeNum);
    NOTICE("%d vertexs with %d edges", vertexNum, edgeNum);
	for(int i=0; i<vertexNum; i++)
		g.insertVertex(i);

	for(int line=0; line<edgeNum; line++){
        int node1, node2;
	    fscanf(f, "%d %d", &node1, &node2);
        g.insertEdge(node1, node2);
	}
}

