//
//  ListMiner.h
//  ListMiner
//
//  Created by Chenhao Liu on 11/29/12.
//  Copyright (c) 2012 Chenhao Liu. All rights reserved.
//

#ifndef __ListMiner__ListMiner__
#define __ListMiner__ListMiner__

#include <iostream>
#include <list>
#include "ListNode.h"
#include "Header.h"
#include <ext/hash_map>
#endif /* defined(__ListMiner__ListMiner__) */

unsigned long myhash(const ListNode& node);
bool myequal(const ListNode& node1,const ListNode& node2);

struct my_compare {
public:
    size_t operator()(const ListNode& node) const{
        return hash<unsigned long>()(myhash(node));
    }
    bool operator()(const class ListNode& g1, const class ListNode& g2) const{
		return *(g1.getGraph())==*(g2.getGraph());
	}
};

class ListMiner{
public:
    void miner(const char* infile,const int,const int,const int);
private:
    void update(list<ListNode*>* L,const int t,const int p,const int sigma,__gnu_cxx::hash_map<ListNode,list<ListNode*>,my_compare>*);
    bool subsumed(ListNode*,const int,const int,__gnu_cxx::hash_map<ListNode,list<ListNode*>,my_compare>*);
    Graph* MCS(const Graph*,const Graph*);
    void print(const ListNode*);
};

