//
//  Graph.cpp
//  ListMiner
//
//  Created by Chenhao Liu on 11/29/12.
//  Copyright (c) 2012 Chenhao Liu. All rights reserved.
//

#include "Graph.h"

Graph::Graph(){
    graph=new vector<int>();
    graph->clear();
}
Graph::Graph(vector<int>* g){
    graph=new vector<int>(*g);
}
Graph::Graph(const Graph& g){
    graph=new vector<int>(*(g.getter()));
}
vector<int>* Graph::getter() const{
    return graph;
};
void Graph::setter(vector<int>* g){
    graph=new vector<int>(*g);
}
bool Graph::operator==(const Graph& g) const{
    if (g.getter()->size()!=graph->size()) {
        return false;
    }
    int probe=0;
    while (probe<graph->size()) {
        if (graph->at(probe)!=g.getter()->at(probe)) {
            return false;
        }
        ++probe;
    }
    return true;
}
void Graph::operator=(const Graph& g){
    if (graph) {
        delete graph;
    }
    graph=new vector<int>(*(g.getter()));
}
bool Graph::isPartOf(Graph g){
    if (graph->size()>g.getter()->size()) {
        return false;
    }
    vector<int>::iterator it1=graph->begin();
    vector<int>::iterator it2=g.getter()->begin();
    while (it1!=graph->end()&&it2!=g.getter()->end()) {
        if ((*it1)==(*it2)) {
            ++it1,++it2;
        } else if(*it1>*it2)
                ++it2;
        else return false;
    }
    if (it1!=graph->end()) {
        return false;
    }
    return true;
}
Graph::~Graph(){
    if (graph) {
        delete graph;
    }
}
