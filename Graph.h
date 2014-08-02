//
//  Graph.h
//  ListMiner
//
//  Created by Chenhao Liu on 11/29/12.
//  Copyright (c) 2012 Chenhao Liu. All rights reserved.
//

#ifndef __ListMiner__Graph__
#define __ListMiner__Graph__

#include <iostream>
#include <vector>

using namespace std;
class Graph{
public:
    Graph();
    Graph(vector<int>* g);
    Graph(const Graph& g);
    vector<int>* getter() const;
    void setter(vector<int>* g);
    bool operator==(const Graph& g) const;
    void operator=(const Graph& g);
    bool isPartOf(Graph g);
    ~Graph();
private:
    vector<int>* graph;
    //int timestamp;
};


#endif /* defined(__ListMiner__Graph__) */
