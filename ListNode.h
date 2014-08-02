//
//  ListNode.h
//  ListMiner
//
//  Created by Chenhao Liu on 11/29/12.
//  Copyright (c) 2012 Chenhao Liu. All rights reserved.
//

#ifndef __ListMiner__ListNode__
#define __ListMiner__ListNode__

#include <iostream>
#include "Graph.h"

#endif /* defined(__ListMiner__ListNode__) */
class ListNode{
private:
    int start,end,support;
    Graph* G;
public:
    ListNode();
    ListNode(const int s,const int e,const int spt,const Graph* g);
    ListNode(const ListNode& node);
    int getStart() const;
    void setStart(int s);
    int getEnd() const;
    void setEnd(int e);
    int getSupport() const;
    void setSupport(int s);
    void incrementSupport();
    Graph* getGraph() const;
    void setGraph(const Graph& g);
    void operator=(const ListNode& node);
    bool operator==(const ListNode& node) const;
    
};