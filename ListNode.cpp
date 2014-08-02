//
//  ListNode.cpp
//  ListMiner
//
//  Created by Chenhao Liu on 11/29/12.
//  Copyright (c) 2012 Chenhao Liu. All rights reserved.
//

#include "ListNode.h"
#include "Graph.h"

ListNode::ListNode(){
        start=-1,end=-1,support=0,G=new Graph();
    }
ListNode::ListNode(const int s,const int e,const int spt,const Graph* g):start(s),end(e),support(spt){
    G=new Graph(*g);
}
ListNode::ListNode(const ListNode& node){
    start=node.getStart();
    end=node.getEnd();
    support=node.getSupport();
    G=new Graph(*node.getGraph());
}
int ListNode::getStart() const{
    return start;
}
void ListNode::setStart(int s){
    start=s;
}
int ListNode::getEnd() const{
    return end;
}
void ListNode::setEnd(int e){
    end=e;
}
int ListNode::getSupport() const{
    return support;
}
void ListNode::setSupport(int s){
    support=s;
}
Graph* ListNode::getGraph() const{
    return G;
}

void ListNode::setGraph(const Graph& g){
    if (G) {
        delete G;
    }
    G=new Graph(g);
}
void ListNode::operator=(const ListNode& node){
    start=node.getStart();
    end=node.getEnd();
    support=node.getSupport();
    G=new Graph(*node.getGraph());
}
bool ListNode::operator==(const ListNode& node) const{
    if (start!=node.getStart()) {
        return false;
    }
    if(end!=node.getEnd()){
        return false;
    }
    if (support!=node.getSupport()) {
        return false;
    }
    return (*G)==(*node.getGraph());
}
void ListNode::incrementSupport(){
    ++support;
}