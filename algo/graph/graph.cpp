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
#include <graph.h>

int countSpace(char* buf){
	int pos = 0;
	int count;
	while(buf[pos]!='\n'){
		if(buf[pos]==' ') count++;
		pos++;
	}
	return ++count;
}

int main(){
    Graph<int, int> g;
    FILE* fp = fopen("graph.db","r");
    if(fp == NULL){
        FATAL("fp is null");
    }
    parseMatrix(g,fp);
//    debug<int, int>(g);
    g.show();
    return 0;
}

